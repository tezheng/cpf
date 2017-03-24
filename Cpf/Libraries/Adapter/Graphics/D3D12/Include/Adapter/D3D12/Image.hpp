//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Driver.hpp"
#include "Graphics/Interfaces/iImage.hpp"
#include "Graphics/Interfaces/iImageView.hpp"
#include "D3D12Utils.hpp"
#include "DescriptorManager.hpp"
#include "Move.hpp"

namespace Cpf
{
	namespace Adapter
	{
		namespace D3D12
		{
			class Image : public tRefCounted<Graphics::iImage>
			{
			public:
				Image(ID3D12Resource* resource);
				Image(Device*, const void* initData, const Graphics::ImageDesc* desc CPF_GFX_DEBUG_PARAM_DECL);
				~Image() override;

				const Graphics::ImageDesc& GetDesc() const override;

				ID3D12Resource* GetResource();
				const D3D12_SHADER_RESOURCE_VIEW_DESC* GetResourceViewDesc() const { return &mResourceView; }
				const Descriptor& GetDescriptor() const { return mDescriptor; }

			private:
				IntrusivePtr<ID3D12Resource> mpResource;
				Graphics::ImageDesc mDesc;
				Descriptor mDescriptor;
				D3D12_SHADER_RESOURCE_VIEW_DESC mResourceView;
			};

			class ImageView : public tRefCounted<Graphics::iImageView>
			{
			public:
				ImageView(Descriptor&& desc) : mDescriptor(Move(desc)) {}
				ImageView(Device*, Image*, const Graphics::DepthStencilViewDesc*);

				Descriptor& GetDescriptor() { return mDescriptor; }

			private:
				Descriptor mDescriptor;
			};
		}
	}
}
