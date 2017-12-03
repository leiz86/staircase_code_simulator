/*
 * StaircaseSimulator_test.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#include "StaircaseSimulator.h"
#include "gtest/gtest.h"

TEST(stairSim, run) {
	StaircaseSimulator & scs = StaircaseSimulator::GetInstance();

	const char testOpts[] = "test";
	scs.init(testOpts);

	scs.run(0);
	scs.report(0);
}

// todo: set up test cases for codes with different parameters and verify results (within tolerance)


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
