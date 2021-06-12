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

namespace xq
{
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
			const std::string& f_matchString, DbTestRecordPointersCollection& f_output);

		/// @brief Searches a set of records for a given string in a given column.
		/// @details This is an updated version of the original algorithm from Quickbase. It stores the provided data 
		/// in one DbTableTestStringMatcher and uses its methods to process the search. This is a less optimized version
		/// of the algorithm in the term of speed, but the implementation is generalized and thus allows to use any kind of 
		/// data table without significant changes, given that the table provides a string matcher class. 
		/// @param[in] f_columnName The name of the column to search in.
		/// @param[in] f_matchString The string to search for.
		/// @param[out] f_output Contains the records which match the search criteria.
		void findMatchingRecords(const std::string& f_columnName, 
			const std::string& f_matchString, DbTestRecordPointersCollection& f_output);

	private:
		DbTestRecordCollection m_records; ///< Collection with all the users records.
	};
} /// namespace xq
#endif /// !IN_MEMORY_DB_HPP
