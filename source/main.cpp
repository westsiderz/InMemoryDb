#include "PerformanceTester.hpp"

/// Settings for the performance tests
constexpr uint64_t const cNumberOfTestRecords{ 1000000 };
constexpr uint32_t const cNumberOfTestExecutions{ 10 };

int main()
{
	xq::PerformanceTester tester{};
	for (int i = 0; i < cNumberOfTestExecutions; ++i)
	{
		tester.measureFindMatchingRecordsPerformance(cNumberOfTestExecutions, cNumberOfTestRecords);
	}
	return 0;
}