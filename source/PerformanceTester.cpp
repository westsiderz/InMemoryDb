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

using namespace std::chrono;

namespace xq
{
    void PerformanceTester::measureFindMatchingRecordsPerformanceOneRecord(uint64_t f_numberOfRecords) const
    {
        auto testData = generateTestData("testdata", f_numberOfRecords);
        std::cout << "Test data generated\n";

        /// Set the search string to be unique
        auto searchString = "testdata" + std::to_string(f_numberOfRecords / 2);

        /// Test the original algorithm from Quickbase
        TimeMeasurement timer{};
        timer.startTimer();
        auto filteredSet = QBFindMatchingRecords(testData, "column1", searchString);
        auto filteredSet2 = QBFindMatchingRecords(testData, "column2", "24000");
        timer.stopTimer();
        timer.printTimeInMilliseconds("QBFindMatchingRecords");
        timer.printTimeInSeconds("QBFindMatchingRecords");
        timer.resetTimer();

        /// Test my improved algorithm
        InMemoryDb database{ testData };
        DbTestRecordPointersCollection resultCollection{};
        timer.startTimer();
        database.findMatchingRecords("column1", searchString, resultCollection);
        database.findMatchingRecords("column2", "24000", resultCollection);
        timer.stopTimer();
        timer.printTimeInMilliseconds("AKFindMatchingRecords");
        timer.printTimeInSeconds("AKFindMatchingRecords");
        timer.resetTimer();

        /// Make sure that the function is correct
        assert(filteredSet.size() == 1);
        assert(resultCollection.size() == 1);
    }

    void PerformanceTester::measureFindMatchingRecordsPerformanceSeveralRecords(uint64_t f_numberOfRecords) const
    {
        auto testData = generateTestData("testdata", f_numberOfRecords);
        std::cout << "Test data generated\n";

        /// Test the original algorithm from Quickbase
        TimeMeasurement timer{};
        timer.startTimer();
        auto filteredSet = QBFindMatchingRecords(testData, "column1", "testdata");
        auto filteredSet2 = QBFindMatchingRecords(testData, "column2", "24000");
        timer.stopTimer();
        timer.printTimeInMilliseconds("QBFindMatchingRecords");
        timer.printTimeInSeconds("QBFindMatchingRecords");
        timer.resetTimer();

        /// Test my improved algorithm
        InMemoryDb database{ testData };
        DbTestRecordPointersCollection resultCollection{};
        timer.startTimer();
        database.findMatchingRecords("column1", "testdata", resultCollection);
        database.findMatchingRecords("column2", "24000", resultCollection);
        timer.stopTimer();
        timer.printTimeInMilliseconds("AKFindMatchingRecords");
        timer.printTimeInSeconds("AKFindMatchingRecords");
        timer.resetTimer();

        /// Make sure that the function is correct
        assert(filteredSet.size() >= 1);
        assert(resultCollection.size() >= 1);
        assert(filteredSet.size() == resultCollection.size());
    }

    void PerformanceTester::measureRemoveRecordByIdPerformance(uint64_t f_numberOfRecords, uint32_t f_id) const
    {
        auto testData = generateTestData("testdata", f_numberOfRecords);
        std::cout << "Test data generated\n";

        /// Test the Remove Records algorithm
        TimeMeasurement timer{};
        InMemoryDb database{ testData };
        timer.startTimer();
        database.deleteRecordByID(f_id);
        timer.stopTimer();
        timer.printTimeInMilliseconds("AKRemoveRecordById");
        timer.printTimeInSeconds("AKRemoveRecordById");
        timer.resetTimer();

        /// Check if only one record was deleted
        assert(database.getNumberOfDeletedRecords() == 1);
    }

    DbTestRecordCollection PerformanceTester::generateTestData(const std::string& f_prefixSuffix, uint64_t f_numberOfRecords) const
    {
        DbTestRecordCollection data;
        data.reserve(f_numberOfRecords);
        for (uint64_t i = 1; i <= f_numberOfRecords; ++i)
        {
            DbTableTest rec{i, f_prefixSuffix + std::to_string(i), static_cast<int32_t>(i % 100), std::to_string(i) + f_prefixSuffix};
            data.emplace_back(rec);
        }
        return data;
    }

    DbTestRecordCollection PerformanceTester::QBFindMatchingRecords(const DbTestRecordCollection& f_records, 
        const std::string& f_columnName, const std::string& f_matchString) const
    {
        DbTestRecordCollection result;
        std::copy_if(f_records.begin(), f_records.end(), std::back_inserter(result), [&](DbTableTest rec) {
            if (f_columnName == "column0") {
                uint64_t matchValue = std::stoul(f_matchString);
                return matchValue == rec.id;
            }else if (f_columnName == "column1") {
                return rec.name.find(f_matchString) != std::string::npos;
            }else if (f_columnName == "column2") {
                int32_t matchValue = std::stoi(f_matchString);
                return matchValue == rec.balance;
            }else if (f_columnName == "column3") {
                return rec.address.find(f_matchString) != std::string::npos;
            }
            else {
                return false;
            }
            });
        return result;
    }
} /// namespace xq