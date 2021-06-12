/// @file TimeMeasurement.hpp
///
/// @brief Definition of the class performing time measurements.
/// @details Provides methods which start and stop timer and return the measured time.
/// @author Ahmed Karaibrahimov
/// @version 1.0
/// @date 6/11/2021
/// @copyright Copyright 2021 Ahmed Karaibrahimov. All rights reserved.
/// @license No license required at all. Use it as you wish.

#ifndef TIME_MEASUREMENT_HPP
#define TIME_MEASUREMENT_HPP

#include <chrono>
#include <string>

namespace xq
{
	/// @enum TimerStatus
	/// @brief Different states of the timer
	/// @var TimerStatus::NotStarted
	/// @var TimerStatus::Started
	/// @var TimerStatus::Stopped
	enum class TimerStatus : uint8_t
	{
		NotStarted,
		Started,
		Stopped
	};

	/// @class TimeMeasurement
	/// @brief Methods to measure the execution times of operations.
	/// @details Provides methods which start and stop timer and measure the time
	/// passed for the execution of a given operation.  
	class TimeMeasurement
	{
	public:
		/// @brief Start the timer.
		/// @details Gets the current time as a begin time. Sets the state to Started.
		void startTimer();

		/// @brief Stop the timer.
		/// @details Gets the current time as an end time. Sets the state to Stopped.
		void stopTimer();

		/// @brief Reset the timer.
		/// @details Sets the state to NotStarted.
		void resetTimer();

		/// @brief Print the measured time in seconds
		/// @details Calculates the duration between the begin and the end time.
		/// Prints the result in seconds and the measured operation name.
		/// @param[in] f_operationName The name of the measured operation.  
		void printTimeInSeconds(const std::string& f_operationName) const;

		/// @brief Print the measured time in milliseconds
		/// @details Calculates the duration between the begin and the end time.
		/// Prints the result in milliseconds and the measured operation name.
		/// @param[in] f_operationName The name of the measured operation.  
		void printTimeInMilliseconds(const std::string& f_operationName) const;

	private:
		std::chrono::steady_clock::time_point m_startTime{}; ///< The time point when the timer was started.
		std::chrono::steady_clock::time_point m_endTime{}; ///< The time point when the timer was stopped.
		TimerStatus m_timerStatus{ TimerStatus::NotStarted }; ///< The current state of the timer
	};
} /// namespace xq
#endif // !TIME_MEASUREMENT_HPP

