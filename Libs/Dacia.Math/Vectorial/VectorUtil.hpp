#include <Definitions.hpp>
#include <Geometry\Point.hpp>

#include <vector>

namespace dmath
{
	Vector3 Cross(Vector3 vec1, Vector3 vec2);
	Vector3 Normalize(Vector3 & vec);
	Vector3 Projection(Vector3 v1, Vector3 v2);
	Vector3 Rejection(Vector3 v1, Vector3 v2);

	highP Length(Vector3 v);

	void GramSchmidt(std::vector<Vector3> & vectors);
}