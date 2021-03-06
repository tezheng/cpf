//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iFence.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Threading/Thread.hpp"
#include <atomic>

TEST_F(ConcurrencyTest, First_Opcode)
{
	using namespace CPF;
	using namespace Concurrency;

	for (auto i = 0; i < 10; ++i)
	{
		IntrusivePtr<iScheduler> pScheduler;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kSchedulerCID.GetID(), iScheduler::kIID.GetID(), pScheduler.AsVoidPP())));
		EXPECT_TRUE(GOM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

		IntrusivePtr<iFence> pFence;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kFenceCID.GetID(), iFence::kIID.GetID(), pFence.AsVoidPP())));

		IntrusivePtr<iWorkBuffer> pWorkBuffer;
		EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kWorkBufferCID.GetID(), iWorkBuffer::kIID.GetID(), pWorkBuffer.AsVoidPP())));

		{
			std::atomic<int> firstThreadArrived = 0;
			pWorkBuffer->FirstOne([](const WorkContext*, void* context) {
				// Signal that we have arrived.
				(*reinterpret_cast<std::atomic<int>*>(context)).store(1);

				// Wait a sec, just to make sure the next instruction executes before we wake.
				Threading::Thread::Sleep(Time::Seconds(0.1f));
			},
			&firstThreadArrived);
			pWorkBuffer->FirstOne([](const WorkContext*, void* context) {
				// Some thread should arrive that is not the above thread.
				for (; (*reinterpret_cast<std::atomic<int>*>(context)).load() != 1;)
					;
			},
			&firstThreadArrived);

			// Wait for completion.
			pScheduler->Execute(pWorkBuffer);
			pScheduler->Submit(pFence);
			pFence->Wait();
			EXPECT_EQ(1, firstThreadArrived);
		}
		pScheduler->Shutdown();
		pScheduler.Adopt(nullptr);
	}
}
