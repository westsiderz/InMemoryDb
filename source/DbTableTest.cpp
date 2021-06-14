/// @file DbTablesTest.cpp
///
/// @brief Implementation of the test table for the in-memory database.
/// @details This struct will be used to describe a test table in the database
/// used for performance tests. Also contains a class, which will take care to 
/// match a given string with the content in a given column.
/// @author Ahmed Karaibrahimov
/// @version 1.0
/// @date 6/12/2021
/// @copyright Copyright 2021 Ahmed Karaibrahimov. All rights reserved.
/// @license No license required at all. Use it as you wish

#include "DbTableTest.hpp"

namespace xq
{
    DbTableTestStringMatcher::DbTableTestStringMatcher(const std::string& f_columnName, const std::string& f_stringToMatch)
    {
        // Select the value to be searched for and the function to execute the respective search
        if (f_columnName == "column0")
        {
            m_uint64tToMatch = std::stoul(f_stringToMatch);
            m_functionToExecute = std::bind(&DbTableTestStringMatcher::matchId, this, std::placeholders::_1);
        }
        else if (f_columnName == "column1")
        {
            m_stringToMatch = f_stringToMatch;
            m_functionToExecute = std::bind(&DbTableTestStringMatcher::matchName, this, std::placeholders::_1);
        }
        else if (f_columnName == "column2")
        {
            m_int32tToMatch = std::stoi(f_stringToMatch);
            m_functionToExecute = std::bind(&DbTableTestStringMatcher::matchBalance, this, std::placeholders::_1);
        }
        else
        {
            m_stringToMatch = f_stringToMatch;
            m_functionToExecute = std::bind(&DbTableTestStringMatcher::matchAddress, this, std::placeholders::_1);
        }
    }

    bool DbTableTestStringMatcher::checkMatching(const DbTableTest& f_record) const
    {
        return m_functionToExecute(f_record);
    }

    bool DbTableTestStringMatcher::matchId(const DbTableTest& f_record) const
    {
        return f_record.id == m_uint64tToMatch;
    }

    bool DbTableTestStringMatcher::matchName(const DbTableTest& f_record) const
    {
        return f_record.name.find(m_stringToMatch) != std::string::npos;
    }

    bool DbTableTestStringMatcher::matchBalance(const DbTableTest& f_record) const
    {
        return f_record.balance == m_int32tToMatch;
    }

    bool DbTableTestStringMatcher::matchAddress(const DbTableTest& f_record) const
    {
        return f_record.address.find(m_stringToMatch) != std::string::npos;
    }
}