/*
 * StaircaseSimulator.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef STAIRCASESIMULATOR_H_
#define STAIRCASESIMULATOR_H_

#include <cstddef>

#include "DataManager.h"
#include "NoiseGenerator.h"
#include "StaircaseCode.h"

class StaircaseSimulator {
	DataManager dm;
	NoiseGeneratorNS::NoiseGenerator ng;
	StaircaseCodeNS::StaircaseCode sc;

	// make private, as singleton
	StaircaseSimulator();
	StaircaseSimulator(StaircaseSimulator &) = default;
	StaircaseSimulator & operator=(StaircaseSimulator &) = default;

	void runAtChannel(double p, double &ber, double &bker);

public:
	virtual ~StaircaseSimulator();
	static StaircaseSimulator & GetInstance(void);

	/*
	 * function to initialize simulator
	 *
	 * inputs:
	 * opts, c-string of input options from command line
	 *
	 * return:
	 * 0, success
	 * -1, error
	 *
	 */
	int init(const char *opts);

	/*
	 * function runs staircase simulator
	 *
	 * inputs:
	 * type, select run type:
	 * 	0, run until converged
	 * 	1, run 1 iteration (testing)
	 *  >=2, reserved for future use
	 *
	 * return:
	 * 0, success
	 * -1, error
	 *
	 */
	int run(int type);

	/*
	 * function reports simulation results
	 *
	 * input:
	 * type, select report type:
	 * 0, print
	 * 1, save to file
	 * >=2, reserved for future use
	 *
	 * return:
	 * 0, success
	 * -1, error, e.g., file IO error
	 *
	 */
	int report(int type);
};

#endif /* STAIRCASESIMULATOR_H_ */
