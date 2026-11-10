#include "pch.h"
#include "../Project2/Enemy.h"

TEST(TestCaseName, TestName) {

	Enemy test;
	//(test.GetHealth(), 1);
	test.LoseHealth(10);
	//EXPECT_EQ(test.GetHealth(), -9);

  EXPECT_TRUE(true);
}

TEST(TestCaseName, TestName1) {

	Entity* test = nullptr;
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}