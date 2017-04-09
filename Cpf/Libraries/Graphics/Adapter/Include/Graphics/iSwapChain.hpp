//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"

namespace Cpf
{
	namespace Graphics
	{
		struct iImage;
		struct iImageView;

		enum class SwapEffect : int32_t;
		struct SwapChainDesc;

		struct iSwapChain : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("Graphics::iSwapChain"_crc64);

			virtual void Present() = 0;
			virtual void Resize(int32_t x, int32_t y) = 0;
			virtual int32_t GetCurrentIndex() = 0;
			virtual iImage* GetImage(int32_t index) = 0;
			virtual iImageView* GetImageView(int32_t index) = 0;
		};
	}
}