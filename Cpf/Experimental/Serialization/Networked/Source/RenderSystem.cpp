//////////////////////////////////////////////////////////////////////////
#include "RenderSystem.hpp"
#include "Graphics.hpp"
#include "MultiCore/iStage.hpp"
#include "MultiCore/iPipeline.hpp"
#include "Application/Application.hpp"
#include "Application/Window.hpp"

using namespace Cpf;
using namespace MultiCore;
using namespace Graphics;

bool RenderSystem::Install()
{
	return System::Install(kID, &RenderSystem::_Create);
}

bool RenderSystem::Remove()
{
	return System::Remove(kID);
}

COM::Result RenderSystem::Configure()
{
	mpTimer = GetSystem<iTimer>(GetOwner(), mDesc.mTimer.GetString());
	return mpTimer != nullptr ? COM::kOK : COM::kInvalid;
}

bool RenderSystem::Initialize(iWindow* window, Resources::Locator* locator)
{
	if (Graphics::Create(1, mpInstance.AsTypePP()))
	{
		if (_SelectAdapter() &&
			mpInstance->CreateDevice(mpAdapter, mpDevice.AsTypePP()) &&
			_CreateSwapChain(window) &&
			_CreateRenderData(window, locator)
			)
		{
			mpDebugUI->SetWindowSize(window->GetClientArea().x, window->GetClientArea().y);
			_CreateStages();
			return true;
		}
	}
	return false;
}

bool RenderSystem::Shutdown()
{
	for (int i = 0; i < kBufferCount; ++i)
	{
		mpPreCommandPool[i].Adopt(nullptr);
		mpPreCommandBuffer[i].Adopt(nullptr);
		mpPostCommandPool[i].Adopt(nullptr);
		mpPostCommandBuffer[i].Adopt(nullptr);
		mpDebugUIPool[i].Adopt(nullptr);
		mpDebugUIBuffer[i].Adopt(nullptr);
	}
	mpFence.Adopt(nullptr);

	mpDepthBufferImages.clear();
	mpDepthBufferImageViews.clear();

	mpDebugUI.Adopt(nullptr);
	mpSwapChain.Adopt(nullptr);
	mpDevice.Adopt(nullptr);
	mpAdapter.Adopt(nullptr);
	mpInstance.Adopt(nullptr);
	return true;
}

void RenderSystem::Resize(int32_t w, int32_t h)
{
	mpSwapChain->Resize(w, h);
	if (mpDebugUI)
		mpDebugUI->SetWindowSize(w, h);
}

DebugUI& RenderSystem::GetDebugUI()
{
	return *mpDebugUI;
}


RenderSystem::RenderSystem(Plugin::iRegistry* rgy, MultiCore::iPipeline* pipeline, const char* name, const Desc* desc)
	: mpTimer(nullptr)
	, mDesc(*desc)
	, mpRegistry(rgy)
{
	System::Initialize(rgy, pipeline, name);
}

RenderSystem::~RenderSystem()
{}

iSystem* RenderSystem::_Create(Plugin::iRegistry* rgy, MultiCore::iPipeline* owner, const char* name, const System::Desc* desc)
{
	return new RenderSystem(rgy, owner, name, reinterpret_cast<const Desc*>(desc));
}

void RenderSystem::_CreateStages()
{
	IntrusivePtr<iSingleUpdateStage> beginFrame;
	mpRegistry->Create(nullptr, MultiCore::kSingleUpdateStageCID, MultiCore::iSingleUpdateStage::kIID, beginFrame.AsVoidPP());
	beginFrame->Initialize(this, "Begin Frame");
	beginFrame->SetUpdate(&RenderSystem::_BeginFrame, this, BlockOpcode::eFirst);
	AddStage(beginFrame);

	IntrusivePtr<iSingleUpdateStage> debugUI;
	mpRegistry->Create(nullptr, MultiCore::kSingleUpdateStageCID, MultiCore::iSingleUpdateStage::kIID, debugUI.AsVoidPP());
	debugUI->Initialize(this, "DebugUI");
	debugUI->SetUpdate(&RenderSystem::_DebugUI, this, BlockOpcode::eLast);
	AddStage(debugUI);

	IntrusivePtr<iSingleUpdateStage> endFrame;
	mpRegistry->Create(nullptr, MultiCore::kSingleUpdateStageCID, MultiCore::iSingleUpdateStage::kIID, endFrame.AsVoidPP());
	endFrame->Initialize(this, "End Frame");
	endFrame->SetUpdate(&RenderSystem::_EndFrame, this, BlockOpcode::eLast);
	AddStage(endFrame);

	//////////////////////////////////////////////////////////////////////////
	AddDependency({
		{GetID(), endFrame->GetID(), iStage::kExecute},
		{GetID(), beginFrame->GetID(), iStage::kExecute},
		DependencyPolicy::eAfter
	});

	AddDependency({
		{ GetID(), debugUI->GetID(), iStage::kExecute },
		{ GetID(), beginFrame->GetID(), iStage::kExecute },
		DependencyPolicy::eAfter
	});
	AddDependency({
		{ GetID(), endFrame->GetID(), iStage::kExecute },
		{ GetID(), debugUI->GetID(), iStage::kExecute },
		DependencyPolicy::eBarrier
	});
}

bool RenderSystem::_SelectAdapter()
{
	// Enumerate the graphics adapters attached to the system.
	int adapterCount = 0;
	mpInstance->EnumerateAdapters(adapterCount, nullptr);
	Vector<IntrusivePtr<iAdapter>> adapters;
	adapters.resize(adapterCount);
	mpInstance->EnumerateAdapters(adapterCount, adapters[0].AsTypePP());

	int bestAdapter = -1;
	for (int i = 0; i < adapterCount; ++i)
	{
		if (adapters[i]->IsSoftware() || adapters[i]->IsRemote())
			continue;
		bestAdapter = i;
		mpAdapter.Adopt(adapters[bestAdapter]);
		mpAdapter->AddRef();
		break;
	}

	return bestAdapter != -1;
}

bool RenderSystem::_CreateSwapChain(iWindow* window)
{
	// Create the swapchain attached to the window.
	SwapChainDesc desc{
		Format::eRGBA8un,
		SwapEffect::eFlipDiscard,
		{ 1, 0 },
		kBufferCount,
		true
	};
	mpDevice->CreateSwapChain(mpInstance, window, &desc, mpSwapChain.AsTypePP() CPF_GFX_DEBUG_PARAMS);

	// Create a set of depth buffers to go with the swap chain.
	mpDepthBufferImages.resize(desc.mBackBufferCount);
	mpDepthBufferImageViews.resize(desc.mBackBufferCount);
	ImageDesc depthBufferDesc
	{
		window->GetClientArea().x, window->GetClientArea().y,
		1,
		1,
		Format::eD32f,
		{ 1, 0 },
		ImageFlags::eAllowDepthStencil
	};
	for (int i = 0; i < desc.mBackBufferCount; ++i)
	{
		mpDevice->CreateImage2D(&depthBufferDesc, nullptr, mpDepthBufferImages[i].AsTypePP());
		mpDevice->CreateDepthStencilView(mpDepthBufferImages[i], nullptr, mpDepthBufferImageViews[i].AsTypePP());
	}

	return mpSwapChain;
}

bool RenderSystem::_CreateRenderData(iWindow* window, Resources::Locator* locator)
{
	mpDevice->CreateFence(3, mpFence.AsTypePP() CPF_GFX_DEBUG_PARAMS);
	for (int i = 0; i < kBufferCount; ++i)
	{
		mpDevice->CreateCommandPool(mpPreCommandPool[i].AsTypePP() CPF_GFX_DEBUG_PARAMS);
		mpDevice->CreateCommandPool(mpPostCommandPool[i].AsTypePP() CPF_GFX_DEBUG_PARAMS);
		mpDevice->CreateCommandBuffer(mpPreCommandPool[i], mpPreCommandBuffer[i].AsTypePP() CPF_GFX_DEBUG_PARAMS);
		mpDevice->CreateCommandBuffer(mpPostCommandPool[i], mpPostCommandBuffer[i].AsTypePP() CPF_GFX_DEBUG_PARAMS);
		mpDevice->CreateCommandPool(mpDebugUIPool[i].AsTypePP() CPF_GFX_DEBUG_PARAMS);
		mpDevice->CreateCommandBuffer(mpDebugUIPool[i], mpDebugUIBuffer[i].AsTypePP() CPF_GFX_DEBUG_PARAMS);
	}
	mpDebugUI.Adopt(new DebugUI());
	mpDebugUI->Initialize(mpDevice, window, locator);
	return true;
}

void RenderSystem::_BeginFrame(Concurrency::ThreadContext&, void* context)
{
	RenderSystem& self = *reinterpret_cast<RenderSystem*>(context);

	// Manage indexing.
	self.mScheduleIndex = 1;	// Skips 0, we'll be filling that in ourselves.
	self.mBufferIndex = (self.mBufferIndex + 1) % kBufferCount;
	self.mSwapIndex = self.mpSwapChain->GetCurrentIndex();

	// Can only have 3 frames outstanding at a time so hang out here if we get too far ahead.
	auto lastFence = self.mFenceTarget;
	if (lastFence - self.mpFence->GetValue() >= kBufferCount)
		self.mpFence->WaitFor(lastFence - (kBufferCount - 1));

	// Issue on the shared command buffers.
	self.mpPreCommandPool[self.mBufferIndex]->Reset();
	self.mpPreCommandBuffer[self.mBufferIndex]->Reset(self.mpPreCommandPool[self.mBufferIndex]);
	self.mpPreCommandBuffer[self.mBufferIndex]->Begin();

	// TODO: This will move into the render pass abstraction when it is ready.
	self.mpDevice->BeginFrame(self.mpPreCommandBuffer[self.mBufferIndex]);

	// Transition the current back buffer and depth buffers to render targets.
	// TODO: This will go away with the render pass abstraction.
	self.mpPreCommandBuffer[self.mBufferIndex]->ImageTransition(
		self.mpSwapChain->GetImage(self.mSwapIndex),
		ResourceState::ePresent,
		ResourceState::eRenderTarget,
		SubResource::eAll);

	// Cycle the colors to make sure things are working.
	Math::Vector4fv color(0.0f, 0.0f, 0.0f, 1.0f);

	// Clear the color and depth buffers.
	self.mpPreCommandBuffer[self.mBufferIndex]->ClearRenderTargetView(self.mpSwapChain->GetImageView(self.mSwapIndex), color, 0, nullptr);

	// End the command buffer prior to submission.
	self.mpPreCommandBuffer[self.mBufferIndex]->End();

	// Always the first to issue.
	self.mpScheduledBuffers[0] = self.mpPreCommandBuffer[self.mBufferIndex];
}

void RenderSystem::_DebugUI(Concurrency::ThreadContext&, void* context)
{
	RenderSystem& self = *reinterpret_cast<RenderSystem*>(context);
	float deltaTime = self.mpTimer->GetDeltaTime();

	self.mpDebugUIPool[self.mBufferIndex]->Reset();
	self.mpDebugUIBuffer[self.mBufferIndex]->Reset(self.mpDebugUIPool[self.mBufferIndex]);
	self.mpDebugUIBuffer[self.mBufferIndex]->Begin();

	iImageView* imageViews[] = { self.mpSwapChain->GetImageView(self.mSwapIndex) };
	self.mpDebugUIBuffer[self.mBufferIndex]->SetRenderTargets(1, imageViews, nullptr);

	self.mpDebugUI->BeginFrame(self.mpDebugUIBuffer[self.mBufferIndex], deltaTime);
	self.mpDebugUI->Execute();
	self.mpDebugUI->EndFrame(self.mpDebugUIBuffer[self.mBufferIndex]);

	self.mpDebugUIBuffer[self.mBufferIndex]->End();
	self.mpScheduledBuffers[Atomic::Inc(self.mScheduleIndex) - 1] = self.mpDebugUIBuffer[self.mBufferIndex];
}

void RenderSystem::_EndFrame(Concurrency::ThreadContext&, void* context)
{
	RenderSystem& self = *reinterpret_cast<RenderSystem*>(context);

	// 
	self.mpPostCommandPool[self.mBufferIndex]->Reset();
	self.mpPostCommandBuffer[self.mBufferIndex]->Reset(self.mpPostCommandPool[self.mBufferIndex]);
	self.mpPostCommandBuffer[self.mBufferIndex]->Begin();

	// Transition the back buffer to present.
	self.mpPostCommandBuffer[self.mBufferIndex]->ImageTransition(self.mpSwapChain->GetImage(self.mSwapIndex), ResourceState::eRenderTarget, ResourceState::ePresent, SubResource::eAll);

	// Let the device take care of any final needed work, read backs for instance.
	self.mpDevice->EndFrame(self.mpPostCommandBuffer[self.mBufferIndex]);

	// End the command buffer prior to submission.
	self.mpPostCommandBuffer[self.mBufferIndex]->End();

	// Pick up and add the transition for present.
	int32_t commandBufferCount = Atomic::Inc(self.mScheduleIndex);
	self.mpScheduledBuffers[commandBufferCount - 1] = self.mpPostCommandBuffer[self.mBufferIndex];

	// Submit the command buffers.
	self.mpDevice->Submit(commandBufferCount, self.mpScheduledBuffers);

	// Present the back buffer.
	self.mpSwapChain->Present();

	// Wait for completion.
	auto fenceToWaitFor = Atomic::Inc(self.mFenceTarget);
	self.mpDevice->Signal(self.mpFence, fenceToWaitFor);

	// TODO: Move into the render passes.
	self.mpDevice->Finalize();
}
