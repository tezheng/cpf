//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Graphics/iImageView.hpp"
#include "DescriptorManager.hpp"
#include "Move.hpp"

namespace CPF
{
	namespace Graphics
	{
		struct DepthStencilViewDesc;
	}
}

namespace CPF
{
	namespace Adapter
	{
		namespace D3D12
		{
			class Image;

			class ImageView : public tRefCounted<Graphics::iImageView>
			{
			public:
				ImageView(Descriptor&& desc) : mDescriptor(Move(desc)) {}
				ImageView(Device*, Image*, const Graphics::DepthStencilViewDesc*);

				GOM::Result CPF_STDCALL QueryInterface(uint64_t id, void** outIface) override;

				Descriptor& GetDescriptor() { return mDescriptor; }

			private:
				Descriptor mDescriptor;
			};
		}
	}
}
