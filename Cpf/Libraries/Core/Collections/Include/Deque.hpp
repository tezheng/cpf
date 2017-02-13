//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/deque.h"
#else
#	include <deque>
#endif

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename T>
	using Deque = CPF_STL_NAMESPACE::deque<T>;
}