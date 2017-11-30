/*
 * ParamStructures.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: leizhang
 */

#include <cmath>

#include "ParamStructures.h"

bool ComponentCodeNS::Params::validateParams(void) {
	// todo: validate parameters
	return true;
}

int ComponentCodeNS::Params::populateParams(void) {
	if(!validateParams()) {
		return -1;
	}

	n = nC - s;
	k = kC - s;
	d = t * 2 + 1;
	m = (uint16_t) log2((double) (nC + 1));

	return 0;
}

bool StaircaseCodeNS::Params::validateParams(void) {
	return width > 0 && nBlocks > 0 && maxIters > 0;
}
