#pragma once

#include "Geometry.hpp"
#include "Angle.hpp"

namespace dmath
{
	struct Rectangle
	{
		Rectangle();
		explicit Rectangle(Point2D _anchor, double length);
		explicit Rectangle(Point2D _anchor, double _width, double _height);

		bool CheckCollision(Point2D point);
		bool CheckCollision(Rectangle other);
		bool CheckCollision(Circle circle);

		bool inline IsSquare() const
		{
			return width == height;
		}

		double inline GetArea() const
		{
			return width * height;
		}

		double inline GetPerimeter() const
		{
			return width * 2 + height * 2;
		}

		Point2D inline GetLowerLeft() const
		{
			return Point2D(anchor + Point2D(0, height));
		}

		Point2D inline GetUpperLeft() const
		{
			return anchor;
		}

		Point2D inline GetLowerRight() const
		{
			return Point2D(anchor + Point2D(width, height));
		}

		Point2D inline GetUpperRight() const
		{
			return Point2D(anchor + Point2D(width, 0));
		}

		void Scale(double factor);
		void Scale(Vector2 factor);
		void Translate(Point2D offset);
		void Rotate(Angle angle, Point2D axis);

		union { double width {0.}, x; };
		union { double height{0.}, y; };
		Point2D anchor{	0., 0.};
	};

}