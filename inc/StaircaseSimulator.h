/*
 * StaircaseSimulator.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef STAIRCASESIMULATOR_H_
#define STAIRCASESIMULATOR_H_

class StaircaseSimulator {


	// make private, as singleton
	StaircaseSimulator();
	StaircaseSimulator(StaircaseSimulator &) = default;
	StaircaseSimulator & operator=(StaircaseSimulator &) = default;

public:
	virtual ~StaircaseSimulator();
	static StaircaseSimulator & GetInstance(void);
};

#endif /* STAIRCASESIMULATOR_H_ */
