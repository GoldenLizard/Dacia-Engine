#include "../Shared.hpp"
#include "Stopwatch.hpp"

ARO::Utilities::Stopwatch::Stopwatch():
	m_timeElapsed(std::chrono::milliseconds(0))
{

}

void ARO::Utilities::Stopwatch::Start()
{
	m_startTime = std::chrono::steady_clock::now();
	m_timeElapsed = std::chrono::milliseconds(0);
}

ARO_UTIL
void ARO::Utilities::Stopwatch::Stop()
{
	m_endTime = std::chrono::steady_clock::now();

	m_timeElapsed += std::chrono::duration_cast<std::chrono::milliseconds>
					(m_endTime - m_startTime);
}

ARO_UTIL
void ARO::Utilities::Stopwatch::Continue()
{
	m_startTime = std::chrono::steady_clock::now();
}

ARO_UTIL
void ARO::Utilities::Stopwatch::Reset()
{
	m_timeElapsed = std::chrono::milliseconds(0);
	m_startTime = std::chrono::steady_clock::now();
}

ARO_UTIL
std::chrono::milliseconds 
ARO::Utilities::Stopwatch::GetDuration()
{
	return m_timeElapsed;
}

ARO_UTIL
double ARO::Utilities::Stopwatch::GetDurationHours()
{
	return std::chrono::duration_cast<std::chrono::hours>
		(m_timeElapsed).count();
}

ARO_UTIL
double ARO::Utilities::Stopwatch::GetDurationMinutes()
{
	return std::chrono::duration_cast<std::chrono::minutes>
		(m_timeElapsed).count();
}

ARO_UTIL
double ARO::Utilities::Stopwatch::GetDurationSeconds()
{
	return 1.0 * std::chrono::duration_cast<std::chrono::seconds>
		(m_timeElapsed).count();
}

ARO_UTIL
double ARO::Utilities::Stopwatch::GetDurationMilliseconds()
{
	return double(m_timeElapsed.count());
}

ARO_UTIL
double ARO::Utilities::Stopwatch::GetDurationMicroseconds()
{
	return 1.0 * std::chrono::duration_cast<std::chrono::microseconds>
		(m_timeElapsed).count();
}

ARO_UTIL
double ARO::Utilities::Stopwatch::GetDurationNanoseconds()
{
	return 1.0 * std::chrono::duration_cast<std::chrono::nanoseconds>
		(m_timeElapsed).count();
}
