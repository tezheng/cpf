//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include "CPF/Outcome.hpp"

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	namespace IO
	{
		//////////////////////////////////////////////////////////////////////////
		class Stream;


		/** @brief Error type enumeration. */
		enum class Error : int64_t
		{
			eNone = 0,
			eUnknownError = -1,
			eOutOfMemory = 1,
			eInvalidFile
		};


		//////////////////////////////////////////////////////////////////////////
		enum class Access : int32_t;
		enum class Origin : int32_t;
	}
}

#include "CPF/IO/Attributes.hpp"
#include "CPF/IO/Access.hpp"
#include "CPF/IO/Origin.hpp"