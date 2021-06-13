/// @file TestTimeMeasurement.cpp
///
/// @brief Unit tests for the TimeMeasurement class.
/// @author Ahmed Karaibrahimov
/// @version 1.0
/// @date 6/13/2021
/// @copyright Copyright 2021 Ahmed Karaibrahimov. All rights reserved.
/// @license No license required at all. Use it as you wish.

#include "gtest/gtest.h"
#include "TimeMeasurement.hpp"

/// @brief Test that the timer can be started successfully
/// if it hasn't been started already.
TEST(TimeMeasurement, StartTimerSuccess) {
	xq::TimeMeasurement timer{};
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::NotStarted);

	timer.startTimer();
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::Started);
}

/// @brief Test that the timer start will fail if it has been started already.
TEST(TimeMeasurement, StartTimerSecondTimeFails) {
	xq::TimeMeasurement timer{};
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::NotStarted);

	testing::internal::CaptureStdout();
	timer.startTimer();
	timer.startTimer();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::Started);
	EXPECT_EQ(output, "The timer cannot be started\n");
}

/// @brief Test that the timer can be stopped successfully
/// if it has been started first.
TEST(TimeMeasurement, StopTimerSuccess) {
	xq::TimeMeasurement timer{};
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::NotStarted);

	timer.startTimer();
	timer.stopTimer();
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::Stopped);
}

/// @brief Test that the timer stop will fail if it hasn't been started already.
TEST(TimeMeasurement, StopTimerFailsIfNotStarted) {
	xq::TimeMeasurement timer{};
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::NotStarted);

	testing::internal::CaptureStdout();
	timer.stopTimer();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(timer.getTimerState(), xq::TimerStatus::Stopped);
	EXPECT_EQ(output, "The timer cannot be stopped\n");
}

/// @brief Test that the timer stop will fail if a second attempt to be stopped is made.
TEST(TimeMeasurement, StopTimerSecondTimeFails) {
	xq::TimeMeasurement timer{};
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::NotStarted);

	testing::internal::CaptureStdout();
	timer.startTimer();
	timer.stopTimer();
	timer.stopTimer();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::Stopped);
	EXPECT_EQ(output, "The timer cannot be stopped\n");
}

/// @brief Test that the timer will be reset if it has been started.
TEST(TimeMeasurement, ResetTimerIfStarted) {
	xq::TimeMeasurement timer{};
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::NotStarted);

	timer.startTimer();
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::Started);

	timer.resetTimer();
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::NotStarted);
}

/// @brief Test that the timer will be reset if it has been started.
TEST(TimeMeasurement, ResetTimerIfStopped) {
	xq::TimeMeasurement timer{};
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::NotStarted);

	timer.startTimer();
	timer.stopTimer();
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::Stopped);

	timer.resetTimer();
	EXPECT_EQ(timer.getTimerState(), xq::TimerStatus::NotStarted);
}