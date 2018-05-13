//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iConstantBuffer.hpp"
#include "CPF/iRefCounted.hpp"
#include "Resource.hpp"
#include "DescriptorManager.hpp"
#include "CommandBuffer.hpp"


namespace CPF
{
	namespace Driver
	{
		namespace D3D12
		{
			class Device;

			class ConstantBuffer final : public GOM::tUnknown<Graphics::iConstantBuffer>
			{
			public:
				ConstantBuffer(Device* device, const Graphics::ResourceDesc* desc, const void* initData);
				virtual ~ConstantBuffer();

				void Update(size_t offset, size_t size, const void* data) override;

				bool Map(void**, const Graphics::Range* = nullptr) override;
				void Unmap(const Graphics::Range* range) override;

				const Descriptor& GetDescriptor() const { return mDescriptor; }
				D3D12_GPU_VIRTUAL_ADDRESS GetGPUAddress() const { return mpResource->GetGPUVirtualAddress(); }

			private:
				IntrusivePtr<ID3D12Resource> mpResource;
				Descriptor mDescriptor;
				size_t mSize;
				uint8_t* mpBuffer;
			};
		}
	}
}