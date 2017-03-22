//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Math/Quaternion.hpp"

namespace Cpf
{
	namespace Math
	{
		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE>::Matrix33()
		{}

		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE>::Matrix33(Element v0)
			: mRows{ Row(v0), Row(v0), Row(v0) }
		{}

		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE>::Matrix33(Row r0, Row r1, Row r2)
			: mRows{ r0, r1, r2 }
		{}

		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE>::Matrix33(
				Element _00, Element _01, Element _02,
				Element _10, Element _11, Element _12,
				Element _20, Element _21, Element _22
			)
			: mRows{ Row{ _00, _01, _02 }, Row{ _10, _11, _12 }, Row{ _20, _21, _22 } }
		{}

		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE>::Matrix33(Quaternion<typename TYPE::Lanes_4> value)
		{
			Element x2 = q.x + q.x;  Element y2 = q.y + q.y;  Element z2 = q.z + q.z;
			Element xx = q.x * x2;   Element xy = q.x * y2;   Element xz = q.x * z2;
			Element yy = q.y * y2;   Element yz = q.y * z2;   Element zz = q.z * z2;
			Element wx = q.w * x2;   Element wy = q.w * y2;   Element wz = q.w * z2;

			mRows[0] = Row(Element(1) - (yy + zz), xy + wz, xz - wy);
			mRows[1] = Row(xy - wz, Element(1) - (xx + zz), yz + wx);
			mRows[2] = Row(xz + wy, yz - wx, Element(1) - (xx + yy));
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE>& CPF_VECTORCALL Matrix33<TYPE>::operator = (const Matrix33<TYPE>& rhs)
		{
			mRows[0] = rhs.mRows[0];
			mRows[1] = rhs.mRows[1];
			mRows[2] = rhs.mRows[2];
			return *this;
		}

		template <typename TYPE> CPF_FORCE_INLINE
			typename Matrix33<TYPE>::Row& CPF_VECTORCALL Matrix33<TYPE>::operator [](int idx)
		{
			return mRows[idx];
		}
		template <typename TYPE> CPF_FORCE_INLINE
			const typename Matrix33<TYPE>::Row& CPF_VECTORCALL Matrix33<TYPE>::operator [](int idx) const
		{
			return mRows[idx];
		}

		template <typename TYPE>
			Matrix33<TYPE> CPF_VECTORCALL operator * (const Matrix33<TYPE>& lhs, const Matrix33<TYPE>& rhs)
		{
			Matrix33<TYPE> result(typename Matrix33<TYPE>::Element(0));
			for (int r = 0; r < 3; ++r)
			{
				for (int c = 0; c < 3; ++c)
				{
					for (int i = 0; i < 3; ++i)
						result[r][c] = result[r][c] + lhs[r][i] * rhs[i][c];
				}
			}
			return result;
		}

		//////////////////////////////////////////////////////////////////////////
		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::Identity()
		{
			return Matrix33<TYPE>(
				Element(1), Element(0), Element(0),
				Element(0), Element(1), Element(0),
				Element(0), Element(0), Element(1)
				);
		}

		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::AxisAngle(Row axis, Element radians)
		{
			CPF_ASSERT(MagnitudeSq(axis) > Element(0.0001));
			Row a = Normalize(axis);
			Element ca = std::cos(radians);
			Element sa = std::sin(radians);

			Element omc = 1 - ca;
			Element xx = a.x*a.x;
			Element xy = a.x*a.y;
			Element xz = a.x*a.z;
			Element yy = a.y*a.y;
			Element yz = a.y*a.z;
			Element zz = a.z*a.z;

			return Matrix33<TYPE>(
				ca + xx * omc, xy * omc + a.z * sa, xz * omc - a.y * sa,
				xy * omc - a.z * sa, ca + yy * omc, yz * omc + a.x * sa,
				xz * omc + a.y * sa, yz * omc - a.x * sa, ca + zz * omc
				);
		}

		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::RotationX(Element radians)
		{
			Element sa = std::sin(radians);
			Element ca = std::cos(radians);

			return Matrix33<TYPE>(
				1, 0, 0,
				0, ca, sa,
				0, -sa, ca
				);
		}

		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::RotationY(Element radians)
		{
			Element sa = std::sin(radians);
			Element ca = std::cos(radians);

			return Matrix33<TYPE>(
				ca, 0, -sa,
				0, 1, 0,
				sa, 0, ca
				);
		}

		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::RotationZ(Element radians)
		{
			Element sa = std::sin(radians);
			Element ca = std::cos(radians);

			return Matrix33v<TYPE>(
				ca, sa, 0,
				-sa, ca, 0,
				0, 0, 1
				);
		}

		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::Scale(Element x, Element y)
		{
			using Element = typename TYPE::Element;
			return Matrix33<TYPE>(
				Element(x), Element(0), Element(0),
				Element(0), Element(y), Element(0),
				Element(0), Element(0), Element(1)
				);
		}

		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE> CPF_VECTORCALL Matrix33<TYPE>::Translation(Element x, Element y)
		{
			using Element = typename TYPE::Element;
			return Matrix33<TYPE>(
				Element(1), Element(0), Element(0),
				Element(0), Element(1), Element(0),
				Element(x), Element(y), Element(1)
				);
		}

		template <typename TYPE> CPF_FORCE_INLINE
			Matrix33<TYPE> CPF_VECTORCALL Transpose(const Matrix33<TYPE> value)
		{
			Matrix33<TYPE> result;
			for (int r = 0; r < 3; ++r)
			{
				typename Matrix33<TYPE>::Row column(value[0][r], value[1][r], value[2][r]);
				result[r] = column;
			}
			return result;
		}

		template <typename TYPE> CPF_FORCE_INLINE
			bool CPF_VECTORCALL Near(const Matrix33<TYPE> lhs, const Matrix33<TYPE> rhs, typename Matrix33<TYPE>::Element tolerance)
		{
			return Near(lhs[0], rhs[0], tolerance) && Near(lhs[1], rhs[1], tolerance) && Near(lhs[2], rhs[2], tolerance);
		}
	}
}
