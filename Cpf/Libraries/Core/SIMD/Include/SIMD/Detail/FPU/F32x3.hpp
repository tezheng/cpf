//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SIMD/Detail/FPU/FPU.hpp"
#include "SIMD/Detail/Ref32x4_1.hpp"
#include "SIMD/Detail/Ref32x4_2.hpp"
#include "SIMD/Detail/Ref32x4_3.hpp"
#include "SIMD/Detail/Ref32x4_4.hpp"

namespace Cpf
{
	namespace SIMD
	{
		namespace FPU
		{
			//////////////////////////////////////////////////////////////////////////
			template<int COUNT>
			struct alignas(4) F32x3<float3, 4, 3, float, COUNT>
			{
				static constexpr int kAlignment = 4;
				using Type = float3;
				static constexpr int kLanes = 3;
				using Element = float;
				static constexpr int kCount = COUNT;
				static constexpr int kLaneMask = (1 << kCount) - 1;

				using Lanes_1 = F32x3<Type, 4, 3, float, 1>;
				using Lanes_2 = F32x3<Type, 4, 3, float, 2>;
				using Lanes_3 = F32x3<Type, 4, 3, float, 3>;

				F32x3() {}
				explicit F32x3(Element value) : mVector{ value, value, value } {}
				template <typename = typename std::enable_if<COUNT == 2, Element>::type>
				F32x3(Element v0, Element v1) : mVector(v0, v1) {}
				template <typename = typename std::enable_if<COUNT == 3, Element>::type>
				F32x3(Element v0, Element v1, Element v2) : mVector(v0, v1, v2) {}

				template <typename = typename std::enable_if<COUNT == 3, Element>::type>
				F32x3(Lanes_2 v01, Element v2)
					: mVector(v01.mVector.mData[0], v01.mVector.mData[1], v2)
				{
				}
				template <typename = typename std::enable_if<COUNT == 3, Element>::type>
				F32x3(Element v0, Lanes_2 v12)
					: mVector(v0, v12.mVector.mData[0], v12.mVector.mData[1])
				{
				}


				explicit constexpr F32x3(Type value) : mVector(value) {}

				F32x3& operator = (Type value) { mVector = value; return *this; }

				explicit operator Type () const { return mVector; }

				template <typename = typename std::enable_if<COUNT == 1, Element>::type>
				operator Lanes_1 () const { return mVector; }
				template <typename = typename std::enable_if<COUNT == 2, Element>::type>
				operator Lanes_2 () const { return mVector; }
				template <typename = typename std::enable_if<COUNT == 3, Element>::type>
				operator Lanes_3 () const { return mVector; }

				template <typename = typename std::enable_if<std::equal_to<int>()(kCount, 1), Element>::type>
				operator const Element() const { return mVector.mData[0]; }

				template <int INDEX>
				Element GetLane() const
				{
					return mVector.mData[INDEX];
				}
				Element GetLane(int index) const
				{
					return mVector.mData[index];
				}
				void SetLane(int index, float value)
				{
					mVector.mData[index] = value;
				}
				template <int I0, int I1>
				Type GetLanes() const
				{
					Type result(mVector.mData[I0], mVector.mData[I1]);
					return result;
				}
				template <int I0, int I1, int I2>
				Type GetLanes() const
				{
					Type result(mVector.mData[I0], mVector.mData[I1], mVector.mData[I2]);
					return result;
				}
				template <int I0, int I1, int I2, int I3>
				Type GetLanes() const
				{
					Type result(mVector.mData[I0], mVector.mData[I1], mVector.mData[I2], mVector.mData[i3]);
					return result;
				}

				Type mVector;
			};

			template<int COUNT>
			using F32x3_ = F32x3<float3, 4, 3, float, COUNT>;

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE typename F32x3_<COUNT> Cross(const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs);

			template <>
			CPF_FORCE_INLINE typename F32x3_<3> Cross(const F32x3_<3> lhs, const F32x3_<3> rhs)
			{
				return F32x3_<3>(
					lhs.mVector.mData[1] * rhs.mVector.mData[2] - rhs.mVector.mData[1] * lhs.mVector.mData[2],
					lhs.mVector.mData[2] * rhs.mVector.mData[0] - rhs.mVector.mData[2] * lhs.mVector.mData[0],
					lhs.mVector.mData[0] * rhs.mVector.mData[1] - rhs.mVector.mData[0] * lhs.mVector.mData[1]);
			}



			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE int operator == (const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] == rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator != (const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] != rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator < (const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] < rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator <= (const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] <= rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator > (const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] > rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE int operator >= (const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				int result = 0;
				for (int i = 0; i < COUNT; ++i)
					if (lhs.mVector.mData[i] >= rhs.mVector.mData[i])
						result |= 1 << i;
				return result;
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> operator - (const F32x3_<COUNT> value)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = -value.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> operator + (const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] + rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> operator - (const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] - rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> operator * (const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] * rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> operator / (const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] / rhs.mVector.mData[i];
				return result;
			}

			//////////////////////////////////////////////////////////////////////////
			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> Min(const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] <= rhs.mVector.mData[i] ? lhs.mVector.mData[i] : rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<1> HMin(const F32x3_<COUNT> value)
			{
				float result = value.mVector.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result < value.mVector.mData[i] ? result : value.mVector.mData[i];
				return F32x3_<1>(result);
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> Max(const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = lhs.mVector.mData[i] >= rhs.mVector.mData[i] ? lhs.mVector.mData[i] : rhs.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<1> HMax(const F32x3_<COUNT> value)
			{
				float result = value.mVector.mData[0];
				for (int i = 1; i < COUNT; ++i)
					result = result >= value.mVector.mData[i] ? result : value.mVector.mData[i];
				return F32x3_<1>(result);
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> Sqrt(const F32x3_<COUNT> value)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::sqrt(value.mVector.mData[i]);
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> Reciprocal(const F32x3_<COUNT> value)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = 1.0f / value.mVector.mData[i];
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> RSqrt(const F32x3_<COUNT> value)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = 1.0f / std::sqrt(value.mVector.mData[i]);
				return result;
			}
			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> Clamp(const F32x3_<COUNT> value, typename F32x3_<COUNT>::Element low, typename F32x3_<COUNT>::Element high)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = (value.mVector.mData[i] <= low) ? low : value.mVector.mData[i] >= high ? high : value.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x3_<COUNT>::Element Dot(const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				typename F32x3_<COUNT>::Element result = 0.0f;
				for (int i = 0; i < COUNT; ++i)
					result += lhs.mVector.mData[i] * rhs.mVector.mData[i];
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x3_<COUNT>::Element Magnitude(const F32x3_<COUNT> value)
			{
				return std::sqrt(Dot(value, value));
			}

			template <int COUNT>
			CPF_FORCE_INLINE typename F32x3_<COUNT>::Element MagnitudeSq(const F32x3_<COUNT> value)
			{
				return Dot(value, value);
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> Normalize(const F32x3_<COUNT> value)
			{
				return value / F32x3_<COUNT>(Magnitude(value));
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> Round(const F32x3_<COUNT> value, Rounding mode)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
				{
					switch (mode)
					{
					case Rounding::eCurrent:
						result.mVector.mData[i] = std::round(value.mVector.mData[i]);
						break;
					case Rounding::eUp:
						result.mVector.mData[i] = std::ceil(value.mVector.mData[i]);
						break;
					case Rounding::eDown:
						result.mVector.mData[i] = std::floor(value.mVector.mData[i]);
						break;
					case Rounding::eTruncate:
					{
						int32_t v = int32_t(value.mVector.mData[i]);
						result.mVector.mData[i] = float(v);
					}
					break;
					case Rounding::eNearest:
						result.mVector.mData[i] = std::round(value.mVector.mData[i]);
						break;
					}
				}
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> Floor(const F32x3_<COUNT> value)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::floor(value.mVector.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> Ceil(const F32x3_<COUNT> value)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::ceil(value.mVector.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> Modulus(const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::fmod(lhs.mVector.mData[i], rhs.mVector.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE F32x3_<COUNT> Abs(const F32x3_<COUNT> value)
			{
				F32x3_<COUNT> result;
				for (int i = 0; i < COUNT; ++i)
					result.mVector.mData[i] = std::abs(value.mVector.mData[i]);
				return result;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool Near(const F32x3_<COUNT> lhs, const F32x3_<COUNT> rhs, float tolerance)
			{
				return (Abs(lhs - rhs) <= F32x3_<COUNT>(tolerance)) == F32x3_<COUNT>::kLaneMask;
			}

			template <int COUNT>
			CPF_FORCE_INLINE bool Valid(const F32x3_<COUNT> value)
			{
				F32x3_<COUNT> test(value * F32x3_<COUNT>{ 0.0f });
				return (test == F32x3_<COUNT>{0.0f}) == F32x3_<COUNT>::kLaneMask;
			}

			//////////////////////////////////////////////////////////////////////////
			using F32x3_3 = F32x3<float3, 4, 3, float, 3>;
		}
	}
}