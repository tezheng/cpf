//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Detail/Ref32x4_2.hpp"
#include "SIMD/Detail/Ref32x4_3.hpp"

// TODO: This is a temporary test.

namespace Cpf
{
	namespace Math
	{
		template <typename TYPE>
		union Vector3v
		{
			using Storage = typename TYPE::Type;
			using Element = typename TYPE::Element;

			Vector3v() {}
			Vector3v(typename TYPE::Element value)
				: mVector(value)
			{}
			Vector3v(Element v0, Element v1, Element v2)
				: mVector(v0, v1, v2)
			{}

			template <int I0, int I1, int I2>
			Vector3v(Cpf::SIMD::Ref32x4_3<TYPE, I0, I1, I2>& ref) : mVector(ref) {}

			explicit operator Storage () const { return static_cast<Storage>(mVector); }

			TYPE mVector;

			REF32X4_1_SWIZZLE(TYPE);
			REF32X4_2_SWIZZLE(TYPE);
			REF32X4_3_SWIZZLE(TYPE);
		};
	}
}
