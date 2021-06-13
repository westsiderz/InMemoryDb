/// @file InMemoryDb.hpp
///
/// @brief Definition of the in-memory database class InMemoryDb.
/// @details This class provides implementation of a database which is hosted
/// directly in the memory. The implementation provides operation on this database
/// like Find Matching Records and Delete Records.
/// @author Ahmed Karaibrahimov
/// @version 1.0
/// @date 6/10/2021
/// @copyright Copyright 2021 Ahmed Karaibrahimov. All rights reserved.
/// @license No license required at all. Use it as you wish.

#ifndef IN_MEMORY_DB_HPP
#define IN_MEMORY_DB_HPP

#include "DbTableTest.hpp"

#include <queue>

namespace xq
{
	typedef std::queue<uint64_t> DbFreeIdsCollection;
	/// @class InMemoryDb
	/// @brief In-memory database class.
	/// @details Provides implementation of a database which is hosted
	/// directly in the memory with expected database operations like
	/// Find Matching Records, Add Records and Delete Records. 
	class InMemoryDb
	{
	public:
		/// @brief Class constructor with arguments.
		/// @details Constructs the class using the given arguments.
		InMemoryDb(const DbTestRecordCollection& f_records);

		/// @brief Searches a set of records for a given string in a given column in a more optimized way.
		/// @details This is an updated version of the original algorithm from Quickbase. It checks
		/// what is the selected column, if needed transforms the given search string to a number
		/// and checks if it matches with the content in the given column. This is a more optimized version
		/// of the algorithm in the term of speed, but it is also with a table specific implementation, thus not allowing for the 
		/// use of another table structure, without the respective changes. 
		/// @param[in] f_columnName The name of the column to search in.
		/// @param[in] f_matchString The string to search for.
		/// @param[out] f_output Contains the records which match the search criteria.
		void findMatchingRecordsOptimized(const std::string& f_columnName,
			const std::string& f_matchString, DbTestRecordPointersCollection& f_output) const;

		/// @brief Searches a set of records for a given string in a given column.
		/// @details This is an updated version of the original algorithm from Quickbase. It stores the provided data 
		/// in one DbTableTestStringMatcher and uses its methods to process the search. This is a less optimized version
		/// of the algorithm in the term of speed, but the implementation is generalized and thus allows to use any kind of 
		/// data table without significant changes, given that the table provides a string matcher class. 
		/// @param[in] f_columnName The name of the column to search in.
		/// @param[in] f_matchString The string to search for.
		/// @param[out] f_output Contains the records which match the search criteria.
		void findMatchingRecords(const std::string& f_columnName, 
			const std::string& f_matchString, DbTestRecordPointersCollection& f_output) const;

		/// @brief Delete a record from the database with the given id.
		/// @details Traverses the whole collection of records and looks for a record, which matches the selected Id.
		/// Sets that record's ID to 0 which annotates that the record is deleted. The record is not actually removed from the collection
		/// because this is a costly operation but instead it's index is saved in another collection to be used later when adding new record.
		/// This way deleting new records will not require shifting of the remaining and adding new record might not require reallocation
		/// of new memory.
		/// @param[in] f_id The id of the record to be deleted.
		void deleteRecordByID(uint32_t f_id);

		/// @brief Delete a record from the database with the given id in a non-optimized way.
		/// @details Traverses the whole collection of records and looks for a record, which matches the selected Id.
		/// Removes the record from the collection, which also causes all the aftercomming records to be shifted.
		/// @param[in] f_id The id of the record to be deleted.
		void deleteRecordByIDNonOptimized(uint32_t f_id);

		/// @brief Add a new record to the database.
		/// @details First checks if there is a free slot in the database by looking at m_freeIds. In case there is,
		/// put the new record on its place. In case there is non, push the new record at the back of the records' collection.
		/// @param[in] f_newRecord The new record to be added.
		void addRecord(const DbTableTest& f_newRecord);

		/// @brief Gets the number of deleted records.
		/// @details Gets the number of elements in the m_freeIds member variable.
		/// @returns Number of deleted records.
		uint64_t getNumberOfDeletedRecords() const;

		/// @brief Get the number of records in the database.
		/// @returns The number of available records, which are not considered deleted.
		uint64_t getNumberOfRecords() const;

	private:
		DbTestRecordCollection m_records; ///< Collection with all the users records.
		DbFreeIdsCollection m_freeIndexes; ///< Collection with indexes of deleted records, which can be used to add new records.
	};
} /// namespace xq
#endif /// !IN_MEMORY_DB_HPP
