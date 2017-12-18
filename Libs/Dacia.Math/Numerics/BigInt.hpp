#pragma once

#include "../Definitions.hpp"
#include <vector>
#include <cmath>
#include <iostream>

namespace GameMath
{
	enum class sign : uint8
	{
		SIGNED,
		UNSIGNED,
	};

	enum class base : uint8
	{
		BINARY,
		OCTAL,
		DECIMAL,
		HEXADECIMAL
	};

	template<sign S = sign::SIGNED>
	class BigInt
	{
		std::vector<bool> m_number;
		bool const k_isInfinity;
		
		bool m_carry;
		bool m_hasChanged;
		std::string m_representation;

		std::string halveDecString(std::string const & no);

		public:
			BigInt(int32);
			BigInt(char *);
			BigInt(std::string);
			
			friend std::ostream & operator<<(std::ostream & op, BigInt & big);
			friend std::istream & operator>>(std::istream & op, BigInt & big);

			void ToDecimal();
			void ToHex();
			void ToOctal();

			BigInt operator ~();
			BigInt operator ^(BigInt & rhs);
			BigInt operator ^=(BigInt & rhs);

			void operator +=(BigInt & rhs);
			BigInt operator +(BigInt & rhs);

			void operator -=(BigInt & rhs);
			BigInt operator -(BigInt & rhs);

			void operator *=(BigInt & rhs);
			BigInt operator *(BigInt & rhs);

			void operator /=(BigInt & rhs);
			BigInt operator /(BigInt & rhs);

			std::string GetRepresentation(base);
	};

	template<size_t lenght>
	BigInt operator ""_BIG(char(&number)[length]);
}