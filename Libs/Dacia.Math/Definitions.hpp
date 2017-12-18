#pragma once

#ifdef DMATH_DLL
#ifdef _WIN32
	#ifdef DMATH_EXPORT
		#define DMATH_UTIL __declspec(dllexport)
		#define DMATH_PRIVATE
		#define TEMPLATE
	#else
		#define DMATH_UTIL __declspec(dllimport)
		#define DMATH_PRIVATE
		#define TEMPLATE
#endif
	#elif __GNUC__
		#define DMATH_UTIL		__attribute__ ((visibility ("default")))
		#define DMATH_PRIVATE	__attribute__ ((visibility ("hidden")))
		#define TEMPLATE
	#else
		#define DMATH_UTIL
		#define DMATH_PRIVATE
		#define TEMPLATE extern
#endif

#else
	#define DMATH_UTIL
	#define DMATH_PRIVATE
	#define TEMPLATE
#endif

#define DMATH_DECLARATION _cdecl

#include <cmath>
#include <cfenv>
#include <ratio>
#include <complex>

#ifdef	LEFT_HAND

#elif	RIGHT_HAND

#else

#endif

#include "3rd Party\glm\common.hpp"
#include "3rd Party\glm\matrix.hpp"
#include "3rd Party\glm\gtx\quaternion.hpp"

namespace dmath
{
	typedef unsigned char		byte;

	typedef unsigned char		uint8;
	typedef short unsigned int	uint16;
	typedef long unsigned int	uint32;
	typedef long long unsigned  uint64;

	typedef signed char			int8;
	typedef short int			int16;
	typedef long int			int32;
	typedef long long int		int64;

	typedef float				lowP;
	typedef double				mediumP;

	typedef std::conditional<(sizeof(long double) > 8),
								long double,
								double>::type
								highP;

	enum class CoordinateSystem
	{
		EUCLIDEAN, HOMOGENOUS, BARYCENTRIC
	};

	enum class Endian : byte
	{
		LITTLE, BIG
	};

	constexpr highP PI			= 3.1415926535897932384L;
	constexpr highP TAU			= PI * 2.L;
	constexpr highP PI_HALF		= PI / 2.L;
	constexpr highP PI_THIRD	= PI / 3.L;
	constexpr highP PI_QUART	= PI / 4.L;
	constexpr highP PI_SIXTH	= PI / 6.L;

	constexpr highP RAD_TO_DEG = 180.L / PI;
	constexpr highP DEG_TO_RAD = PI / 180.L;

	constexpr highP PHI = 1.6180339887498948482L;
	constexpr highP E	= 2.7182818284590452353L;

	typedef DMATH_UTIL glm::vec2 Vector2;
	typedef DMATH_UTIL glm::vec3 Vector3;
	typedef DMATH_UTIL glm::vec4 Vector4;

	typedef DMATH_UTIL glm::mat2 Matrix2;
	typedef DMATH_UTIL glm::mat3 Matrix3;
	typedef DMATH_UTIL glm::mat4 Matrix4;

	typedef DMATH_UTIL glm::quat Quaternion;

	DMATH_UTIL
	constexpr uint16 
	DMATH_DECLARATION HighWord(uint32 dword)
	{
		return uint16(dword & 0xffff0000 >> 4);
	}

	DMATH_UTIL
	constexpr uint16 
	DMATH_DECLARATION LowWord(uint32 dword)
	{
		return dword & 0x0000ffff;
	}

	DMATH_UTIL
	constexpr byte 
	DMATH_DECLARATION HighByte(uint16 word)
	{
		return word & 0xff00 >> 2;
	}

	DMATH_UTIL
	constexpr byte 
	DMATH_DECLARATION LowByte(uint16 word)
	{
		return word & 0x00ff;
	}

	DMATH_UTIL
	bool  constexpr 
	DMATH_DECLARATION Support128bitsFloat()
	{
		return sizeof(long double) == 16;
	}

	DMATH_UTIL
	bool  constexpr 
	DMATH_DECLARATION SupportLongDouble()
	{
		return sizeof(long double) > 8;
	}

	template<typename T>
	constexpr T absolute(T const & no)
	{
		return no >= 0 ? no : no * T(-1);
	}

	template<typename T> 
	constexpr T square(T const & no)
	{
		return no * no;
	}

	template<typename T>
	constexpr T max(T const & a, T const & b)
	{
		return a > b ? a : b;
	}

	template<typename T>
	constexpr T min(T const & a, T const & b)
	{
		return a < b ? a : b;
	}

#pragma warning(disable : 4244)
	template<typename T1, typename T2>
	constexpr  T1 max (T1 const & a, T2 const & b)
	{
		return a > b ? a : b;
	}

	template<typename T1, typename T2>
	constexpr  T1  min(T1 const & a, T2 const & b)
	{
		return a < b ? a : b;
	}
#pragma warning(default : 4244)

	template<typename T>
	constexpr T clamp(T a, T minCap, T maxCap)
	{
		return min(maxCap, max(a, minCap));
	}

	template<typename T>
	constexpr highP c_sqrt(T const x0, uint16 const maxIter = 16u)
	{
		return newtonMethod(x0, x0, 0, maxIter);
	}


	constexpr highP newtonMethod(highP x,
								 highP x0,
								 uint16 currentIter,
								 uint16 const maxIter)
	{
		return currentIter < maxIter ?
			   newtonMethod(x - ((square(x) - x0) /  (2.*x - 1.)),
							x0, currentIter + 1U , maxIter) : x;
	}

	template<typename T>
	constexpr highP RadToDeg(T value)
	{
		return value * RAD_TO_DEG;
	}

	template<typename T>
	constexpr highP DegToRad(T value)
	{
		return value * DEG_TO_RAD;
	}

}