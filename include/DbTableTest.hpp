/// @file DbTablesTest.hpp
///
/// @brief Definition of the test table for the in-memory database.
/// @details This struct will be used to describe a test table in the database
/// used for performance tests. Also contains a class, which will take care to 
/// match a given string with the content in a given column.
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

    // Definitions for the Records Collections
    typedef std::vector<DbTableTest> DbTestRecordCollection;
    typedef std::vector<const DbTableTest*> DbTestRecordPointersCollection;

    /// @struct DbTableTest
    /// @brief Table records for users.
    /// @brief Provides table record structure for recording user data.
    struct DbTableTest
    {
        uint64_t id; ///< Unique id column.  
        std::string name; ///< Name of the user.
        int32_t balance; ///< Balance of the user.
        std::string address; ///< Surname of the user.    
    };

    /// @class DbTableTestStringMatcher
    /// @brief String matcher functionality for the Test table.
    /// @details Provides functionality to match a given string against data from the DbTableTest
    /// depending on the selected column. Each table structure shall have such a class, which will
    /// take care to match any string to any column from the table. This will allow for the usage of 
    /// any kind of tables using the existing algorithms without any need to update them.
    class DbTableTestStringMatcher
    {
    public:
        /// @brief Class constructor with arguments.
        /// @details Constructs an object with the given arguments. Based on the selected column 
        /// it sets internal variables to be used for the comparisons against the test table records
        /// and also selects the corect comparison function to be executed.
        /// @param[in] f_columnName The name of the column which will be searched.
        /// @param[in] f_stringToMatch The string to be searched for.
        DbTableTestStringMatcher(const std::string& f_columnName, const std::string& f_stringToMatch);

        /// @brief Check if a given record matches a provided string.
        /// @details Executes a previously selected function which will match a given string against a given field
        /// from the Test table.
        /// @param[in] f_record The table record to check for matching strings.
        /// @returns True if a field from the record matches the given string, false elsewhen. 
        inline bool checkMatching(const DbTableTest& f_record) const;
        
    private:
        /// @brief Match the provided string against the ID column.
        /// @param[in] f_record The table record to check for matching strings.
        /// @returns True if the provided string matches the ID, false elsewhen.
        inline bool matchId(const DbTableTest& f_record) const;

        /// @brief Match the provided string against the Name column.
        /// @param[in] f_record The table record to check for matching strings.
        /// @returns True if the provided string matches the Name, false elsewhen.
        inline bool matchName(const DbTableTest& f_record) const;

        /// @brief Match the provided string against the Balance column.
        /// @param[in] f_record The table record to check for matching strings.
        /// @returns True if the provided string matches the balance, false elsewhen.
        inline bool matchBalance(const DbTableTest& f_record) const;

        /// @brief Match the provided string against the Address column.
        /// @param[in] f_record The table record to check for matching strings.
        /// @returns True if the provided string matches the Address, false elsewhen.
        inline bool matchAddress(const DbTableTest& f_record) const;

        std::function<bool(const DbTableTest&)> m_functionToExecute; ///< Pointer to a function to be executed for the current search.
        std::string m_stringToMatch; ///< The string value to match against any column of type string.
        int32_t m_int32tToMatch; ///< The integer value to match against any column of type integer.
        uint64_t m_uint64tToMatch; ///< The long value to match against any column of type long.
    };
} /// namespace xq
#endif /// !DB_TABLE_TEST_HPP
