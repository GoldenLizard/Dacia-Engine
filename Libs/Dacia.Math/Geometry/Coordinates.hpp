#pragma once

#include <Definitions.hpp>
#include "Barycentric.hpp"

namespace dmath
{
	Vector4 inline constexpr EuclideanToBarycentric(Vector4 v);
	Vector4 inline constexpr HomogenousToBarycentric(Vector4 v);
	Vector4 inline constexpr BarycentricToEuclidean(Vector4 v);
	Vector4 inline constexpr BarycentricToHomogenous(Vector4 v);
	
	Vector4 inline constexpr EuclideanToHomogenous(Vector4 v)
	{
		return Vector4{v.x/v.w, v.y/v.w, v.z/v.w, v.w};
	}

	Vector4 inline constexpr HomogenousToEuclidean(Vector4 v)
	{
		return Vector4{ v.x * v.w, v.y * v.w, v.z * v.w, v.w };
	}
}