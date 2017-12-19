#pragma once

#include <Definitions.hpp>

namespace dmath
{
	typedef Vector2 Point2D;
	typedef Vector3 Point3D;

	struct Point2d
	{
		//euclidean, barycentric, spherical
		union { highP x, alpha, roll; };
		union { highP y, beta,  yaw;  };

		Point2d operator +=(Point2d p2);
		Point2d operator /=(Point2d p2);
		Point2d operator -=(Point2d p2);
		Point2d operator *=(Point2d p2);

		Point2d operator +(Point2d p2);
		Point2d operator /(Point2d p2);
		Point2d operator -(Point2d p2);
		Point2d operator *(Point2d p2);

		inline bool operator==(Point2d p2)
		{
			return x == p2.x && y == p2.y;
		}
	};

	struct Point3d
	{
		//euclidean, barycentric, spherical
		union { highP x, alpha, roll; };
		union { highP y, beta,  yaw;  };
		union { highP z, gamma, pitch;};

		Point3d operator +=(Point3d p3);
		Point3d operator /=(Point3d p3);
		Point3d operator -=(Point3d p3);
		Point3d operator *=(Point3d p3);

		Point3d operator +(Point3d p3);
		Point3d operator /(Point3d p3);
		Point3d operator -(Point3d p3);
		Point3d operator *(Point3d p3);

		inline bool operator==(Point3d p3)
		{
			return x == p3.x && y == p3.y && z == p3.z;
		}
	};

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