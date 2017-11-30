/*
 * StaircaseCode.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#include <StaircaseCode.h>

using namespace StaircaseCodeNS;

StaircaseCode::StaircaseCode() {

}

StaircaseCode::~StaircaseCode() {
	if(scBlocks != NULL) {
		delete[] scBlocks;
		scBlocks = NULL;
	}
	nScBlocks = 0;
}

void StaircaseCode::init(DataManager& dm) {
	Params &params = dm.getStaircaseCodeParams();
	createBlocks(params.nBlocks, params.width);
	maxIters = params.maxIters;
}

void StaircaseCode::createBlocks(const int _nBlocks, const int _width) {
	scBlocks = new Block[_nBlocks];
	// todo: use the _width parameter to set each block

	nScBlocks = _nBlocks;
}
