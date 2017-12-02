/*
 * ParamStructures.h
 *
 *  Created on: Nov 29, 2017
 *      Author: leizhang
 */

#ifndef INC_PARAMSTRUCTURES_H_
#define INC_PARAMSTRUCTURES_H_

#include <cstdint>
#include <cstdio>
#include <string>

namespace ComponentCodeNS {

struct Params {
	uint16_t nC;	// un-shortened length
	uint16_t kC; 	// un-shortened dimension
	uint16_t n;		// length
	uint16_t k;		// dimension
	uint16_t s;		// shorten

	uint16_t m;		// field extension degree

	uint16_t d;		// min distance
	uint16_t t;		// unique correction radius

	bool isValid = false;

	Params() :
		nC(0), kC(0), n(0), k(0), t(0) {
		s = 0;
		m = 0;
		d = 0;
	}

	Params(int _nC, int _kC, int _t, int _s = 0) :
			Params() {
		nC = _nC;
		kC = _kC;
		t = _t;
		s = _s;

		// validate and populate remaining
		isValid = validateParams();
		if (isValid) {
			populateParams();
		}
	}

	/*
	 * validate code parameters
	 */
	bool validateParams(void);

	/*
	 * populate dependent parameters from internal values
	 * of nC, kC, t, and s
	 *
	 * return:
	 * 0, success
	 * -1, error, likely input parameters are invalid
	 *
	 * note: remember to set nC, kC, t, and s before call
	 *
	 */
	int populateParams(void);

	std::string ToString(void);

};

}

namespace StaircaseCodeNS {

struct Params {
	int width;
	int nBlocks;
	int maxIters;

	uint32_t nBlockBits;
	uint32_t nTotalBits;

	bool isValid = false;

	Params() :
		width(0),
		nBlocks(0),
		maxIters(0),
		nBlockBits(0),
		nTotalBits(0) {
	}

	Params(const int _w, const int _nb, const int _mi) :
		width(_w),
		nBlocks(_nb),
		maxIters(_mi){
		isValid = validateParams();
		nBlockBits = width * width;
		nTotalBits = nBlockBits * nBlocks;
	}

	bool validateParams(void);
};

}

/* simulation parameters */
struct Params {
	double pMin;
	double pMax;
	double pStep;
	int blocksMin;
	int blocksMax;

	Params() :
		pMin(0.0),
		pMax(0.0),
		pStep(0.1),
		blocksMin(0),
		blocksMax(0) {
	}

	Params(double _pMin, double _pMax, double _pStep, int _blocksMin, int _blocksMax) :
		pMin(_pMin),
		pMax(_pMax),
		pStep(_pStep),
		blocksMin(_blocksMin),
		blocksMax(_blocksMax) {

	}
};

#endif /* INC_PARAMSTRUCTURES_H_ */
