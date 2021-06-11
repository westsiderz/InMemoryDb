/// @file DbTablesStructs.hpp
///
/// @brief Definition of table structures for the in-memory database.
/// @details The structures which will be used to describe a table in the database.
/// @author Ahmed Karaibrahimov
/// @version 1.0
/// @date 6/10/2021
/// @copyright Copyright 2021 Ahmed Karaibrahimov. All rights reserved.
/// @license No license required at all. Use it as you wish.

#ifndef DB_TABLES_STRUCTS_HPP
#define DB_TABLES_STRUCTS_HPP

#include <string>
#include <vector>
namespace xq
{
    struct DbTableTest;

    /// Definitions for the Records Collections
    typedef std::vector<DbTableTest> DbTestRecordCollection;
    typedef std::vector<const DbTableTest*> DbTestRecordPointersCollection;

    /// @struct DbTableTest
    /// @brief Table records for users.
    /// @brief Provides table record structure for recording user data.
    struct DbTableTest
    {
        std::string name; ///< Name of the user.
        std::string surname; ///< Surname of the user.
        int64_t balance; ///< Balance of the user.
        uint32_t id; ///< Unique id column.   
    };
}
#endif // !DB_TABLES_STRUCTS_HPP
