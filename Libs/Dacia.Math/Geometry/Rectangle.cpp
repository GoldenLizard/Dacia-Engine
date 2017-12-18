#include "Rectangle.hpp"
#include "Circle.hpp"

dmath::Rectangle::Rectangle():
	anchor(Point2D(0., 0.)),
	width(0),
	height(0)
{
}

dmath::Rectangle::Rectangle(Point2D _anchor, double length):
	anchor(_anchor),
	width(length),
	height(length)
	
{
}

dmath::Rectangle::Rectangle(Point2D _anchor, double _width, double _height):
	anchor(_anchor),
	width(_width),
	height(_height)
{
}

bool dmath::Rectangle::CheckCollision(Point2D point)
{
	return anchor.x + width >= point.x && anchor.x <= point.x
		&& anchor.y + height >= point.y && anchor.y <= point.y;
}

bool dmath::Rectangle::CheckCollision(Rectangle other)
{
	return anchor.x + width >= other.anchor.x && anchor.x <= other.anchor.x &&
		   anchor.y + height >= other.anchor.y && anchor.y <= other.anchor.y;
}

bool dmath::Rectangle::CheckCollision(Circle circle)
{
	Point2D closestPoint = Point2D(
		max(anchor.x, min(anchor.x + width, circle.center.x)),
		max(anchor.y, min(anchor.y + height, circle.center.y))
	);

	return EuclideanDistance(closestPoint, circle.center) <= circle.radius;
}

void dmath::Rectangle::Scale(double factor)
{
	width	*= factor;
	height	*= factor;
}

void dmath::Rectangle::Scale(Vector2 factor)
{
	width	*= factor.x;
	height	*= factor.y;
}

void dmath::Rectangle::Translate(Point2D offset)
{
	anchor += offset;
}

void dmath::Rectangle::Rotate(Angle angle, Point2D axis)
{
	Quaternion quat(angle, Vector3(axis, 0.0));
	Point3D rotatedPoint = quat * Point3D(anchor, 0.0);

	anchor = { rotatedPoint.x, rotatedPoint.y };
}
