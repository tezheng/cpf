//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include <d3d12.h>
#include <dxgi1_5.h>
#include <d3dcommon.h>
#include <D3Dcompiler.h>
#include <d3d12sdklayers.h>
#include "Adapter/D3D12/d3dx12.h"
#include "CPF/Graphics/Format.hpp"
#include "CPF/Graphics/iOutput.hpp"
#include "CPF/Graphics/iSwapChain.hpp"
#include "CPF/Graphics/iCommandBuffer.hpp"

#define SAFE_RELEASE(a) {if (a) a->Release();}


namespace CPF
{
	namespace Graphics
	{
		enum class ModeScaling : int32_t;
		enum class ScanlineOrder : int32_t;
		struct ResourceBindingDesc;
	}
	namespace Adapter
	{
		namespace D3D12
		{
			DXGI_FORMAT Convert(Graphics::Format pf);
			Graphics::Format Convert(DXGI_FORMAT pf);
			Graphics::ScanlineOrder Convert(DXGI_MODE_SCANLINE_ORDER order);
			Graphics::ModeScaling Convert(DXGI_MODE_SCALING scaling);
			DXGI_SWAP_EFFECT Convert(Graphics::SwapEffect swapEffect);
			D3D12_RESOURCE_STATES Convert(Graphics::ResourceState resourceState);
			UINT Convert(Graphics::SubResource sr);
			UINT ConvertEnumMode(Graphics::EnumMode mode);
		}
	}
}
