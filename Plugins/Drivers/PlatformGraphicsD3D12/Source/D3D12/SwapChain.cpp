//////////////////////////////////////////////////////////////////////////
#include "Driver/D3D12/SwapChain.hpp"
#include "Driver/D3D12/Instance.hpp"
#include "Driver/D3D12/Device.hpp"
#include "Driver/D3D12/D3D12Utils.hpp"
#include "Driver/D3D12/Image.hpp"
#include "Driver/D3D12/ImageView.hpp"
#include "CPF/Platform/Graphics/WindowData.hpp"
#include "CPF/GOM/ResultCodes.hpp"
#include "CPF/Logging.hpp"
#include "CPF/Std/Move.hpp"

#ifdef CPF_DEBUG
#pragma comment( lib, "dxguid.lib")
#endif

using namespace CPF;
using namespace Driver;
using namespace D3D12;

SwapChain::SwapChain(
	Instance* instance,
	Graphics::iDevice* device,
	const Graphics::WindowData* windowData,
	int32_t w,
	int32_t h,
	const Graphics::SwapChainDesc* desc
)
	: mpDevice(static_cast<Device*>(device))
	, mDesc(*desc)
{
	if (windowData && instance && instance->GetFactory() && device && mpDevice->GetD3DDevice() && mpDevice->GetD3DQueue())
	{
		HRESULT hr;
		IDXGIFactory2* dxgiFactory = instance->GetFactory();
		ID3D12Device* d3d12Device = mpDevice->GetD3DDevice();
		ID3D12CommandQueue* d3d12CommandQueue = mpDevice->GetD3DQueue();

		DXGI_SWAP_CHAIN_DESC1 sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.Width = w;
		sd.Height = h;
		sd.Format = Convert(mDesc.mFormat);
		sd.SampleDesc.Count = mDesc.mMultiSample.mCount;
		sd.SampleDesc.Quality = mDesc.mMultiSample.mQuality;
		sd.BufferUsage = 0; // Defaults to DXGI_USAGE_RENDER_TARGET_OUTPUT during creation.
		sd.BufferCount = mDesc.mBackBufferCount;
		sd.SwapEffect = Convert(mDesc.mSwapEffect);
		sd.Flags = desc->mVSync ? 0 : DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

		IDXGISwapChain1* tempSwapChain;
		hr = dxgiFactory->CreateSwapChainForHwnd(d3d12CommandQueue, windowData->mHWnd, &sd, nullptr, nullptr, &tempSwapChain);
		if (SUCCEEDED(hr))
		{
			if (SUCCEEDED(tempSwapChain->QueryInterface(__uuidof(IDXGISwapChain), mpSwapChain.AsVoidPP())))
			{
				tempSwapChain->Release();

				if (mDesc.mAllowFullscreen)
					dxgiFactory->MakeWindowAssociation(windowData->mHWnd, 0);
				else
					dxgiFactory->MakeWindowAssociation(windowData->mHWnd, DXGI_MWA_NO_ALT_ENTER);
			}
		}
		else
			return;
		
		// Create backbuffer views.
		mRenderTargets.resize(sd.BufferCount);
		mRenderTargetViews.resize(sd.BufferCount);
		for (UINT i = 0; i < sd.BufferCount; ++i)
		{
			mRenderTargetViews[i].Adopt(new ImageView(STD::Move(mpDevice->GetRenderTargetViewDescriptors().Alloc())));
			ID3D12Resource* rt;
			mpSwapChain->GetBuffer(i, IID_PPV_ARGS(&rt));
			mRenderTargets[i].Adopt(new Image(rt));
			d3d12Device->CreateRenderTargetView(
				mRenderTargets[i].As<Image>()->GetResource(),
				nullptr, 
				mRenderTargetViews[i].As<ImageView>()->GetDescriptor()
				);
		}
	}
	CPF_LOG(D3D12, Info) << "Created swapchain: " << intptr_t(this) << " - " << intptr_t(mpSwapChain.Ptr());
}

SwapChain::~SwapChain()
{
	mRenderTargetViews.clear();
	mRenderTargets.clear();
	if (mpSwapChain)
		mpSwapChain->SetFullscreenState(FALSE, nullptr);
	CPF_LOG(D3D12, Info) << "Destroyed swapchain: " << intptr_t(this) << " - " << intptr_t(mpSwapChain.Ptr());
}

void SwapChain::Present()
{
	mpSwapChain->Present(mDesc.mVSync ? 1 : 0, mDesc.mVSync ? 0 : DXGI_PRESENT_ALLOW_TEARING);
}

void SwapChain::Resize(int32_t x, int32_t y)
{
	// Flush the current frame in order to safely perform the resize.
	IntrusivePtr<Graphics::iFence> fence;
	mpDevice->CreateFence(false, fence.AsTypePP());
	mpDevice->Signal(fence);
	fence->Wait();

	// TODO: Validate that DXGI is taking care of resource synchronization.  Seems to be a safe bet but can't be sure.
	CPF_LOG(D3D12, Info) << "Resizing swap chain to: " << x << "x" << y;
	mRenderTargets.clear();
	mRenderTargetViews.clear();

	if (SUCCEEDED(mpSwapChain->ResizeBuffers(mDesc.mBackBufferCount, x, y, Convert(mDesc.mFormat), mDesc.mVSync ? 0 : DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING)))
	{
		CPF_LOG(D3D12, Info) << "Resizing swap chain succeeded";
		mRenderTargets.resize(mDesc.mBackBufferCount);
		mRenderTargetViews.resize(mDesc.mBackBufferCount);
		for (auto i = 0; i < mDesc.mBackBufferCount; ++i)
		{
			mRenderTargetViews[i].Adopt(new ImageView(STD::Move(mpDevice->GetRenderTargetViewDescriptors().Alloc())));
			ID3D12Resource* rt;
			mpSwapChain->GetBuffer(i, IID_PPV_ARGS(&rt));
			mRenderTargets[i].Adopt(new Image(rt));
			mpDevice->GetD3DDevice()->CreateRenderTargetView(mRenderTargets[i].As<Image>()->GetResource(), nullptr, 
				mRenderTargetViews[i].As<ImageView>()->GetDescriptor()
				);
		}
	}
}

int32_t SwapChain::GetCurrentIndex()
{
	return mpSwapChain->GetCurrentBackBufferIndex();
}

Graphics::iImage* SwapChain::GetImage(int32_t index)
{
	return mRenderTargets[index];
}

Graphics::iImageView* SwapChain::GetImageView(int32_t index)
{
	return mRenderTargetViews[index];
}
