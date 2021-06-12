#include "DbTableTest.hpp"

namespace xq
{
    DbTableTestStringMatcher::DbTableTestStringMatcher(const std::string& f_columnName, const std::string& f_stringToMatch)
    {
        if (f_columnName == "column0")
        {
            m_uint32tToMatch = std::stoul(f_stringToMatch);
            m_functionToExecute = std::bind(&DbTableTestStringMatcher::matchId, this, std::placeholders::_1);
        }
        else if (f_columnName == "column1")
        {
            m_stringToMatch = f_stringToMatch;
            m_functionToExecute = std::bind(&DbTableTestStringMatcher::matchName, this, std::placeholders::_1);
        }
        else if (f_columnName == "column2")
        {
            m_int64tToMatch = std::stol(f_stringToMatch);
            m_functionToExecute = std::bind(&DbTableTestStringMatcher::matchBalance, this, std::placeholders::_1);
        }
        else
        {
            m_stringToMatch = f_stringToMatch;
            m_functionToExecute = std::bind(&DbTableTestStringMatcher::matchAddress, this, std::placeholders::_1);
        }

        /// A workaround: The checkMatching() function is not inlined and instead gets removed by the compiler.
        /// Adding call to it here fixes this
        DbTableTest dummy{};
        checkMatching(dummy);
    }

    bool DbTableTestStringMatcher::checkMatching(const DbTableTest& f_record)
    {
        return m_functionToExecute(f_record);
    }

    bool DbTableTestStringMatcher::matchId(const DbTableTest& f_record)
    {
        return f_record.id == m_uint32tToMatch;
    }

    bool DbTableTestStringMatcher::matchName(const DbTableTest& f_record)
    {
        return f_record.name.find(m_stringToMatch) != std::string::npos;
    }

    bool DbTableTestStringMatcher::matchBalance(const DbTableTest& f_record)
    {
        return f_record.balance == m_int64tToMatch;
    }

    bool DbTableTestStringMatcher::matchAddress(const DbTableTest& f_record)
    {
        return f_record.address.find(m_stringToMatch) != std::string::npos;
    }
}