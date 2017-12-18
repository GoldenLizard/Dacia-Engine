#pragma once

#include <Definitions.hpp>

namespace dmath
{
	class Angle
	{
		mediumP m_valueInRads	{0.};

		public:

			enum MEASURE { DEGREES, RADIANS };

			Angle(const double & value, MEASURE unit = RADIANS);
			Angle() = default;

			Angle& operator+=(double const & value);
			Angle& operator*=(double const & value);
			Angle& operator-=(double const & value);
			Angle& operator/=(double const & value);

			Angle& operator+=(Angle const & other);
			Angle& operator*=(Angle const & other);
			Angle& operator-=(Angle const & other);
			Angle& operator/=(Angle const & other);

			Angle operator+(const Angle & value);
			Angle operator-(const Angle & value);
			Angle operator/(const Angle & value);
			Angle operator*(const Angle & value);

			Angle operator+(const double & other);
			Angle operator-(const double & other);
			Angle operator/(const double & other);
			Angle operator*(const double & other);

			bool operator <(const Angle & value);
			bool operator >(const Angle & value);
			bool operator <=(const Angle & value);
			bool operator >=(const Angle & value);
			bool operator ==(const Angle & value);

			bool operator <(const double & value);
			bool operator >(const double & value);
			bool operator <=(const double & value);
			bool operator >=(const double & value);
			bool operator ==(const double & value);

			const double Sin();
			const double Cos();
			const double Tan();
			const double Ctg();

			const double ASin();
			const double ACos();
			const double ATan();
			const double ACtg();

			const double Radians();
			const double Degrees();

			inline operator int16()
			{
				return static_cast<int16>(m_valueInRads);
			}

			inline operator lowP()
			{
				return static_cast<lowP>(m_valueInRads);
			}

			inline operator mediumP()
			{
				return m_valueInRads;
			}
	};

	inline Angle operator "" _deg(long double const value)
	{
		return Angle(value, Angle::DEGREES);
	}
		
	inline Angle operator "" _rad(long double const value)
	{
		return Angle(value, Angle::RADIANS);
	}

}