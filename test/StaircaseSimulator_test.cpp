/*
 * StaircaseSimulator_test.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#include "StaircaseSimulator.h"
#include "gtest/gtest.h"

TEST(stairSim, init) {
	StaircaseSimulator & scs = StaircaseSimulator::GetInstance();

}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
