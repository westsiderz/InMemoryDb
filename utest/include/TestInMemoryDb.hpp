/// @file TestInMemoryDb.hpp
///
/// @brief Unit tests for the InMemoryDb class.
/// @author Ahmed Karaibrahimov
/// @version 1.0
/// @date 6/13/2021
/// @copyright Copyright 2021 Ahmed Karaibrahimov. All rights reserved.
/// @license No license required at all. Use it as you wish.

#ifndef TEST_IN_MEMORY_DB_HPP
#define TEST_IN_MEMORY_DB_HPP

#include "gtest/gtest.h"
#include "InMemoryDb.hpp"

namespace xq
{
    /// @class InMemoryDbTest
    /// @brief Test Fixture for the InMemoryDb.
    class InMemoryDbTest : public ::testing::Test {
    protected:

        /// @brief Setup the required data for the test.
        /// @param[]in f_numberOfRecords The number of records to be created for the test.
        void setupTest(uint32_t f_numberOfRecords);

        std::shared_ptr<InMemoryDb> m_inMemoryDb; ///< Handle for the In-memory database

    private:
        /// @brief Generates test data.
        /// @details Generates test data to be used for testing the algorithms and store it in a collection. 
        /// @param[in] f_numberOfRecords The number of records to be generated.
        void generateData(uint32_t f_numberOfRecords);

        DbTestRecordCollection m_records{}; ///< Collection of records
    };
}

#endif // !TEST_IN_MEMORY_DB_HPP



