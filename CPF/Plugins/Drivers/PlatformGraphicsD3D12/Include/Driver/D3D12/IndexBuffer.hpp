//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Platform/Graphics/iIndexBuffer.hpp"
#include "Driver/D3D12/D3D12Utils.hpp"
#include "CPF/IntrusivePtr.hpp"
#include "CPF/GOM/tUnknown.hpp"

namespace CPF
{
	namespace Graphics
	{
		enum class HeapType : int32_t;
		struct ResourceDesc;
	}

	namespace Driver
	{
		namespace D3D12
		{
			class Device;

			class IndexBuffer final : public GOM::tUnknown<Graphics::iIndexBuffer>
			{
			public:
				IndexBuffer(Device* device, const Graphics::ResourceDesc* desc, Graphics::Format format);
				virtual ~IndexBuffer();

				GOM::Result QueryInterface(GOM::IID id, void** outIface) override;

				bool Map(void**, const Graphics::Range* = nullptr) override;
				void Unmap(const Graphics::Range* range) override;

				ID3D12Resource* GetResource() const;
				const D3D12_INDEX_BUFFER_VIEW* GetView() const;

			private:
				IntrusivePtr<ID3D12Resource> mpResource;
				D3D12_INDEX_BUFFER_VIEW mView;
				size_t mSize;
			};
		}
	}
}
