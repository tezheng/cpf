//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Detail/LaneRef.hpp"
#include "SIMD/Detail/LaneIndex.hpp"
#include "SIMD/Detail/Swizzles.hpp"

namespace CPF
{
	namespace Math
	{
		template <typename TYPE>
		union Vector4v
		{
			//////////////////////////////////////////////////////////////////////////
			using StorageType = typename TYPE::StorageType;
			using LaneType = typename TYPE::LaneType;
			static constexpr int LaneMask = TYPE::LaneMask;

			using Lanes_1 = typename TYPE::Lanes_1;
			using Lanes_2 = typename TYPE::Lanes_2;
			using Lanes_3 = typename TYPE::Lanes_3;
			using Lanes_4 = typename TYPE::Lanes_4;

			//////////////////////////////////////////////////////////////////////////
			Vector4v();
			explicit Vector4v(LaneType value);
			explicit Vector4v(TYPE value);
			Vector4v(LaneType v0, LaneType v1, LaneType v2, LaneType v3);
			template <int I0, int I1, int I2, int I3>
			explicit Vector4v(SIMD::LaneRef_4<TYPE, I0, I1, I2, I3>& ref);

			explicit Vector4v(Lanes_2 v01, LaneType v2, LaneType v3);
			explicit Vector4v(LaneType v0, Lanes_2 v12, LaneType v3);
			explicit Vector4v(LaneType v0, LaneType v1, Lanes_2 v23);
			explicit Vector4v(Lanes_2 v01, Lanes_2 v23);

			explicit Vector4v(Lanes_3 v012, LaneType v3);
			explicit Vector4v(LaneType v0, Lanes_3 v123);

			//////////////////////////////////////////////////////////////////////////
			SIMD::LaneIndex<TYPE> CPF_VECTORCALL operator [](int idx);
			LaneType CPF_VECTORCALL operator [](int idx) const;

			//////////////////////////////////////////////////////////////////////////
			Vector4v& CPF_VECTORCALL operator += (const Vector4v& rhs);
			Vector4v& CPF_VECTORCALL operator -= (const Vector4v& rhs);
			Vector4v& CPF_VECTORCALL operator *= (const Vector4v& rhs);
			Vector4v& CPF_VECTORCALL operator *= (LaneType rhs);
			Vector4v& CPF_VECTORCALL operator /= (const Vector4v& rhs);
			Vector4v& CPF_VECTORCALL operator /= (LaneType rhs);

			//////////////////////////////////////////////////////////////////////////
			explicit operator StorageType () const { return static_cast<StorageType>(mSIMD); }

			//////////////////////////////////////////////////////////////////////////
			TYPE mSIMD;
			LANEREF_1_SWIZZLE(TYPE);
			LANEREF_2_SWIZZLE(TYPE);
			LANEREF_3_SWIZZLE(TYPE);
			LANEREF_4_SWIZZLE(TYPE);
		};
	}
}

#include "Math/Detail/Vector4v.inl"
#include "SIMD/Types.hpp"
#include "SIMD/Detail/FPU/F32x4.hpp"

namespace CPF
{
	namespace Math
	{
		using Vector4fv = Vector4v<SIMD::F32x4>;
		using Vector4f = Vector4v<SIMD::FPU::F32x4_4>;
	}
}
