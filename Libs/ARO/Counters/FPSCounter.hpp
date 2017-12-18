#pragma once

#include "../Shared.hpp"
#include "Stopwatch.hpp"

namespace ARO
{
	namespace Utilities
	{
		extern "C"
		{
			constexpr uint16 BUFFER_SIZE = 1024;

			class ARO_UTIL FPSCounter
			{
				Stopwatch	m_counter;
				size_t		m_lastIndex{ 0 };

				std::chrono::milliseconds m_totalDuration;

				std::chrono::milliseconds m_avgFrame;
				std::chrono::milliseconds m_lastFrame;
				std::chrono::milliseconds m_bestFrame;
				std::chrono::milliseconds m_worstFrame;

				constexpr inline static double
					toFPS(std::chrono::milliseconds duration)
				{
					return 1e3 / duration.count();
				}

				constexpr inline static double
					toMilliseconds(double fps)
				{
					return 1e3 / fps;
				}

				bool inline isBufferFull()
				{
					return m_lastIndex == BUFFER_SIZE;
				}

				void ResetBuffer();
				void AddToBuffer(std::chrono::milliseconds);

				void RegisterFrame();

			public:

				FPSCounter();

				void OnStartFrame();
				void OnEndFrame();

				double GetFPS();
				double GetLastFrameFPS();

			};
		}
	}
}

