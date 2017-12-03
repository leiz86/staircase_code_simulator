/*
 * StaircaseCode.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#include "StaircaseCode.h"

using namespace StaircaseCodeNS;

StaircaseCode::StaircaseCode() :
	ber(0.0),
	bker(0.0) {
}

StaircaseCode::~StaircaseCode() {
}

void StaircaseCode::init(const DataManager& dm) {
	params = dm.getStaircaseCodeParams();
	cc.setParams(dm.getComponentCodeParams());
	initBlocks();
}

void StaircaseCode::initBlocks(void) {
	for(int i = 0; i < params.nBlocks; i++) {
		blocks.push_back(Block());
		for(int j = 0; j < params.width; j++) {
			blocks[i].rowErrPos.push_back(std::vector<int>());
			blocks[i].colErrPos.push_back(std::vector<int>());
		}
	}
}

void StaircaseCodeNS::StaircaseCode::firstIteration(
		const NoiseGeneratorNS::NoiseGenerator& ng) {
	// sample noise
	uint32_t nSamples = params.nTotalBits - params.nBlockBits;	// all except first block, which is not transmitted
	std::vector<uint32_t> noise;
	ng.generate(nSamples, noise);

	// populate blocks with noise
	for(uint32_t e : noise) {
		int blockInd = e / params.nBlockBits + 1;	// +1 to skip first block
		/*
		 * blocks are populated from noise array
		 * row-by-row, left-to-right in each row
		 *
		 */
		int rowInd = (e % params.nBlockBits) / params.width;
		int colInd = (e % params.nBlockBits) % params.width;
		blocks[blockInd].rowErrPos[rowInd].push_back(colInd);
		blocks[blockInd].colErrPos[colInd].push_back(rowInd);
	}

	for(int i = 0; i < params.nBlocks; i++) {
		printf("----- block %d -----\n", i);
		blocks[i].print();	// debug
	}

	// decode
	decode();


	// tabulate errors

	// update convergence criteria
	converged = true;	// debug
}

void StaircaseCodeNS::StaircaseCode::nextIteration(
		const NoiseGeneratorNS::NoiseGenerator& ng) {
	// sample noise for last (new block), pop_front + push_back

	// decode

	// tabulate errors

	// update convergence criteria

	// (clearly the last 2 functions can be combined)
}

void StaircaseCodeNS::StaircaseCode::decode(void) {
	for (int iter = 0; iter < params.maxIters; iter++) {
		// decode blocks from oldest to newest
		for (int blkInd = 0; blkInd < (int) params.nBlocks - 1; blkInd++) {
			for (int codeInd = 0; codeInd < (int) params.width; codeInd++) {
				// get error positions on left and right of component code
				// note: right error positions have NOT been adjusted by params.width
				std::vector<int> &left = getLeftErrorVector(blkInd, codeInd);
				std::vector<int> &right = getRightErrorVector(blkInd, codeInd);	// not adjusted, yet

				uint16_t nErrors = 0;
				nErrors = left.size() + right.size();
				if(nErrors <= cc.params.t) {
					// no need to call decoder, remove errors
					removeErrors();
					// todo: start here
				} else {
					// call decoder

					// add errors

					// remove errors
					removeErrors();

				}
			} /* codes loop */
		} /* blocks loop */

		// todo: early termination
	}

}

std::vector<int> & StaircaseCodeNS::StaircaseCode::getLeftErrorVector(int blkInd, int codeInd) {
	if ((blkInd % 2) == 0) {
		// rows first
		return blocks[blkInd].rowErrPos[codeInd];
	} else {
		// columns first
		return blocks[blkInd].colErrPos[codeInd];
	}
}

std::vector<int> & StaircaseCodeNS::StaircaseCode::getRightErrorVector(int blkInd, int codeInd) {
	if ((blkInd % 2) == 0) {
		// rows first
		return blocks[blkInd + 1].colErrPos[codeInd];
	} else {
		// columns first
		return blocks[blkInd + 1].rowErrPos[codeInd];
	}
}
