//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iInstance.hpp"
#include "Plugin/iRegistry.hpp"
#include "IntrusivePtr.hpp"
#include "D3D12Utils.hpp"

#define CPF_D3D12_DEBUG_LAYER 1
#if defined(CPF_DEBUG) || CPF_D3D12_DEBUG_LAYER
#	define CPF_USE_D3D12_DEBUG_LAYER
#endif

namespace Cpf
{
	class iWindow;

	namespace Graphics
	{
		struct iDevice;
		struct iAdapter;
		struct iSwapChain;

		struct SwapChainDesc;
	}
	namespace Adapter
	{
		namespace D3D12
		{
			//////////////////////////////////////////////////////////////////////////
			static constexpr Cpf::GOM::ClassID kD3D12InstanceCID = Cpf::GOM::ClassID("Adapter::D3D12::iInstance"_crc64);

			//////////////////////////////////////////////////////////////////////////
			struct Instance : tRefCounted<Graphics::iInstance>
			{
				Instance(GOM::iBase*);
				virtual ~Instance();

				GOM::Result CPF_STDCALL Cast(GOM::InterfaceID id, void** outIface) override;

				GOM::Result CPF_STDCALL EnumerateAdapters(int& count, Graphics::iAdapter** adapters) override;
				GOM::Result CPF_STDCALL CreateDevice(Graphics::iAdapter* adapter, Graphics::iDevice**) override;

				//
				IDXGIFactory2* GetFactory() const { return mpDXGIFactory2; }

			private:
				IntrusivePtr<IDXGIFactory2> mpDXGIFactory2;

#ifdef CPF_USE_D3D12_DEBUG_LAYER
				IntrusivePtr<ID3D12Debug> mpDebugController;
#endif
			};
		}
	}
}
