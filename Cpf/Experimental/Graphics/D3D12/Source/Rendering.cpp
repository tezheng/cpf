//////////////////////////////////////////////////////////////////////////
#include "ExperimentalD3D12.hpp"
#include "Graphics/TopologyType.hpp"

using namespace Cpf;
using namespace Math;
using namespace Graphics;


void ExperimentalD3D12::_BeginFrame(Concurrency::ThreadContext&)
{
	// Issue on the shared command buffers.
	mpPreCommandPool[mCurrentBackbuffer]->Reset();
	mpPreCommandBuffer[mCurrentBackbuffer]->Reset(mpPreCommandPool[mCurrentBackbuffer]);
	mpPreCommandBuffer[mCurrentBackbuffer]->Begin();

	// TODO: This will move into the render pass abstraction when it is ready.
	mpDevice->BeginFrame(mpPreCommandBuffer[mCurrentBackbuffer]);
}

void ExperimentalD3D12::_ClearBuffers(Concurrency::ThreadContext&)
{
	// Setup the frame.
	int32_t backBuffer = Atomic::Load(mCurrentBackbuffer);

	// Transition the current back buffer and depth buffers to render targets.
	// TODO: This will go away with the render pass abstraction.
	mpPreCommandBuffer[mCurrentBackbuffer]->ImageTransition(
		mpSwapChain->GetImage(backBuffer),
		ResourceState::ePresent,
		ResourceState::eRenderTarget,
		SubResource::eAll);
	mpPreCommandBuffer[mCurrentBackbuffer]->ImageTransition(
		mpDepthBufferImages[backBuffer],
		ResourceState::ePresent,
		ResourceState::eDepthWrite,
		SubResource::eAll
	);

	// Cycle the colors to make sure things are working.
	Color4f color(0.0f, 0.0f, 0.0f, 1.0f);

	// Clear the color and depth buffers.
	iImageView* imageViews[] = { mpSwapChain->GetImageView(mCurrentBackbuffer) };
	mpPreCommandBuffer[mCurrentBackbuffer]->SetRenderTargets(1, imageViews, mpDepthBufferImageViews[backBuffer]);
	mpPreCommandBuffer[mCurrentBackbuffer]->ClearRenderTargetView(mpSwapChain->GetImageView(backBuffer), color, 0, nullptr);
	mpPreCommandBuffer[mCurrentBackbuffer]->ClearDepthStencilView(mpDepthBufferImageViews[backBuffer], DepthStencilClearFlag::eDepth, 1.0f, 0, 0, nullptr);

	// End the command buffer prior to submission.
	mpPreCommandBuffer[mCurrentBackbuffer]->End();

	// Always the first to issue.
	mpScheduledBuffers[0] = mpPreCommandBuffer[mCurrentBackbuffer];
}

void ExperimentalD3D12::_Draw(Concurrency::ThreadContext& tc)
{
	ThreadData& threadData = *reinterpret_cast<ThreadData*>(tc.UserData());

	// Start issuing commands.
	threadData.mpCommandPool[mCurrentBackbuffer]->Reset();
	threadData.mpCommandBuffer[mCurrentBackbuffer]->Reset(threadData.mpCommandPool[mCurrentBackbuffer]);
	threadData.mpCommandBuffer[mCurrentBackbuffer]->Begin();

	//////////////////////////////////////////////////////////////////////////
	/* Do some drawing...
	*/
	int32_t backBuffer = Atomic::Load(mCurrentBackbuffer);
	iImageView* imageViews[] = { mpSwapChain->GetImageView(backBuffer) };
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetRenderTargets(1, imageViews, mpDepthBufferImageViews[backBuffer]);

	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetResourceBinding(mpResourceBinding);
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetPipeline(mpPipeline);

	Viewport viewport{
		0.0f, 0.0f,
		float(mpWindow->GetClientArea().x), float(mpWindow->GetClientArea().y),
		0.0f, 1.0f
	};
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetViewports(1, &viewport);
	Rectanglei scissor(0, mpWindow->GetClientArea().x, 0, mpWindow->GetClientArea().y);
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetScissorRects(1, &scissor);
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetTopology(PrimitiveTopology::eTriangleList);

	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetConstantBuffer(0, mpViewProj);
	iVertexBuffer* vbs[2] = { mpVertexBuffer, mpInstanceBuffer[mCurrentBackbuffer] };
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetVertexBuffers(0, 2, vbs);
	threadData.mpCommandBuffer[mCurrentBackbuffer]->SetIndexBuffer(mpIndexBuffer);

	threadData.mpCommandBuffer[mCurrentBackbuffer]->DrawIndexedInstanced(3, kInstanceCount, 0, 0, 0);

	// End the command buffer prior to submission.
	threadData.mpCommandBuffer[mCurrentBackbuffer]->End();
	mpScheduledBuffers[Atomic::Inc(mCurrentScheduledBuffer) - 1] = threadData.mpCommandBuffer[mCurrentBackbuffer];
}

void ExperimentalD3D12::_PreparePresent(Concurrency::ThreadContext&)
{
	// This is not split out to be parallel with the above as it must always be the last submitted buffer.
	// Issue on the shared command buffers.
	mpPostCommandPool[mCurrentBackbuffer]->Reset();
	mpPostCommandBuffer[mCurrentBackbuffer]->Reset(mpPostCommandPool[mCurrentBackbuffer]);
	mpPostCommandBuffer[mCurrentBackbuffer]->Begin();

	// Transition the back buffer and depth buffer to present.
	int32_t backBuffer = Atomic::Load(mCurrentBackbuffer);
	mpPostCommandBuffer[mCurrentBackbuffer]->ImageTransition(mpSwapChain->GetImage(backBuffer), ResourceState::eRenderTarget, ResourceState::ePresent, SubResource::eAll);
	mpPostCommandBuffer[mCurrentBackbuffer]->ImageTransition(mpDepthBufferImages[backBuffer], ResourceState::eDepthWrite, ResourceState::ePresent, SubResource::eAll);

	// Let the device take care of any final needed work, read backs for instance.
	mpDevice->EndFrame(mpPostCommandBuffer[mCurrentBackbuffer]);

	// End the command buffer prior to submission.
	mpPostCommandBuffer[mCurrentBackbuffer]->End();
}

void ExperimentalD3D12::_EndFrame(Concurrency::ThreadContext&)
{
	// Pick up and add the transition for present.
	int32_t commandBufferCount = Atomic::Inc(mCurrentScheduledBuffer);
	mpScheduledBuffers[commandBufferCount - 1] = mpPostCommandBuffer[mCurrentBackbuffer];

	// Submit the command buffers.
	mpDevice->Submit(commandBufferCount, mpScheduledBuffers);

	// Present the back buffer.
	mpSwapChain->Present();

	// Wait for completion.
	auto fenceToWaitFor = Atomic::Inc(mFenceTarget);
	mpDevice->Signal(mpFence, fenceToWaitFor);

	// TODO: This sure seems like a race condition but it is how all the examples seem to work.
	if (mpFence->GetValue() < fenceToWaitFor)
		mpFence->WaitFor(fenceToWaitFor);

	// TODO: Move into the render passes.
	mpDevice->Finalize();
}
