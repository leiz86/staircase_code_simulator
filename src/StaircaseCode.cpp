/*
 * StaircaseCode.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#include <StaircaseCode.h>

using namespace StaircaseCodeNS;

StaircaseCode::StaircaseCode() :
	ber(0.0),
	bker(0.0) {
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
	for(int i = 0; i < params.nBlocks; i++) {
		// populate each block with empty keys for each row and column
		for(int j = 0; j < params.width; j++) {
			blocks[i].rowErrPos.insert(std::pair<int, std::vector<int>>(j, std::vector<int>()));
			blocks[i].colErrPos.insert(std::pair<int, std::vector<int>>(j, std::vector<int>()));
		}
	}
}
