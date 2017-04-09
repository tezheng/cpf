//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class ModeRotation : int32_t
		{
			eUnspecified,
			eIdentity,
			eRotated90,
			eRotated180,
			eRotated270
		};
	}
}