#include "Circle.hpp"
#include "Rectangle.hpp"

dmath::Circle::Circle():
	center(Point2D(0.,0.)),
	radius(1.)
{
}

dmath::Circle::Circle(Point2D _center, double _radius):
	center(_center),
	radius(_radius)
{
}

bool dmath::Circle::CheckCollision(Point2D p) const
{
	return EuclideanDistance(p, center) <= radius;
}

bool dmath::Circle::CheckCollision(aabb2d box) const
{
	Point2D closestPoint = Point2D(
		max(box.anchor.x, min(box.anchor.x + box.width,  center.x)),
		max(box.anchor.y, min(box.anchor.y + box.height, center.y))
	);

	return EuclideanDistance(closestPoint, center) <= radius;
}

bool dmath::Circle::CheckCollision(Circle other) const
{
	return EuclideanDistance(center, other.center) <= radius;
}
