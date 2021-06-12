/// @file DbTablesTest.hpp
///
/// @brief Definition of the test table for the in-memory database.
/// @details This struct will be used to describe a table in the database
/// used for performance tests.
/// @author Ahmed Karaibrahimov
/// @version 1.0
/// @date 6/10/2021
/// @copyright Copyright 2021 Ahmed Karaibrahimov. All rights reserved.
/// @license No license required at all. Use it as you wish.

#ifndef DB_TABLE_TEST_HPP
#define DB_TABLE_TEST_HPP

#include <functional>
#include <string>
#include <unordered_map>
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
        uint32_t id; ///< Unique id column.  
        std::string name; ///< Name of the user.
        int64_t balance; ///< Balance of the user.
        std::string address; ///< Surname of the user.    
    };

    struct DbTableTestStringMatcher
    {
    public:
        DbTableTestStringMatcher(const std::string& f_columnName, const std::string& f_stringToMatch);

        inline bool checkMatching(const DbTableTest& f_record);
        
    private:

        inline bool matchId(const DbTableTest& f_record);

        inline bool matchName(const DbTableTest& f_record);

        inline bool matchBalance(const DbTableTest& f_record);

        inline bool matchAddress(const DbTableTest& f_record);

        std::function<bool(const DbTableTest&)> m_functionToExecute;

        std::string m_stringToMatch;
        uint32_t m_uint32tToMatch;
        int64_t m_int64tToMatch;
    };
} /// namespace xq
#endif /// !DB_TABLE_TEST_HPP
