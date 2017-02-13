//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Core/Core.hpp"
#include "eastl/bonus/ring_buffer.h"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	template<typename T>
	using RingBuffer = eastl::ring_buffer<T>;
}
