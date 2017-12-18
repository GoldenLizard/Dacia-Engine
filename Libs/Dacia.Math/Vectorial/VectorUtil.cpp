#include "VectorUtil.hpp"

dmath::Vector3 dmath::Normalize(Vector3 & vec)
{
	return glm::normalize(vec);
}

dmath::Vector3 dmath::Projection(Vector3 v1, Vector3 v2)
{
	return v1 * (v2 / Vector3(Length(v2)));
}

dmath::Vector3 dmath::Rejection(Vector3 v1, Vector3 v2)
{
	return v1 - Projection(v1,v2);
}

dmath::highP dmath::Length(Vector3 v)
{
	return glm::length(v);
}

void dmath::GramSchmidt(std::vector<Vector3> & vectors)
{
	std::vector<Vector3> orthogonalized;
	auto space		= vectors.size();
	auto counter	= 0u;

	orthogonalized.reserve(space);

	auto projUtil = [&](Vector3 vec) -> Vector3
	{
		Vector3 projSum{ 0,0,0 };
		for (auto iter = 0u; iter < counter; ++iter)
			projSum += Projection(vec, vectors[iter]);
	};

	for (auto vec : vectors)
	{
		vec -= projUtil(vec);
		vec = Normalize(vec);
		++counter;
	}
}