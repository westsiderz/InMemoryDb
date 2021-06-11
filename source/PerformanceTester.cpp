/// @file PerformanceTester.cpp
///
/// @brief Implementation of the class performing tests on the database operations.
/// @details Tests the performance of the different database operations and provides the results.
/// @author Ahmed Karaibrahimov
/// @version 1.0
/// @date 6/11/2021
/// @copyright Copyright 2021 Ahmed Karaibrahimov. All rights reserved.
/// @license No license required at all. Use it as you wish.

#include "InMemoryDb.hpp"
#include "PerformanceTester.hpp"
#include "TimeMeasurement.hpp"

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <iterator>
#include <string>

using namespace std::chrono;

namespace xq
{
    void PerformanceTester::measureFindMatchingRecordsPerformance(uint32_t f_numberOfExecutions, uint64_t f_numberOfRecords)
    {
        auto testData = generateTestData("testdata", f_numberOfRecords);
        std::cout << "Test data generated\n";

        /// Run the test several times
        for (uint32_t i = 0; i < f_numberOfExecutions; ++i)
        {
            std::cout << "Test #" << i << "\n";
            TimeMeasurement timer{};
            timer.startTimer();
            auto filteredSet = QBFindMatchingRecords(testData, "column1", "testdata");
            auto filteredSet2 = QBFindMatchingRecords(testData, "column2", "24000");
            timer.stopTimer();
            timer.printTimeInMilliseconds("QBFindMatchingRecords");
            timer.printTimeInSeconds("QBFindMatchingRecords");
            timer.resetTimer();

            InMemoryDb database{ testData };
            DbTestRecordPointersCollection resultCollection{};
            timer.startTimer();
            database.findMatchingRecords("column1", "testdata", resultCollection);
            database.findMatchingRecords("column2", "24000", resultCollection);
            timer.stopTimer();
            timer.printTimeInMilliseconds("AKFindMatchingRecords");
            timer.printTimeInSeconds("AKFindMatchingRecords");
            timer.resetTimer();

            // make sure that the function is correct
            assert(filteredSet.size() >= 1);
            assert(resultCollection.size() >= 1);
            assert(filteredSet.size() == resultCollection.size());

            std::cout << "\n";
        }
    }

    DbTestRecordCollection PerformanceTester::generateTestData(const std::string& f_prefixSuffix, uint64_t f_numberOfRecords)
    {
        DbTestRecordCollection data;
        data.reserve(f_numberOfRecords);
        for (uint64_t i = 0; i < f_numberOfRecords; ++i)
        {
            DbTableTest rec = {f_prefixSuffix + std::to_string(i), std::to_string(i) + f_prefixSuffix, static_cast<long>(i % 100),  static_cast<uint32_t>(i)};
            data.emplace_back(rec);
        }
        return data;
    }

    DbTestRecordCollection PerformanceTester::QBFindMatchingRecords(const DbTestRecordCollection& f_records, 
        const std::string& f_columnName, const std::string& f_matchString)
    {
        DbTestRecordCollection result;
        std::copy_if(f_records.begin(), f_records.end(), std::back_inserter(result), [&](DbTableTest rec) {
            if (f_columnName == "column0") {
                uint32_t matchValue = std::stoul(f_matchString);
                return matchValue == rec.id;
            }else if (f_columnName == "column1") {
                return rec.name.find(f_matchString) != std::string::npos;
            }else if (f_columnName == "column2") {
                long matchValue = std::stol(f_matchString);
                return matchValue == rec.balance;
            }else if (f_columnName == "column3") {
                return rec.surname.find(f_matchString) != std::string::npos;
            }
            else {
                return false;
            }
            });
        return result;
    }
}