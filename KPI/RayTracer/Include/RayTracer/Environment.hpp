//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RayTracer/RayTracer.hpp"

// Forward reference.
class JSONValue;

namespace RayTracer
{
	class Scene;

	class CPF_ALIGN(16) Environment
	{
	public:
		enum class EnvironmentType : uint32_t
		{
			Solid,
			Gradient,
			Spherical,
			Cubic
		};

		Environment();

		bool					Parse( Scene& s, JSONValue* v );
		Vector4					Color( const Ray3& r );

	private:
		//
		EnvironmentType			mType;
		Vector4					mColor;
	};
}
