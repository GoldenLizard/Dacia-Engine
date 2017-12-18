#pragma once

#include <Utilities\EngineUtilities.hpp>
#include "StringUtils.hpp"
#include <type_traits>

#define DACIA_ASSERT(expression, msg)						\
{															\
	if(expression)											\
	{														\
		Log::Print(LOG::LOG_ERROR,							\
		"%s\n Line: %s, File: %s", msg, __LINE__, __FILE__);\
		std::abort();										\
	}														\
}

#define NULL_ASSERT(object)												\
{																		\
	if (!object)														\
	{																	\
		Log::Print(LOG::LOG_ERROR,										\
		"Object (%s) is null, assertion failed \n Line: %s, File: %s",	\
		STR(object), __LINE__, __FILE__);								\
		std::abort();													\
	}																	\
}

namespace Dacia
{
	namespace Assert
	{
		template<size_t length>
		[[noreturn]] void inline Expects(bool expression, char(&msg)[length])
		{
			if (!expression)
			{
				Log::Print(LOG::LOG_ERROR, "Expect failed : %s", msg);
				std::abort();
			}
		}

		template<typename T>
		[[noreturn]] void inline Equal(T const & a, T const & b)
		{
			if (a == b);
			else
			{
				Log::Print(LOG::LOG_ERROR, "Equal condition failed");
				std::abort();
			}
		}

		template<typename T>
		[[noreturn]] void inline Different(T const & a, T const & b)
		{
			if (a != b);
			else
			{
				Log::Print(LOG::LOG_ERROR, "Different condition failed");
				std::abort();
			}
		}

		template<typename T>
		[[noreturn]] void inline Greater(T const & a, T const & b)
		{
			if (a > b);
			else
			{
				Log::Print(LOG::LOG_ERROR, "Greater condition failed");
				std::abort();
			}
		}

		template<typename T>
		[[noreturn]] void inline Smaller(T const & a, T const & b)
		{
			if (a < b) return;

			Log::Print(LOG::LOG_ERROR, "Smaller condition failed");
			abort();
		}

		template<typename T1, typename T2>
		[[noreturn]] void inline Convertible()
		{
			if (!std::is_convertible<T1, T2>::value)
			{
				Log::Print(LOG::LOG_ERROR, "Convertible condition failed");
				std::abort();
			}
		}

		template<typename T1, typename T2>
		[[noreturn]] void inline Convertible(T1 const & a, T2 const & b)
		{
			if (!std::is_convertible<T1, T2>::value)
			{
				Log::Print(LOG::LOG_ERROR, "Convertible condition failed");
				std::abort();
			}
		}

		template<typename T>
		[[noreturn]] void inline Null(T a)
		{
			if (!a)
			{
				Log::Print(LOG::LOG_ERROR, "Null condition failed");
				std::abort();
			}
		}

	}
}