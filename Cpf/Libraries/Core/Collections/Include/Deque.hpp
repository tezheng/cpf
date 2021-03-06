//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#ifdef CPF_USE_EASTL
#	include "EASTL/deque.h"
#else
#	include <deque>
#endif

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	template<typename T>
	using Deque = CPF_STL_NAMESPACE::deque<T>;
}
