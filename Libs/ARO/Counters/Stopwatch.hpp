#pragma once

#include "../Shared.hpp"
#include <chrono>

#pragma warning(disable : 4251)

namespace ARO
{
	namespace Utilities
	{
		extern "C"
		{
			class ARO_UTIL Stopwatch
			{
				constexpr static double to_Nanoseconds	= 1e6;
				constexpr static double to_Microseconds = 1e3;
				constexpr static double to_Milliseconds = 1e0;
				constexpr static double to_Seconds		= 1e-3;
				constexpr static double to_Minutes		= 1e-3 * 1.0 / 60.0;
				constexpr static double to_Hours		= 1e-3 * 1.0 / (60.0 * 60.0);
				constexpr static double to_Days			= 1e-3 * 1.0 / (60.0 * 60.0 * 24.0);

				Clock::time_point m_startTime;
				Clock::time_point m_endTime;

				std::chrono::milliseconds m_timeElapsed;

			public:

				Stopwatch();

				void Start();
				void Stop();
				void Continue();
				void Reset();

				std::chrono::milliseconds
					GetDuration();

				double GetDurationHours();
				double GetDurationMinutes();
				double GetDurationSeconds();
				double GetDurationMilliseconds();
				double GetDurationMicroseconds();
				double GetDurationNanoseconds();
			};
		}
	}
}