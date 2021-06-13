#include "PerformanceTester.hpp"

#include <iostream>

/// Settings for the performance tests
constexpr uint64_t const cNumberOfTestRecordsSameAmount{ 1000000 };
constexpr uint32_t const cNumberOfTestExecutionsSameAmount{ 5 };
constexpr uint32_t const cNumberOfTestRecordsDifferentAmountPower{ 10 };
constexpr uint32_t const cNumberOfTestExecutionsdifferentAmount{ 6 };
constexpr uint32_t const cIfDeleteRecords{ 10 };
constexpr uint32_t const cNumberOfTestExecutionsDeleteRecords{ 5 };

void testFindMatchingRecord()
{
	xq::PerformanceTester tester{};
	/// Test with same amount of records several times
	std::cout << "Testing Find Matching Records with the same anount of records\n";
	for (uint32_t i = 0; i < cNumberOfTestExecutionsSameAmount; ++i)
	{
		std::cout << "Starting test #" << i + 1 << " with " << cNumberOfTestRecordsSameAmount << " records\n";
		tester.measureFindMatchingRecordsPerformanceSeveralRecords(cNumberOfTestRecordsSameAmount);
		std::cout << "\n";
	}
	std::cout << "\n";

	/// Test with different amounts of records several times
	std::cout << "Testing Find Matching Records with different anounts of records\n";
	for (uint32_t i = 0; i < cNumberOfTestExecutionsdifferentAmount; ++i)
	{
		auto numberOfRecords = static_cast<uint64_t>(pow(static_cast<double>(cNumberOfTestRecordsDifferentAmountPower), static_cast<double>(i + 2)));
		std::cout << "Starting test #" << i + 1 << " with " << numberOfRecords << " records\n";
		tester.measureFindMatchingRecordsPerformanceSeveralRecords(numberOfRecords);
		std::cout << "\n";
	}
	std::cout << "\n";
}

void testRemoveRecordById()
{
	xq::PerformanceTester tester{};
	/// Test with same amount of records several times
	std::cout << "Testing Remove Record By ID\n";
	for (uint32_t i = 0; i < cNumberOfTestExecutionsDeleteRecords; ++i)
	{
		auto recordsIdToDelete = static_cast<uint32_t>(pow(static_cast<double>(cIfDeleteRecords), static_cast<double>(i + 1)));
		std::cout << "Starting test #" << i + 1 << " with record id = " << recordsIdToDelete << " records\n";
		tester.measureRemoveRecordByIdPerformance(cNumberOfTestRecordsSameAmount, recordsIdToDelete);
		std::cout << "\n";
	}
	std::cout << "\n";
}

int main()
{
	testFindMatchingRecord();
	testRemoveRecordById();
	return 0;
}