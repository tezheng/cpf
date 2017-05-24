//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iKeyboardDevice.hpp"

namespace Cpf
{
	namespace SDL2
	{
		class KeyboardDevice : public tRefCounted<iKeyboardDevice>
		{
		public:
			KeyboardDevice(GOM::iBase*);
			virtual ~KeyboardDevice();

			GOM::Result CPF_STDCALL Cast(GOM::InterfaceID id, void** outIface) override;

			GOM::Result CPF_STDCALL GetModifiers(KeyModifier*) override;
		};
	}
}
