#pragma once

#include <Definitions.hpp>

namespace dmath
{
	namespace unused
	{
		template<typename precision_t = dmath::MediumP>
		struct Vector3
		{
			union { precision_t x, r, s; };
			union { precision_t y, g, t; };
			union { precision_t z, b, v; };

			precision_t Length();
			Vector3		Normalize();
			Vector3		Projection(Vector3 target);
			Vector3		Rejection(Vector3 target);
			Vector3		Reorthogonalize(byte axis);

			void operator+=(Vector3);
			void operator+=(precision_t);
		};

		template<typename precision_t = dmath::MediumP>
		struct Vector4
		{
			union { precision_t x, r, s; };
			union { precision_t y, g, t; };
			union { precision_t z, b, v; };
			union { precision_t w, a; };

			precision_t Length();
			Vector4		Normalize();
			Vector4		Projection(Vector4 target);
			Vector4		Rejection(Vector4 target);
			Vector4		Reorthogonalize(byte axis);

			void operator+=(Vector4);
			void operator+=(precision_t);
		};
	}

}