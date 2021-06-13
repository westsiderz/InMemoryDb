/// @file PerformanceTester.hpp
///
/// @brief Definition of the class performing tests on the database operations.
/// @details Tests the performance of the different database operations and provides the results.
/// @author Ahmed Karaibrahimov
/// @version 1.0
/// @date 6/11/2021
/// @copyright Copyright 2021 Ahmed Karaibrahimov. All rights reserved.
/// @license No license required at all. Use it as you wish.

#ifndef PERFORMANCE_TESTER_HPP
#define PERFORMANCE_TESTER_HPP

#include "DbTableTest.hpp"

namespace xq
{
	/// @class PerformanceTester
	/// @brief Methods to measure the performance of the database operations.
	/// @details Provides methods which will measure the performance of the different database operations.
	class PerformanceTester
	{
	public:
		/// @brief Measure the performance of the Find Matching Records operation.
		/// @details Measures the time to search for a matching records in the database.
		/// Only one record is available, matching the criteria. 
		/// Makes comparison against the original algorithm.
		/// @param[in] f_numberOfRecords The number of total records to generate and search among. 
		void measureFindMatchingRecordsPerformanceOneRecord(uint64_t f_numberOfRecords) const;

		/// @brief Measure the performance of the Find Matching Records operation.
		/// @details Measures the time to search for a matching records in the database.
		/// Several records are available, matching the criteria. 
		/// Makes comparison against the original algorithm.
		/// @param[in] f_numberOfRecords The number of total records to generate and search among. 
		void measureFindMatchingRecordsPerformanceSeveralRecords(uint64_t f_numberOfRecords) const;

		/// @brief Measure the performance of the Remove Record By Id operation.
		/// @details Measures the time to search for a record with the given ID in the database and delete it.
		/// @param[in] f_numberOfRecords The number of total records to generate and search among. 
		/// @param[in] f_id The ID of the record to be deleted. 
		void measureRemoveRecordByIdPerformance(uint64_t f_numberOfRecords, uint32_t f_id) const;

		/// @brief Measure the time to add new record.
		/// @details Measure the time to delete an existing record and add a new one on its place
		/// and also add new record at the end of the collection.
		/// @param[in] f_numberOfRecords The number of total records to generate and search among. 
		/// @param[in] f_id The ID of the record to be deleted. 
		void measureAddNewRecord(uint64_t f_numberOfRecords, uint32_t f_id) const;

	private:
		/// @brief Generates test data.
		/// @details Generates test data to be used for testing the algorithms and store it in a collection.
		/// @param[in] f_prefixSuffix The string to be used to populate the string members of the test data. 
		/// @param[in] f_numberOfRecords The number of records to be generated.
		/// @returns Collection of user records.
		DbTestRecordCollection generateTestData(const std::string& f_prefixSuffix, uint64_t f_numberOfRecords) const;

		/// @brief The original algorithm from Quickbase.
		/// @details This is the original algorithm for matching records search from Quickbase.
		/// @param[in] f_records The records to search in.
		/// @param[in] f_columnName The column to search in. 
		/// @param[in] f_matchString The string to search for.
		/// @returns Collection with all the matching records.
		DbTestRecordCollection QBFindMatchingRecords(const DbTestRecordCollection& f_records, 
			const std::string& f_columnName, const std::string& f_matchString) const;
	};
} /// namespace xq
#endif // !PERFORMANCE_TESTER_HPP
