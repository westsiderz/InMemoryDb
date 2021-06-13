/// @file TestDbTableTest.cpp
///
/// @brief Unit tests for the DbTableTestStringMatcher class.
/// @author Ahmed Karaibrahimov
/// @version 1.0
/// @date 6/13/2021
/// @copyright Copyright 2021 Ahmed Karaibrahimov. All rights reserved.
/// @license No license required at all. Use it as you wish.

#include "gtest/gtest.h"
#include "DbTableTest.hpp"

/// @brief Test that the matcher can match an ID column
TEST(DbTableTest, MatchIdSuccess) 
{
	xq::DbTableTestStringMatcher stringMatcher{ "column0", "88" };
	xq::DbTableTest record{ 88, "testdata88", 1988, "88testdata" };

	EXPECT_EQ(stringMatcher.checkMatching(record), true);
}

/// @brief Test that the matcher cannot match a wrong ID
TEST(DbTableTest, MatchIdFail)
{
	xq::DbTableTestStringMatcher stringMatcher{ "column0", "1988" };
	xq::DbTableTest record{ 88, "testdata88", 1988, "88testdata" };

	EXPECT_EQ(stringMatcher.checkMatching(record), false);
}

/// @brief Test that the matcher can match a name column
TEST(DbTableTest, MatchNameSuccess)
{
	xq::DbTableTestStringMatcher stringMatcher{ "column1", "testdata88" };
	xq::DbTableTest record{ 88, "testdata88", 1988, "88testdata" };

	EXPECT_EQ(stringMatcher.checkMatching(record), true);
}

/// @brief Test that the matcher cannot match a wrong name
TEST(DbTableTest, MatchNameFail)
{
	xq::DbTableTestStringMatcher stringMatcher{ "column1", "testdata1988" };
	xq::DbTableTest record{ 88, "testdata88", 1988, "88testdata" };

	EXPECT_EQ(stringMatcher.checkMatching(record), false);
}

/// @brief Test that the matcher can match a balance column
TEST(DbTableTest, MatchBalanceSuccess)
{
	xq::DbTableTestStringMatcher stringMatcher{ "column2", "1988" };
	xq::DbTableTest record{ 88, "testdata88", 1988, "88testdata" };

	EXPECT_EQ(stringMatcher.checkMatching(record), true);
}

/// @brief Test that the matcher cannot match a wrong balance
TEST(DbTableTest, MatchBalanceFail)
{
	xq::DbTableTestStringMatcher stringMatcher{ "column2", "88" };
	xq::DbTableTest record{ 88, "testdata88", 1988, "88testdata" };

	EXPECT_EQ(stringMatcher.checkMatching(record), false);
}

/// @brief Test that the matcher can match an address column
TEST(DbTableTest, MatchAddressSuccess)
{
	xq::DbTableTestStringMatcher stringMatcher{ "column3", "88testdata" };
	xq::DbTableTest record{ 88, "testdata88", 1988, "88testdata" };

	EXPECT_EQ(stringMatcher.checkMatching(record), true);
}

/// @brief Test that the matcher cannot match a wrong address
TEST(DbTableTest, MatchAddressFail)
{
	xq::DbTableTestStringMatcher stringMatcher{ "column3", "1988testdata" };
	xq::DbTableTest record{ 88, "testdata88", 1988, "88testdata" };

	EXPECT_EQ(stringMatcher.checkMatching(record), false);
}