//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class TopologyType : int32_t
		{
			eUndefined = 0,
			ePoint,
			eLine,
			eTriangle,
			ePatch,
			eCount
		};
	}
}
