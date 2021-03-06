//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iApplicationMain.hpp"
#include "CPF/Application/iWindowedApplication.hpp"
#include "Application/iWindow.hpp"
#include "Graphics.hpp"
#include "Concurrency/iScheduler.hpp"
#include "Resources/iLocator.hpp"
#include "EntityService/Interfaces/iManager.hpp"
#include "Threading/Reactor.hpp"
#include "iDebugUI.hpp"
#include "MultiCore/iExecutionPlan.hpp"
#include "MovementSystem.hpp"
#include "CPF/Graphics/iImage.hpp"
#include "CPF/Graphics/iImageView.hpp"
#include "CPF/Graphics/iFrameBuffer.hpp"
#include "CPF/Graphics/iRenderPass.hpp"
#include <atomic>

//
namespace CPF
{
	class ExperimentalD3D12 : public tRefCounted<iApplicationMain>
	{
	public:
		ExperimentalD3D12()
			: mFenceTarget(1)
			, mSelectedInstruction(0)
			, mpInstructionList(nullptr)
			, mInstructionCount(0)
			, mpEntityManager(nullptr)
			, mpRegistry(nullptr)
			, mpApplication(nullptr)
		{}

		GOM::Result CPF_STDCALL QueryInterface(uint64_t, void**) override { return GOM::kNotImplemented; }

		GOM::Result CPF_STDCALL Initialize(Plugin::iRegistry*, GOM::ClassID* appCid) override;
		GOM::Result CPF_STDCALL Main(iApplication* application) override;
		void CPF_STDCALL Shutdown() override;

		Plugin::iRegistry* GetRegistry() { return mpRegistry; }

		static const int32_t kInstancesPerDimension = 50;
		static const int32_t kInstanceCount = kInstancesPerDimension*kInstancesPerDimension*kInstancesPerDimension;

		Graphics::iVertexBuffer* GetCurrentInstanceBuffer() const { return mpInstanceBuffer[mCurrentBackbuffer]; }

		void ReconfigurePipeline();

		// Moving to a render system.
		void _BeginFrame(const Concurrency::WorkContext*);
		void _Draw(const Concurrency::WorkContext*);
		void _DebugUI(const Concurrency::WorkContext*);
		void _EndFrame(const Concurrency::WorkContext*);

	private:
		bool _CreateWindow();
		void _CreateWorkerData(const Concurrency::WorkContext* tc);
		void _DestroyWorkerData(const Concurrency::WorkContext* tc);

		bool _SelectAdapter(Graphics::iInstance* instance, Graphics::iAdapter**);
		bool _EnumerateOutputs(Graphics::iAdapter*);
		bool _CreateSwapChain(Graphics::iInstance* instance);

		bool _CreateResources();
		void _DestroyResources();

		void _Resize(int32_t x, int32_t y);

		void _UpdatePipelineDisplay();

		IntrusivePtr<Resources::iLocator> mpLocator;

		static const int32_t mBackBufferCount = 3;

		IntrusivePtr<iWindow> mpWindow;
		IntrusivePtr<Graphics::iDevice> mpDevice;
		IntrusivePtr<Graphics::iSwapChain> mpSwapChain;
		IntrusivePtr<Graphics::iRenderPass> mpRenderPass;
		Vector<IntrusivePtr<Graphics::iFrameBuffer>> mpFrameBuffers;
		IntrusivePtr<Graphics::iImage> mpDepthBuffer;
		IntrusivePtr<Graphics::iImageView> mpDepthBufferView;
		IntrusivePtr<Graphics::iResourceBinding> mpResourceBinding;
		IntrusivePtr<Graphics::iConstantBuffer> mpViewProj;
		IntrusivePtr<Graphics::iShader> mpVertexShader;
		IntrusivePtr<Graphics::iShader> mpPixelShader;

		IntrusivePtr<Graphics::iVertexBuffer> mpVertexBuffer;
		IntrusivePtr<Graphics::iVertexBuffer> mpInstanceBuffer[mBackBufferCount];
		IntrusivePtr<Graphics::iIndexBuffer> mpIndexBuffer;

		IntrusivePtr<Graphics::iCommandPool> mpPreCommandPool[mBackBufferCount];
		IntrusivePtr<Graphics::iCommandBuffer> mpPreCommandBuffer[mBackBufferCount];
		IntrusivePtr<Graphics::iPipeline> mpPipeline;
		IntrusivePtr<Graphics::iFence> mpFence;
		IntrusivePtr<Concurrency::iScheduler> mpScheduler;

		std::atomic<int32_t> mCurrentScheduledBuffer = 0;
		Graphics::iCommandBuffer* mpScheduledBuffers[Concurrency::kMaxThreads * 4];

		std::atomic<int32_t> mCurrentBackbuffer = 0;
		std::atomic<uint64_t> mFenceTarget = 1;
		std::atomic<uint64_t> mFrameIndex = 0;
		std::atomic<uint64_t> mSubmissionIndex = 0;

		Time::Value mStartTime;
		Time::Value mCurrentTime;
		Time::Value mDeltaTime;

		float mFOV;
		float mViewportSize;
		float mAspectRatio;

		//
		IntrusivePtr<MultiCore::iExecutionPlan> mpMultiCore;

		// Per thread data.
		struct ThreadData
		{
			IntrusivePtr<Graphics::iCommandPool> mpCommandPool[mBackBufferCount];
			IntrusivePtr<Graphics::iCommandBuffer> mpCommandBuffer[mBackBufferCount];
			IntrusivePtr<Graphics::iCommandPool> mpDebugUIPool[mBackBufferCount];
			IntrusivePtr<Graphics::iCommandBuffer> mpDebugUIBuffer[mBackBufferCount];
		};
		ThreadData mWorkerData[Concurrency::kMaxThreads];

		/* Not used right now.
		struct ModelTransform
		{
			Math::Matrix33fv mOrientation;
			Math::Vector3fv mScale;
			Math::Vector3fv mTranslation;
		};
		IntrusivePtr<Graphics::iConstantBuffer> mpModelTransform;
		*/

		Threading::Reactor mReactor;
		// If the multi-core side of things needs anything run on the main thread,
		// feed it in this queue.
		Threading::Reactor::WorkQueue mReactorQueue;
		IntrusivePtr<EntityService::iManager> mpEntityManager;

		IntrusivePtr<Graphics::iDebugUI> mpDebugUI;

		int mSelectedInstruction;
		char** mpInstructionList;
		int mInstructionCount;

		bool mThreadCountChanged;
		int32_t mThreadCount;

		//////////////////////////////////////////////////////////////////////////
		IntrusivePtr<MoverSystem> mpMoverSystem;

		Plugin::iRegistry* mpRegistry;
		iWindowedApplication* mpApplication;
	};
}
