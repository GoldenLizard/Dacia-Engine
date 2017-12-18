#pragma once

#include <Definitions.hpp>

namespace dmath
{
	typedef Vector2 Point2D;
	typedef Vector3 Point3D;

	double constexpr ManhattanDistance(Point2D a, Point2D b)
	{
		return (absolute(a.x - b.x) + absolute(a.y - b.y));
	}

	double constexpr ManhattanDistace(Point3D a, Point3D b)
	{
		return (absolute(a.x - b.x) + absolute(absolute(a.y - b.y) + absolute(a.z - b.z)));
	}

	double constexpr EuclideanDistance(Point2D a, Point2D b)
	{
		return c_sqrt(square(a.x - b.x) + square(a.y - b.y));
	}

	double constexpr EuclideanDistance(Point3D a, Point3D b)
	{
		return c_sqrt(square(a.x - b.x) + square(a.y - b.y) + square(a.z - b.z));
	}

}