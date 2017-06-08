//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application/iInputManager.hpp"

namespace Cpf
{
	struct iMouseDevice;
	struct iKeyboardDevice;

	namespace SDL2
	{
		class InputManager : public tRefCounted<iInputManager>
		{
		public:
			InputManager(GOM::iBase*);
			virtual ~InputManager();

			GOM::Result CPF_STDCALL Cast(uint64_t, void**) override;

			Events::Emitter* CPF_STDCALL GetEmiter() override;
			GOM::Result CPF_STDCALL EnumerateDevices(EnumCallback, void*) override;
			GOM::Result CPF_STDCALL GetDevice(uint64_t, uint64_t, void**) override;

		private:
			Events::Emitter mEmitter;
			IntrusivePtr<iMouseDevice> mpMouse;
			IntrusivePtr<iKeyboardDevice> mpKeyboard;
		};
	}
}
