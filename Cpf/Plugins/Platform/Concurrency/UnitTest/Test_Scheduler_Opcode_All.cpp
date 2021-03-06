//////////////////////////////////////////////////////////////////////////
#include "Test_All.hpp"
#include "Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/iFence.hpp"
#include "Concurrency/iScheduler.hpp"
#include "Concurrency/iWorkBuffer.hpp"
#include "Threading/Thread.hpp"
#include <atomic>

TEST_F(ConcurrencyTest, All_Opcode)
{
	//////////////////////////////////////////////////////////////////////////
	using namespace CPF;
	using namespace Concurrency;

	//////////////////////////////////////////////////////////////////////////
	IntrusivePtr<iScheduler> pScheduler;
	EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kSchedulerCID.GetID(), iScheduler::kIID.GetID(), pScheduler.AsVoidPP())));
	EXPECT_TRUE(GOM::Succeeded(pScheduler->Initialize(Threading::Thread::GetHardwareThreadCount(), nullptr, nullptr, nullptr)));

	IntrusivePtr<iFence> pFence;
	EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kFenceCID.GetID(), iFence::kIID.GetID(), pFence.AsVoidPP())));

	IntrusivePtr<iWorkBuffer> pWorkBuffer;
	EXPECT_TRUE(GOM::Succeeded(GetRegistry()->Create(nullptr, kWorkBufferCID.GetID(), iWorkBuffer::kIID.GetID(), pWorkBuffer.AsVoidPP())));

	//////////////////////////////////////////////////////////////////////////
	EXPECT_TRUE(pScheduler->GetMaxThreads() >= 4);

	pScheduler->SetActiveThreads(4);
	{
		//////////////////////////////////////////////////////////////////////////
		std::atomic<int> hitCount = 0;
		for (int i=0; i<25; ++i)
		{
			pWorkBuffer->All( [](const WorkContext*, void* context)
			{
				(*reinterpret_cast<std::atomic<int>*>(context)).fetch_add(1);
			},
				&hitCount);
		}
		pScheduler->Execute(pWorkBuffer);
		pScheduler->Submit(pFence);
		pFence->Wait();
		EXPECT_EQ(4 * 25, hitCount);
	}
	pScheduler->Shutdown();
}
