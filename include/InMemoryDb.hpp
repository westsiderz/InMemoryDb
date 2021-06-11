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

#include "DbTablesStructs.hpp"

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
		void findMatchingRecords(const std::string& f_columnName, 
			const std::string& f_matchString, DbTestRecordPointersCollection& f_output);

	private:
		DbTestRecordCollection m_records; ///< Collection with all the users records.
	};
}
#endif // !IN_MEMORY_DB_HPP
