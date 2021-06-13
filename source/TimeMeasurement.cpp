/// @file TimeMeasurement.cpp
///
/// @brief Implementation of the class performing time measurements.
/// @details Provides methods which start and stop timer and return the measured time.
/// @author Ahmed Karaibrahimov
/// @version 1.0
/// @date 6/11/2021
/// @copyright Copyright 2021 Ahmed Karaibrahimov. All rights reserved.
/// @license No license required at all. Use it as you wish.

#include "TimeMeasurement.hpp"

#include <iostream>

namespace xq
{
	void TimeMeasurement::startTimer()
	{
		// The timer can be started only if it hasn't been started already
		if (m_timerStatus != TimerStatus::Started)
		{
			m_startTime = std::chrono::steady_clock::now();
			m_timerStatus = TimerStatus::Started;
		}
		else
		{
			std::cout << "The timer cannot be started\n";
		}
	}

	void TimeMeasurement::stopTimer()
	{
		// The timer can be stopped only if it has been Started already
		if (m_timerStatus == TimerStatus::Started)
		{
			m_endTime = std::chrono::steady_clock::now();
			m_timerStatus = TimerStatus::Stopped;
		}
		else
		{
			std::cout << "The timer cannot be stopped\n";
		}
	}

	void TimeMeasurement::resetTimer()
	{
		m_timerStatus = TimerStatus::NotStarted;
	}

	void TimeMeasurement::printTimeInSeconds(const std::string& f_operationName) const
	{
		// Print the result only if the timer has been started and then stopped
		if (m_timerStatus == TimerStatus::Stopped)
		{
			std::chrono::duration<double> executionTimeInSeconds = m_endTime - m_startTime;
			std::cout << "The operation " << f_operationName << " was executed in " << executionTimeInSeconds.count() << " seconds\n";
		}
		else
		{
			std::cout << "The timer was not started and stopped properly\n";
		} 
	}

	void TimeMeasurement::printTimeInMilliseconds(const std::string& f_operationName) const
	{
		// Print the result only if the timer has been started and then stopped
		if (m_timerStatus == TimerStatus::Stopped)
		{
			auto executionTimeInMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(m_endTime - m_startTime).count();
			std::cout << "The operation " << f_operationName << " was executed in " << executionTimeInMilliseconds << " milliseconds\n";
		}
		else
		{
			std::cout << "The timer was not started and stopped properly\n";
		}
	}
} /// namespace xq