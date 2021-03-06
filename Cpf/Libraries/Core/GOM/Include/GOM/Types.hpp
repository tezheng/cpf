//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Hash/HashID.hpp"

namespace CPF
{
	namespace GOM
	{
		using ClassID = Hash::HashID<uint64_t, struct class_tag>;
		using InterfaceID = Hash::HashID<uint64_t, struct interface_tag>;
		using InstanceID = Hash::HashID<uint64_t, struct instance_tag>;
	}
}
