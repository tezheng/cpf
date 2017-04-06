//////////////////////////////////////////////////////////////////////////
#include "Time/Counter.hpp"
#include "Time.hpp"
#include "Time/Ratio.hpp"
#include <Windows.h>

using namespace Cpf;

namespace
{
	inline Time::Ratio Initialize()
	{
		Time::Ratio result;
		LARGE_INTEGER freq;
		if (::QueryPerformanceFrequency(&freq))
		{
			result.SetNumerator(1);
			result.SetDenominator(freq.QuadPart);
		}
		return result;
	}

	/** @brief The os time ratio, retrieved at library startup. */
	Time::Ratio TimeRatio = Initialize();
}


/**
@brief Initialize the counter system.
@returns True if the OS time systems initialized correctly.
*/
CPF_EXPORT_TIME bool Time::InitializeCounter()
{
	LARGE_INTEGER freq;
	if (::QueryPerformanceFrequency(&freq))
	{
		TimeRatio.SetNumerator(1);
		TimeRatio.SetDenominator(freq.QuadPart);
		return true;
	}
	return false;
}


/**
@brief Get the frequency of the system counter.
@returns The ratio which represents the conversion of the OS specific time value to seconds.
*/
CPF_EXPORT_TIME const Time::Ratio &Time::GetCounterFrequency()
{
	CPF_ASSERT(TimeRatio.GetNumerator() != 0 && TimeRatio.GetDenominator() != 0);
	return TimeRatio;
}


/**
@brief Get the current system counter.
@returns The current OS specific time value.
*/
CPF_EXPORT_TIME int64_t Time::GetCounter()
{
	LARGE_INTEGER counter;
	::QueryPerformanceCounter(&counter);
	return counter.QuadPart;
}
