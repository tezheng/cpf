//////////////////////////////////////////////////////////////////////////
#include "Configuration/Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/Scheduler.hpp"
#include "Concurrency/Opcodes.hpp"


TEST(Concurrency, LastFenced_Opcode)
{
	using namespace Cpf;
	using namespace Concurrency;
	ScopedInitializer<Platform::TimeInitializer> timeInit;

	for (auto i = 0; i < 100; ++i)
	{
		Platform::Threading::Thread::Group threads(Platform::Threading::Thread::GetHardwareThreadCount());
		Scheduler* scheduler = new Scheduler;
		scheduler->Initialize(std::move(threads));
		EXPECT_TRUE(scheduler->ThreadCount() >= 4);
		scheduler->CreateQueue().ActiveThreads(4).Submit();
		{
			auto hitCount = 0;

			Scheduler::Queue queue = scheduler->CreateQueue();
			queue.All(
				[](Scheduler::ThreadContext&, void* context)
			{
				// Increment the counter.
				Atomic::Inc(*reinterpret_cast<int*>(context));
			},
				&hitCount);

			queue.LastOneBarrier(
				[](Scheduler::ThreadContext&, void* context)
			{
				// All threads should have executed the counter by the time we get here
				// and none should have gotten to the next instruction.
				EXPECT_EQ(4, Cpf::Atomic::Load(*reinterpret_cast<int*>(context)));
			},
				&hitCount);

			queue.All(
				[](Scheduler::ThreadContext&, void* context)
			{
				// Increment the counter.
				Atomic::Inc(*reinterpret_cast<int*>(context));
			},
				&hitCount);

			// Wait for completion.
			queue.BlockingSubmit();
			EXPECT_EQ(8, hitCount);
		}
		scheduler->Shutdown();
		delete scheduler;
	}
}