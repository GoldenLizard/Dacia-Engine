#pragma once

#include "Geometry.hpp"

namespace dmath
{
	struct Circle
	{
		Circle();
		Circle(Point2D _center, double _radius);

		mediumP	radius	{0.};
		Point2D center	{0., 0.};

		inline double GetDiameter() const
		{
			return 2. * radius;
		}

		inline double GetArea() const
		{
			return TAU * radius;
		}

		inline double GetCircumference() const
		{
			return PI * radius;
		}

		bool CheckCollision(Point2D p)		const;
		bool CheckCollision(aabb2d box)		const;
		bool CheckCollision(Circle other)	const;
	};
}