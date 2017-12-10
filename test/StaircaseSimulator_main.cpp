/*
 * StaircaseSimulator_main.cpp
 *
 *  Created on: Dec 10, 2017
 *      Author: leizhang
 */

#include "StaircaseSimulator.h"

int main(int argc, char **argv) {
	StaircaseSimulator & scs = StaircaseSimulator::GetInstance();

	const char testOpts[] = "test";
	scs.init(testOpts);

	scs.run(0);
	scs.report(0);

	return 0;
}
