/*
 * StaircaseSimulator.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef STAIRCASESIMULATOR_H_
#define STAIRCASESIMULATOR_H_

#include <cstddef>

class StaircaseSimulator {
	DataManager *dm = NULL;
	NoiseGenerator *ng = NULL;
	StaircaseCode *sc = NULL;

	// make private, as singleton
	StaircaseSimulator();
	StaircaseSimulator(StaircaseSimulator &) = default;
	StaircaseSimulator & operator=(StaircaseSimulator &) = default;

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
	 * state, select run state, can be:
	 * 	0, run until converged
	 * 	1, run 1 iteration (testing)
	 * 	2, ... and above are not currently used
	 *
	 * return:
	 * 0, success
	 * -1, error
	 *
	 */
	int run(int state);
};

#endif /* STAIRCASESIMULATOR_H_ */
