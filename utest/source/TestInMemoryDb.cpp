/// @file TestInMemoryDb.cpp
///
/// @brief Unit tests for the InMemoryDb class.
/// @author Ahmed Karaibrahimov
/// @version 1.0
/// @date 6/13/2021
/// @copyright Copyright 2021 Ahmed Karaibrahimov. All rights reserved.
/// @license No license required at all. Use it as you wish.

#include "TestInMemoryDb.hpp"

namespace xq
{
    void InMemoryDbTest::setupTest(uint32_t f_numberOfRecords)
    {
        generateData(f_numberOfRecords);
        m_inMemoryDb = std::make_shared<InMemoryDb>(m_records);
    }

	void InMemoryDbTest::generateData(uint32_t f_numberOfRecords)
	{
        m_records.reserve(f_numberOfRecords);
        for (uint64_t i = 1; i <= f_numberOfRecords; ++i)
        {
            DbTableTest rec{ i, "testdata" + std::to_string(i), static_cast<int32_t>(i), std::to_string(i) + "testdata" };
            m_records.emplace_back(rec);
        }
	}

    /// @brief Test if the In-Memory database is constructed successfully.
    TEST_F(InMemoryDbTest, ConstructionSuccess) 
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        ASSERT_EQ(m_inMemoryDb->getNumberOfRecords(), 100);
    }

    //********** FindMatchingStringOptimized **********//

    /// @brief Test that an existing record with matching id in column0 is found.
    TEST_F(InMemoryDbTest, FindMetchingStringOptimizedColumn0Success)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecordsOptimized("column0", "88", f_output);
        ASSERT_EQ(f_output.size(), 1);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->id, 88);
    }

    /// @brief Test that a record with non-existing id in column0 is not found.
    TEST_F(InMemoryDbTest, FindMetchingStringOptimizedColumn0NotFound)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecordsOptimized("column0", "888", f_output);
        EXPECT_EQ(f_output.size(), 0);
    }

    /// @brief Test that an existing record with matching name in column1 is found.
    TEST_F(InMemoryDbTest, FindMetchingStringOptimizedColumn1Success)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecordsOptimized("column1", "testdata88", f_output);
        ASSERT_EQ(f_output.size(), 1);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->name, "testdata88");
    }

    /// @brief Test that a record with non-existing name in column1 is not found.
    TEST_F(InMemoryDbTest, FindMetchingStringOptimizedColumn1NotFound)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecordsOptimized("column1", "888", f_output);
        EXPECT_EQ(f_output.size(), 0);
    }

    /// @brief Test that an existing record with matching balance in column2 is found.
    TEST_F(InMemoryDbTest, FindMetchingStringOptimizedColumn2Success)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecordsOptimized("column2", "88", f_output);
        ASSERT_EQ(f_output.size(), 1);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->balance, 88);
    }

    /// @brief Test that a record with non-existing balance in column2 is not found.
    TEST_F(InMemoryDbTest, FindMetchingStringOptimizedColumn2NotFound)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecordsOptimized("column2", "888", f_output);
        EXPECT_EQ(f_output.size(), 0);
    }

    /// @brief Test that an existing record with matching address in column3 is found.
    TEST_F(InMemoryDbTest, FindMetchingStringOptimizedColumn3Success)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecordsOptimized("column3", "88testdata", f_output);
        ASSERT_EQ(f_output.size(), 1);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->address, "88testdata");
    }

    /// @brief Test that a record with non-existing balance in column2 is not found.
    TEST_F(InMemoryDbTest, FindMetchingStringOptimizedColumn3NotFound)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecordsOptimized("column3", "888", f_output);
        EXPECT_EQ(f_output.size(), 0);
    }

    /// @brief Test that multiple records matching the given string are found.
    TEST_F(InMemoryDbTest, FindMetchingStringOptimizedMultipleNameSuccess)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecordsOptimized("column1", "testdata", f_output);
        ASSERT_EQ(f_output.size(), 100);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->name, "testdata1");
        EXPECT_EQ(f_output.at(f_output.size()-1)->name, "testdata100");
    }

    /// @brief Test that multiple records matching the given string are found.
    TEST_F(InMemoryDbTest, FindMetchingStringOptimizedMultipleAddressSuccess)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecordsOptimized("column3", "testdata", f_output);
        ASSERT_EQ(f_output.size(), 100);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->address, "1testdata");
        EXPECT_EQ(f_output.at(f_output.size() - 1)->address, "100testdata");
    }

    /// @brief Test that multiple records matching the given string are found.
    /// Testing 10000 Records
    TEST_F(InMemoryDbTest, FindMetchingStringOptimizedMultipleName10000RecordsSuccess)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(10000);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecordsOptimized("column1", "testdata", f_output);
        ASSERT_EQ(f_output.size(), 10000);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->name, "testdata1");
        EXPECT_EQ(f_output.at(f_output.size() - 1)->name, "testdata10000");
    }

    /// @brief Test that multiple records matching the given string are found.
    /// Testing 100000 Records
    TEST_F(InMemoryDbTest, FindMetchingStringOptimizedMultipleName100000RecordsSuccess)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100000);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecordsOptimized("column1", "testdata", f_output);
        ASSERT_EQ(f_output.size(), 100000);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->name, "testdata1");
        EXPECT_EQ(f_output.at(f_output.size() - 1)->name, "testdata100000");
    }

    /// @brief Test that multiple records matching the given string are found.
    /// Testing 1000000 Records
    TEST_F(InMemoryDbTest, FindMetchingStringOptimizedMultipleName1000000RecordsSuccess)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(1000000);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecordsOptimized("column1", "testdata", f_output);
        ASSERT_EQ(f_output.size(), 1000000);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->name, "testdata1");
        EXPECT_EQ(f_output.at(f_output.size() - 1)->name, "testdata1000000");
    }

    //********** FindMatchingString **********//

    /// @brief Test that an existing record with matching id in column0 is found.
    TEST_F(InMemoryDbTest, FindMetchingStringColumn0Success)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column0", "88", f_output);
        ASSERT_EQ(f_output.size(), 1);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->id, 88);
    }

    /// @brief Test that a record with non-existing id in column0 is not found.
    TEST_F(InMemoryDbTest, FindMetchingStringColumn0NotFound)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column0", "888", f_output);
        EXPECT_EQ(f_output.size(), 0);
    }

    /// @brief Test that an existing record with matching name in column1 is found.
    TEST_F(InMemoryDbTest, FindMetchingStringColumn1Success)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column1", "testdata88", f_output);
        ASSERT_EQ(f_output.size(), 1);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->name, "testdata88");
    }

    /// @brief Test that a record with non-existing name in column1 is not found.
    TEST_F(InMemoryDbTest, FindMetchingStringColumn1NotFound)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column1", "888", f_output);
        EXPECT_EQ(f_output.size(), 0);
    }

    /// @brief Test that an existing record with matching balance in column2 is found.
    TEST_F(InMemoryDbTest, FindMetchingStringColumn2Success)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column2", "88", f_output);
        ASSERT_EQ(f_output.size(), 1);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->balance, 88);
    }

    /// @brief Test that a record with non-existing balance in column2 is not found.
    TEST_F(InMemoryDbTest, FindMetchingStringColumn2NotFound)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column2", "888", f_output);
        EXPECT_EQ(f_output.size(), 0);
    }

    /// @brief Test that an existing record with matching address in column3 is found.
    TEST_F(InMemoryDbTest, FindMetchingStringColumn3Success)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column3", "88testdata", f_output);
        ASSERT_EQ(f_output.size(), 1);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->address, "88testdata");
    }

    /// @brief Test that a record with non-existing balance in column2 is not found.
    TEST_F(InMemoryDbTest, FindMetchingStringColumn3NotFound)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column3", "888", f_output);
        EXPECT_EQ(f_output.size(), 0);
    }

    /// @brief Test that multiple records matching the given string are found.
    TEST_F(InMemoryDbTest, FindMetchingStringMultipleNameSuccess)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column1", "testdata", f_output);
        ASSERT_EQ(f_output.size(), 100);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->name, "testdata1");
        EXPECT_EQ(f_output.at(f_output.size() - 1)->name, "testdata100");
    }

    /// @brief Test that multiple records matching the given string are found.
    TEST_F(InMemoryDbTest, FindMetchingStringMultipleAddressSuccess)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column3", "testdata", f_output);
        ASSERT_EQ(f_output.size(), 100);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->address, "1testdata");
        EXPECT_EQ(f_output.at(f_output.size() - 1)->address, "100testdata");
    }

    /// @brief Test that multiple records matching the given string are found.
    /// Testing 10000 Records
    TEST_F(InMemoryDbTest, FindMetchingStringMultipleName10000RecordsSuccess)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(10000);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column1", "testdata", f_output);
        ASSERT_EQ(f_output.size(), 10000);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->name, "testdata1");
        EXPECT_EQ(f_output.at(f_output.size() - 1)->name, "testdata10000");
    }

    /// @brief Test that multiple records matching the given string are found.
    /// Testing 100000 Records
    TEST_F(InMemoryDbTest, FindMetchingStringMultipleName100000RecordsSuccess)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100000);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column1", "testdata", f_output);
        ASSERT_EQ(f_output.size(), 100000);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->name, "testdata1");
        EXPECT_EQ(f_output.at(f_output.size() - 1)->name, "testdata100000");
    }

    /// @brief Test that multiple records matching the given string are found.
    /// Testing 1000000 Records
    TEST_F(InMemoryDbTest, FindMetchingStringMultipleName1000000RecordsSuccess)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(1000000);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column1", "testdata", f_output);
        ASSERT_EQ(f_output.size(), 1000000);
        ASSERT_NE(f_output.at(0), nullptr);
        EXPECT_EQ(f_output.at(0)->name, "testdata1");
        EXPECT_EQ(f_output.at(f_output.size() - 1)->name, "testdata1000000");
    }

    //********** DeleteRecordsByID **********//

    /// @brief Test deleting record by ID optimized.
    TEST_F(InMemoryDbTest, DeleteRecordByIDSuccess)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        m_inMemoryDb->deleteRecordByID(88);
        EXPECT_EQ(m_inMemoryDb->getNumberOfDeletedRecords(), 1);
        EXPECT_EQ(m_inMemoryDb->getNumberOfRecords(), 99);

        // Verify that the record is not available anymore after it was deleted
        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column1", "testdata88", f_output);
        ASSERT_EQ(f_output.size(), 0);
    }

    /// @brief Test deleting record by ID that is not found - optimized.
    TEST_F(InMemoryDbTest, DeleteRecordByIDNotFound)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        m_inMemoryDb->deleteRecordByID(888);
        EXPECT_EQ(m_inMemoryDb->getNumberOfDeletedRecords(), 0);
        EXPECT_EQ(m_inMemoryDb->getNumberOfRecords(), 100);
    }

    //********** DeleteRecordByIDNonOptimized **********//

    /// @brief Test deleting record by ID.
    TEST_F(InMemoryDbTest, DeleteRecordByIDNonOptimizedSuccess)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        m_inMemoryDb->deleteRecordByIDNonOptimized(88);
        EXPECT_EQ(m_inMemoryDb->getNumberOfDeletedRecords(), 0);
        EXPECT_EQ(m_inMemoryDb->getNumberOfRecords(), 99);

        // Verify that the record is not available anymore after it was deleted
        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column1", "testdata88", f_output);
        ASSERT_EQ(f_output.size(), 0);
    }

    /// @brief Test deleting record by ID that is not found.
    TEST_F(InMemoryDbTest, DeleteRecordByIDNonOptimizedNotFound)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        m_inMemoryDb->deleteRecordByIDNonOptimized(888);
        EXPECT_EQ(m_inMemoryDb->getNumberOfDeletedRecords(), 0);
        EXPECT_EQ(m_inMemoryDb->getNumberOfRecords(), 100);
    }

    //********** AddRecord **********//

    /// @brief Test adding a new record without any old record to be deleted.
    TEST_F(InMemoryDbTest, AddRecordWithoutDelete)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        DbTableTest testRecord{101, "testdata101", 101, "101testdata"};

        m_inMemoryDb->addRecord(testRecord);
        EXPECT_EQ(m_inMemoryDb->getNumberOfDeletedRecords(), 0);
        EXPECT_EQ(m_inMemoryDb->getNumberOfRecords(), 101);

        // Verify that the new record is available
        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column1", "testdata101", f_output);
        ASSERT_EQ(f_output.size(), 1);
    }

    /// @brief Test adding a new record after deleting an old one.
    TEST_F(InMemoryDbTest, AddRecordWithDelete)
    {
        // Initial setup of the test. Verify that the In-memory
        // database object is constructed successfully.
        setupTest(100);
        ASSERT_NE(m_inMemoryDb, nullptr);

        m_inMemoryDb->deleteRecordByID(88);

        DbTableTest testRecord{ 101, "testdata101", 101, "101testdata" };
        m_inMemoryDb->addRecord(testRecord);
        EXPECT_EQ(m_inMemoryDb->getNumberOfDeletedRecords(), 0);
        EXPECT_EQ(m_inMemoryDb->getNumberOfRecords(), 100);

        // Verify that the new record is available
        DbTestRecordPointersCollection f_output{};

        m_inMemoryDb->findMatchingRecords("column1", "testdata101", f_output);
        ASSERT_EQ(f_output.size(), 1);
    }
}

