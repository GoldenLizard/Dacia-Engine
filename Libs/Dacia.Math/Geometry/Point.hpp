#pragma once

#include <Definitions.hpp>

namespace dmath
{
	typedef Vector2 Point2D;
	typedef Vector3 Point3D;

	//struct Point2D
	//{
	//	//euclidean, barycentric, spherical
	//	union { highP x, alpha, roll; };
	//	union { highP y, beta,  yaw;  };
	//};

	//struct Point3D
	//{
	//	//euclidean, barycentric, spherical
	//	union { highP x, alpha, roll; };
	//	union { highP y, beta,  yaw;  };
	//	union { highP z, gamma, pitch;};
	//};

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