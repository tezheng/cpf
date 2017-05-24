//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iBase.hpp"

namespace Cpf
{
	struct iClipboard : GOM::iBase
	{
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::iClipboard"_crc64);
		static constexpr GOM::InstanceID kDefault = GOM::InstanceID("Cpf::iClipboard::Default"_crc64);

		virtual GOM::Result CPF_STDCALL GetClipboardText(int32_t*, char*) = 0;
		virtual GOM::Result CPF_STDCALL SetClipboardText(const char*) = 0;
	};
}
