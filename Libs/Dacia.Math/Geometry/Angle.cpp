#include "Angle.hpp"

namespace dmath
{
	const double Angle::Sin()
	{
		return std::sin(m_valueInRads);
	}
	const double Angle::Cos()
	{
		return std::cos(m_valueInRads);
	}

	const double Angle::Tan()
	{
		return std::tan(m_valueInRads);
	}

	const double Angle::Ctg()
	{
		return Cos()/Sin();
	}

	const double Angle::ASin()
	{
		return std::asin(m_valueInRads);
	}

	const double Angle::ACos()
	{
		return std::acos(m_valueInRads);
	}

	const double Angle::ATan()
	{
		return std::atan(m_valueInRads);
	}

	const double Angle::ACtg()
	{
		return 1.0 / ATan();
	}

	const double Angle::Radians()
	{
		return m_valueInRads;
	}

	const double Angle::Degrees()
	{
		return m_valueInRads * DEG_TO_RAD;
	}

	Angle::Angle(const double & value, MEASURE unit):
		m_valueInRads(unit == DEGREES ? value * DEG_TO_RAD : value)
	{
	}
	Angle & Angle::operator+=(double const & value)
	{
		m_valueInRads += value;
		return *this;
	}

	Angle & Angle::operator*=(double const & value)
	{
		m_valueInRads *= value;
		return *this;
	}

	Angle & Angle::operator-=(double const & value)
	{
		m_valueInRads -= value;
		return *this;
	}

	Angle & Angle::operator/=(double const & value)
	{
		m_valueInRads /= value;
		return *this;
	}

	Angle & Angle::operator+=(Angle const & other)
	{
		m_valueInRads += other.m_valueInRads;
		return *this;
	}

	Angle & Angle::operator*=(Angle const & other)
	{
		m_valueInRads *= other.m_valueInRads;
		return *this;
	}

	Angle & Angle::operator-=(Angle const & other)
	{
		m_valueInRads -= other.m_valueInRads;
		return *this;
	}

	Angle & Angle::operator/=(Angle const & other)
	{
		m_valueInRads /= other.m_valueInRads;
		return *this;
	}

	Angle Angle::operator+(const Angle & value)
	{
		Angle result(m_valueInRads);
		result += value;

		return result;
	}
	Angle Angle::operator-(const Angle & value)
	{
		Angle result(m_valueInRads);
		result -= value;

		return result;
	}

	Angle Angle::operator/(const Angle & value)
	{
		Angle result(m_valueInRads);
		result /= value;

		return result;
	}
	Angle Angle::operator*(const Angle & value)
	{
		Angle result(m_valueInRads);
		result *= value;

		return result;

	}
	Angle Angle::operator+(const double & value)
	{
		Angle result(m_valueInRads);
		result += value;

		return result;

	}
	Angle Angle::operator-(const double & value)
	{
		Angle result(m_valueInRads);
		result -= value;

		return result;
	}
	Angle Angle::operator/(const double & value)
	{
		Angle result(m_valueInRads);
		result /= value;

		return result;
	}

	Angle Angle::operator*(const double & value)
	{
		Angle result(m_valueInRads);
		result *= value;

		return result;
	}

	bool Angle::operator<(const Angle & value)
	{
		return m_valueInRads < value.m_valueInRads;
	}
	bool Angle::operator>(const Angle & value)
	{
		return m_valueInRads > value.m_valueInRads;
	}
	bool Angle::operator<=(const Angle & value)
	{
		return m_valueInRads <= value.m_valueInRads;
	}
	bool Angle::operator>=(const Angle & value)
	{
		return m_valueInRads >= value.m_valueInRads;
	}
	bool Angle::operator==(const Angle & value)
	{
		return m_valueInRads == value.m_valueInRads;
	}

	bool Angle::operator<(const double & value)
	{
		return m_valueInRads < value;
	}

	bool Angle::operator>(const double & value)
	{
		return m_valueInRads > value;
	}
	bool Angle::operator<=(const double & value)
	{
		return m_valueInRads <= value;
	}
	bool Angle::operator>=(const double & value)
	{
		return m_valueInRads >= value;
	}

	bool Angle::operator==(const double & value)
	{
		return m_valueInRads == value;
	}
}
