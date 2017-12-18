#include "BigInt.hpp"


template<GameMath::sign S>
std::string GameMath::BigInt<S>::halveDecString(std::string const & no)
{
	std::string result = "";

	bool hasRemainder = false;
	constexpr int remainder = 5;
	unGameMath::signed digit = 0u;

	auto ctoi = [](char c) -> int
	{
		return c < '9' + 1 and c > '0' - 1 ? c - 0x30 : -1;
	};

	auto itoc = [](int c) -> char
	{
		return c < 10 and c > -1 ? c + 0x30 : '-1';
	};

	for (char c : no)
	{
		if ((digit = ctoi(c)) < 0)
			return "0";

		result += hasRemainder ? itoc(digit / 2 + remainder) : itoc(digit / 2);
		hasRemainder = digit % 2 != 0;
	}

	return result;
}

template<GameMath::sign S>
GameMath::BigInt<S>::BigInt(int32)
{

}

template<GameMath::sign S>
GameMath::BigInt<S>::BigInt(char *)
{
}

template<GameMath::sign S>
GameMath::BigInt<S>::BigInt(std::string decString)
{
	auto ctoi = [](char c) -> int
	{
		return c < '9' + 1 and c > '0' - 1 ? c - 0x30 : -1;
	};

	while (decString.size() > 0)
	{
		ctoi(decString.back()) % 2 == 0 ?
			m_number.push_back(false) :
			m_number.push_back(true);

		decString = halveDecString(decString);

		if (*decString.begin() == '0')
			decString.erase(decString.begin());
	}
}

template<GameMath::sign S>
void GameMath::BigInt<S>::ToDecimal()
{
}

template<GameMath::sign S>
void GameMath::BigInt<S>::ToHex()
{
}

template<GameMath::sign S>
void GameMath::BigInt<S>::ToOctal()
{
}

template<GameMath::sign S>
GameMath::BigInt<S> GameMath::BigInt<S>::operator~()
{
	auto negate = m_number;
	return negate.flip();
}

template<GameMath::sign S>
void GameMath::BigInt<S>::operator+=(BigInt & rhs)
{
	if (rhs.m_number.empty() or m_number.empty())
		return;

	if (m_number.size() != rhs.m_number.size())
	{

	}

	return BigInt();
}

template<size_t lenght>
GameMath::BigInt GameMath::operator""_BIG(char(&number)[length])
{
	return BigInt();
}