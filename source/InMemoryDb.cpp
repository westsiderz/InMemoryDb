/// @file InMemoryDb.cpp
///
/// @brief Implementation of the in-memory database class InMemoryDb.
/// @details This class provides implementation of a database which is hosted
/// directly in the memory. The implementation provides operation on this database
/// like Find Matching Records and Delete Records.
/// @author Ahmed Karaibrahimov
/// @version 1.0
/// @date 6/10/2021
/// @copyright Copyright 2021 Ahmed Karaibrahimov. All rights reserved.
/// @license No license required at all. Use it as you wish.

#include "InMemoryDb.hpp"

#include <algorithm>
#include <iterator>

namespace xq
{
	InMemoryDb::InMemoryDb(const DbTestRecordCollection& f_records)
		:
		m_records{ f_records }
	{
	}

	void InMemoryDb::findMatchingRecords(const std::string& f_columnName,
		const std::string& f_matchString, DbTestRecordPointersCollection& f_output)
	{
        /// This will decrease the execution time by several milliseconds 
        /// but the used memory might be increased unnecessarely.
        /// f_output.reserve(m_records.size());
        
        if (f_columnName == "column0")
        {
            uint32_t matchValue = std::stoul(f_matchString);
            std::for_each(m_records.begin(), m_records.end(), [&](const DbTableTest& rec) {
                if (matchValue == rec.id)
                {
                    f_output.emplace_back(&rec);
                }
            });
        }
        else if (f_columnName == "column1")
        {
            std::for_each(m_records.begin(), m_records.end(), [&](const DbTableTest& rec) {
                if (rec.name.find(f_matchString) != std::string::npos)
                {
                    f_output.emplace_back(&rec);
                }
            });
        }
        else if (f_columnName == "column2")
        {
            int64_t matchValue = std::stol(f_matchString);
            std::for_each(m_records.begin(), m_records.end(), [&](const DbTableTest& rec) {
                if (matchValue == rec.balance)
                {
                    f_output.emplace_back(&rec);
                }
            });
        }
        else if (f_columnName == "column3")
        {
            std::for_each(m_records.begin(), m_records.end(), [&](const DbTableTest& rec) {
                if (rec.address.find(f_matchString) != std::string::npos)
                {
                    f_output.emplace_back(&rec);
                }
            });
        }
	}
} /// namespace xq