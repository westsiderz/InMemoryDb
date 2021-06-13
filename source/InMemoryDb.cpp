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
        // This will decrease the execution time by several milliseconds 
        // but the used memory might be increased unnecessarely.
        f_output.reserve(m_records.size());
        
        // First check what column we are looking at before any processing of the records
        if (f_columnName == "column0")
        {
            // Get the numeric value from the string before the processing of the records 
            // instead of getting it with each record's processing
            uint32_t matchValue = std::stoul(f_matchString);

            // Traverse all records searching for a matching IDs
            std::for_each(m_records.begin(), m_records.end(), [&](const DbTableTest& rec) {
                if (matchValue == rec.id)
                {
                    f_output.emplace_back(&rec);
                }
            });
        }
        else if (f_columnName == "column1")
        {
            // Traverse all records searching for a matching Name
            std::for_each(m_records.begin(), m_records.end(), [&](const DbTableTest& rec) {
                if (rec.name.find(f_matchString) != std::string::npos)
                {
                    f_output.emplace_back(&rec);
                }
            });
        }
        else if (f_columnName == "column2")
        {
            // Get the numeric value from the string before the processing of the records 
            // instead of getting it with each record's processing
            int64_t matchValue = std::stol(f_matchString);
            // Traverse all records searching for a matching Balance
            std::for_each(m_records.begin(), m_records.end(), [&](const DbTableTest& rec) {
                if (matchValue == rec.balance)
                {
                    f_output.emplace_back(&rec);
                }
            });
        }
        else if (f_columnName == "column3")
        {
            // Traverse all records searching for a matching Address
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
        // This will decrease the execution time by several milliseconds 
        // but the used memory might be increased unnecessarely.
        f_output.reserve(m_records.size());
        
        DbTableTestStringMatcher tableTestStringMatcher{ f_columnName, f_matchString };
        std::for_each(m_records.begin(), m_records.end(), [&](const DbTableTest& rec) {
            // Check if the record is not deleted already
            if (rec.id != 0)
            {
                // Search for matching records
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
        // Look for a record with the matching ID and once found, replace it with empty record. Stop any further processing of the records
        auto foundRecordIter = std::find_if(m_records.begin(), m_records.end(), [&](const DbTableTest& rec) {
            return rec.id == f_id; });
        if (foundRecordIter != m_records.end())
        {
            // Save the index of the deleted record for a later use
            m_freeIndexes.push(foundRecordIter->id);

            // Replace the record that has to be deleted with an empty one
            *foundRecordIter = emptyElement;
        }
    }

    void InMemoryDb::deleteRecordByIDNonOptimized(uint32_t f_id)
    {
        // Remove a record with a matching ID from the collection of records
        auto removeIter = std::remove_if(m_records.begin(), m_records.end(), [&](const DbTableTest& rec) {
            return rec.id == f_id;
            });
        if (removeIter != m_records.end())
        {
            m_records.erase(removeIter);
        }
    }

    void InMemoryDb::addRecord(const DbTableTest& f_newRecord)
    {
        // Check if we have available slot already
        if (m_freeIndexes.size() > 0)
        {
            auto freeIndex = m_freeIndexes.front();
            m_freeIndexes.pop();
            // Check just in case that we haven't gotten any wrong index out of bounds
            if (freeIndex < m_records.size())
            {
                // Replace an existing free slot with the new record
                m_records.at(freeIndex) = f_newRecord;
            }
            // If the index was wrong, place the new record at the end of the collection
            else
            {
                m_records.emplace_back(f_newRecord);
            }
        }
        else
        {
            // No free slots available, push the record at the end
            m_records.emplace_back(f_newRecord);
        }
    }

    uint64_t InMemoryDb::getNumberOfDeletedRecords() const
    {
        return m_freeIndexes.size();
    }

    uint64_t InMemoryDb::getNumberOfRecords() const
    {
        return m_records.size() - m_freeIndexes.size();
    }
} /// namespace xq