//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/iResource.hpp"
#include "D3D12Utils.hpp"
#include "IntrusivePtr.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class ResourceDesc;
	}

	namespace Adapter
	{
		namespace D3D12
		{
			class Device;

			static constexpr COM::ClassID kResourceCID = COM::ClassID("Adapter::D3D12::Resource"_crc64);

			class Resource : public tRefCounted<Graphics::iResource>
			{
			public:
				Resource(Device* device, const Graphics::ResourceDesc* desc);
				virtual ~Resource();

				COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface) override;

				ID3D12Resource* GetResource() const { return mpResource; }
				D3D12_GPU_VIRTUAL_ADDRESS GetGPUAddress() const;

			private:
				IntrusivePtr<ID3D12Resource> mpResource;
			};
		}
	}
}
