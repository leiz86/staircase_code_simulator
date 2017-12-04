/*
 * StaircaseCode.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#include <algorithm>
#include <cassert>

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

static inline bool isDecodeRows(const int ind) {
	return (ind % 2) == 0;
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

	for(int i = 0; i < params.nBlocks; i++) {
		printf("----- block %d -----\n", i);
		blocks[i].print();	// debug
	}

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

static std::vector<int> emptyVec;

void StaircaseCodeNS::StaircaseCode::decode(void) {
	for (int iter = 0; iter < params.maxIters; iter++) {
		// decode blocks [0, .., params.nBlocks - 2]
		for (int blkInd = 0; blkInd < (int) params.nBlocks - 1; blkInd++) {
			for (int codeInd = 0; codeInd < (int) params.width; codeInd++) {
				// get error positions on left and right of component code
				// note: right error positions have NOT been adjusted by params.width
				std::vector<int> &left = getLeftErrorVector(blkInd, codeInd);
				std::vector<int> &right = getRightErrorVector(blkInd, codeInd);	// not adjusted, yet

				uint16_t nErrors = 0;
				nErrors = left.size() + right.size();
				if(nErrors <= cc.getParams().t) {
					// guaranteed correction, remove all errors
					updateErrors(blkInd, codeInd, left, emptyVec, isDecodeRows(blkInd));
					updateErrors(blkInd + 1, codeInd, right, emptyVec, isDecodeRows(blkInd));
				}
				// todo: use syndrome decoder
//				else {
//					// call decoder
//
//
//					std::vector<int> leftNew;
//					std::vector<int> rightNew;
//					// update (remove or add) errors
//					updateErrors(blkInd, codeInd, left, leftNew, isDecodeRows(blkInd));
//					updateErrors(blkInd + 1, codeInd, right, rightNew, isDecodeRows(blkInd));
//				}
			} /* codes loop */
		} /* blocks loop */

		// todo: early termination
	}

}

std::vector<int> & StaircaseCodeNS::StaircaseCode::getLeftErrorVector(int blkInd, int codeInd) {
	if (isDecodeRows(blkInd)) {
		return blocks[blkInd].rowErrPos[codeInd];
	} else {
		return blocks[blkInd].colErrPos[codeInd];
	}
}

std::vector<int> & StaircaseCodeNS::StaircaseCode::getRightErrorVector(int blkInd, int codeInd) {
	if (isDecodeRows(blkInd)) {
		return blocks[blkInd + 1].rowErrPos[codeInd];
	} else {
		// columns first
		return blocks[blkInd + 1].colErrPos[codeInd];
	}
}

/*
 * function updates block from vecOld to vecNew
 *
 * inputs:
 * blkInd, index of left block
 * codeInd, index of component code to update
 * vecOld, ref to error array before decoding
 * vecNew, ref to error array after decoding
 *
 * note:
 * updates are done by references to both
 * row and column error vectors in blocks,
 * i.e., nothing is copied, careful with remove and erase
 *
 *
 */
void StaircaseCodeNS::StaircaseCode::updateErrors(const int blkInd,
		const int codeInd, std::vector<int>& vecOld, std::vector<int>& vecNew,
		bool decodeRows) {
//	printf(
//			"inside update errors, blk %d, code %d, row/col %d, old len %lu, new len %lu\n",
//			blkInd, codeInd, decodeRows, vecOld.size(), vecNew.size());
	if (blkInd < 0 || blkInd > (params.nBlocks - 1) || codeInd < 0
			|| codeInd >= params.width) {
		// wrong indices
		printf(
				"SC ERR: update errors: wrong indices given blk %d (max %d), code %d (max %d)\n",
				blkInd, params.nBlocks, codeInd, params.width);
		return;
	}

	// remove errors from old, if any
	for (auto iterOld = vecOld.begin(); iterOld != vecOld.end();) {
		auto iterNew = std::find(vecNew.begin(), vecNew.end(), *iterOld);
		if (iterNew == vecNew.end()) {
			// old error is not found in new, remove it
			removeErrorFromBlock(blkInd, codeInd, *iterOld, decodeRows);
			iterOld = vecOld.erase(iterOld);
		} else {
			// old error is in new, remove it from new to save redundant search
			vecNew.erase(iterNew);
			++iterOld;
		}
	}

	// add new errors, if any
	for (auto iterNew = vecNew.begin(); iterNew != vecNew.end();) {
		addErrorToBlock(blkInd, codeInd, *iterNew, decodeRows);
		vecOld.push_back(*iterNew);
		vecNew.erase(iterNew);
	}
//	printf(
//			"leaving update errors, blk %d, code %d, row/col %d, old len %lu, new len %lu\n",
//			blkInd, codeInd, decodeRows, vecOld.size(), vecNew.size());
}

void StaircaseCodeNS::StaircaseCode::removeErrorFromBlock(const int blkInd,
		const int codeInd, const int e, bool decodeRows) {
//	printf("inside remove error, %d %d %d %d\n", blkInd, codeInd, e, decodeRows);
	if (decodeRows) {
		// remove column errors
		int i = codeInd;
		int j = e;
		std::vector<int> &vec = blocks[blkInd].colErrPos[j];
		auto iter = std::remove(vec.begin(), vec.end(), i);
		assert(iter != vec.end());	// debug
		vec.erase(iter, vec.end());
	} else {
		// remove row errors
		int i = e;
		int j = codeInd;
		std::vector<int> &vec = blocks[blkInd].rowErrPos[i];
		auto iter = std::remove(vec.begin(), vec.end(), j);
		assert(iter != vec.end());	// debug
		vec.erase(iter, vec.end());
	}
//	printf("leaving remove error\n");
}

void StaircaseCodeNS::StaircaseCode::addErrorToBlock(const int blkInd,
		const int codeInd, const int e, bool decodeRows) {
//	printf("inside add error, %d %d %d %d\n", blkInd, codeInd, e, decodeRows);
	if (decodeRows) {
		blocks[blkInd].rowErrPos[codeInd].push_back(e);
	} else {
		blocks[blkInd].colErrPos[codeInd].push_back(e);
	}
//	printf("leaving add error\n");
}
