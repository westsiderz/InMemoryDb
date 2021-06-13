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

	void InMemoryDb::findMatchingRecordsOptimized(const std::string& f_columnName,
		const std::string& f_matchString, DbTestRecordPointersCollection& f_output) const
	{
        /// This will decrease the execution time by several milliseconds 
        /// but the used memory might be increased unnecessarely.
        f_output.reserve(m_records.size());
        
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

    void InMemoryDb::findMatchingRecords(const std::string& f_columnName,
        const std::string& f_matchString, DbTestRecordPointersCollection& f_output) const
    {
        /// This will decrease the execution time by several milliseconds 
        /// but the used memory might be increased unnecessarely.
        f_output.reserve(m_records.size());
        
        DbTableTestStringMatcher tableTestStringMatcher{ f_columnName, f_matchString };
        std::for_each(m_records.begin(), m_records.end(), [&](const DbTableTest& rec) {
            /// Check if the record is not deleted already
            if (rec.id != 0)
            {
                if (tableTestStringMatcher.checkMatching(rec))
                {
                    f_output.emplace_back(&rec);
                }
            }
        });
    }

    void InMemoryDb::deleteRecordByID(uint32_t f_id)
    {
        DbTableTest emptyElement{};
        auto foundRecordIter = std::find_if(m_records.begin(), m_records.end(), [&](const DbTableTest& rec) {
            return rec.id == f_id; });
        if (foundRecordIter != m_records.end())
        {
            /// Save the id of the deleted record for a later use
            m_freeIds.push(foundRecordIter->id);

            /// Replace the record that has to be deleted with an empty one
            *foundRecordIter = emptyElement;
        }
    }

    void InMemoryDb::deleteRecordByIDNonOptimized(uint32_t f_id)
    {
        m_records.erase(std::remove_if(m_records.begin(), m_records.end(), [&](const DbTableTest& rec) {
            return rec.id == f_id;
        }));
    }

    uint64_t InMemoryDb::getNumberOfDeletedRecords() const
    {
        return m_freeIds.size();
    }

    uint64_t InMemoryDb::getNumberOfRecords() const
    {
        return m_records.size() - m_freeIds.size();
    }
} /// namespace xq