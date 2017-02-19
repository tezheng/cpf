//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"

//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_GRAPHICS_DRIVER
#		define CPF_EXPORT_GRAPHICS_DRIVER
#	else // CPF_STATIC_GRAPHICS_DRIVER
#		if CPF_BUILD_GRAPHICS_DRIVER
#			define CPF_EXPORT_GRAPHICS_DRIVER CPF_EXPORT
#		else
#			define CPF_EXPORT_GRAPHICS_DRIVER CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_GRAPHICS_DRIVER CPF_EXPORT
#	else
#		define CPF_EXPORT_GRAPHICS_DRIVER
#	endif
#endif // CPF_TARGET_WINDOWS

#include "Graphics/Driver.hpp"

namespace Cpf
{
	namespace Graphics
	{
		CPF_EXPORT_GRAPHICS_DRIVER bool Create(int64_t id, iInstance** instance);
	}
}