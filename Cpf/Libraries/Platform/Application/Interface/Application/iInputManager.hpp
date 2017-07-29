//////////////////////////////////////////////////////////////////////////
#pragma once
#include "GOM/iUnknown.hpp"
#include "Events/Emitter.hpp"

namespace Cpf
{
	struct iInputDevice;

	struct iInputManager : GOM::iUnknown
	{
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::iInputManager"_crc64);

		using OnDeviceAttached = Events::Event<"OnDeviceAttached"_crc32, std::function<void()>>;
		using OnDeviceDetached = Events::Event<"OnDeviceDetached"_crc32, std::function<void()>>;

		using EnumCallback = bool(*)(void*, iInputDevice*);

		virtual Events::Emitter* CPF_STDCALL GetEmiter() = 0;
		virtual GOM::Result CPF_STDCALL EnumerateDevices(EnumCallback, void*) = 0;
		virtual GOM::Result CPF_STDCALL GetDevice(uint64_t, uint64_t, void**) = 0;
	};
}
