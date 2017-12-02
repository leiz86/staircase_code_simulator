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
	if(blocks != NULL) {
		delete[] blocks;
		blocks = NULL;
	}
}

void StaircaseCode::init(const DataManager& dm) {
	params = dm.getStaircaseCodeParams();
	initBlocks();
}

void StaircaseCode::initBlocks(void) {
	blocks = new Block[params.nBlocks];

}
