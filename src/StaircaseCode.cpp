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
	simParams = dm.getSimulationParams();
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

void StaircaseCodeNS::StaircaseCode::firstBlocks(
		const NoiseGeneratorNS::NoiseGenerator& ng) {
	// reset counters at new channel parameter
	resetErrorCounters();
	nextBlock(ng);
}

void StaircaseCodeNS::StaircaseCode::incrementBlocksDecoded(void) {
	++nBlocksDecoded;
}

void StaircaseCodeNS::StaircaseCode::nextBlock(
		const NoiseGeneratorNS::NoiseGenerator& ng) {
	// pop decoded block
	blocks.pop_front();

	// sample noise
	uint32_t nSamples = params.nBlockBits;	// one block
	std::vector<uint32_t> noise;
	ng.generate(nSamples, noise);

	// populate new block with noise
	Block newBlock;
	for(int i = 0; i < params.width; i++) {
		newBlock.rowErrPos.push_back(std::vector<int>());
		newBlock.colErrPos.push_back(std::vector<int>());
	}
	for(uint32_t e : noise) {
		/*
		 * blocks are populated from noise array
		 * row-by-row, left-to-right in each row
		 *
		 */
		int rowInd = (e % params.nBlockBits) / params.width;
		int colInd = (e % params.nBlockBits) % params.width;
		newBlock.rowErrPos[rowInd].push_back(colInd);
		newBlock.colErrPos[colInd].push_back(rowInd);
	}

	// push into blocks
	blocks.push_back(newBlock);

//	for(int i = 0; i < params.nBlocks; i++) {
//		printf("----- block %d -----\n", i);
//		blocks[i].print();	// debug
//	}

	decode();
	incrementBlocksDecoded();

//	for(int i = 0; i < params.nBlocks; i++) {
//		printf("----- block %d -----\n", i);
//		blocks[i].print();	// debug
//	}

	countErrors();
	updateConverged();
}

void StaircaseCodeNS::StaircaseCode::resetErrorCounters() {
	nBlocksDecoded = 0;
	nTotalBitErrors = 0;
	nTotalBlockErrors = 0;
	ber = 0.0;
	bker = 0.0;
}

void StaircaseCodeNS::StaircaseCode::countErrors() {
	std::vector<std::vector<int>> &rowErrors = blocks.front().rowErrPos;	// get errors in 1st block
	unsigned int errors = 0;
	for (auto iter = rowErrors.begin(); iter != rowErrors.end(); iter++) {
		errors += iter->size();
	}
	if(errors > 0) {
		++nTotalBlockErrors;
		nTotalBitErrors += errors;
	}

	ber = static_cast<double>(nTotalBitErrors) / static_cast<double>(nBlocksDecoded * params.width * params.width);
	bker = static_cast<double>(nTotalBlockErrors) / static_cast<double>(nBlocksDecoded);

	if(nBlocksDecoded % params.reportInterval == 0) {
		printf("%lu blocks decoded, %u %u %02.4e %02.4e\n",
				nBlocksDecoded, nTotalBitErrors, nTotalBlockErrors, ber, bker);
	}
}

void StaircaseCodeNS::StaircaseCode::updateConverged() {
//	converged = true;	// debug
	converged = (nBlocksDecoded >= simParams.blocksMax) ||			// max blocks reached
				(nTotalBlockErrors >= simParams.blocksMin);				// min block errors reached
}

//static void printErrorVector(std::vector<int> &vec, const char *vecName) {	// debugging
//	printf("%s [", vecName);
//	for(int i = 0; i < (int)vec.size(); i++) {
//		printf("%d ", vec[i]);
//	}
//	printf("] (%lu)\n", vec.size());
//}

static std::vector<int> emptyVec;
void StaircaseCodeNS::StaircaseCode::decode(void) {
	for (int iteration = 0; iteration < params.maxIters; iteration++) {
//		printf("iteration: %d\n", iteration);	// debugging

		// decode blocks [0, .., params.nBlocks - 2]
		for (int blkInd = 0; blkInd < (int) params.nBlocks - 1; blkInd++) {
			for (int codeInd = 0; codeInd < (int) params.width; codeInd++) {
//				printf("blkInd, codeInd: %d, %d\n", blkInd, codeInd);	// debugging

				// get error positions on left and right of component code
				// note: right error positions have NOT been adjusted by params.width
				std::vector<int> &left = getLeftErrorVector(blkInd, codeInd);
				std::vector<int> &right = getRightErrorVector(blkInd, codeInd);	// not adjusted, yet

//				printErrorVector(left, "left");	// debugging
//				printErrorVector(right, "right");	// debugging

				uint16_t nErrors = 0;
				nErrors = left.size() + right.size();
				if (nErrors <= cc.getParams().t) {
					// guaranteed correction, remove all errors
					updateErrors(blkInd, codeInd, left, emptyVec,
							isDecodeRows(blkInd));
					updateErrors(blkInd + 1, codeInd, right, emptyVec,
							isDecodeRows(blkInd));
				} else {
					std::vector<int> errorLocs;
					for (int &le : left) {		// add left errors
						errorLocs.push_back(le);
					}
					for (int &re : right) {
						errorLocs.push_back(params.width + re);	//	add right errors, with width offset
					}
					std::vector<int> flipLocs;
					int nDec = cc.decode(errorLocs, flipLocs);
					if (nDec >= 1) {
						// bit flips occurred, first, removed errors if any
						for (auto iter = errorLocs.begin();
								iter != errorLocs.end();) {
							auto iter2 = std::find(flipLocs.begin(),
									flipLocs.end(), *iter);
							if (iter2 != flipLocs.end()) {
								// error is in flip list, remove from both
								iter = errorLocs.erase(iter);
								flipLocs.erase(iter2);
							} else {
								++iter;
							}
						}

						// add new errors, if any
						if (!flipLocs.empty()) {
							for (auto iter = flipLocs.begin();
									iter != flipLocs.end();) {
								errorLocs.push_back(*iter);
								iter = flipLocs.erase(iter);
							}
						}
						assert(flipLocs.size() == 0);
						// populate new left and right errors after decoding
						std::vector<int> leftNew;
						std::vector<int> rightNew;
						for (int &e : errorLocs) {
							if (e < params.width) {
								leftNew.push_back(e);		// add left errors
							} else {
								rightNew.push_back(e - params.width);// add right errors, without width offset
							}
						}

//						printErrorVector(leftNew, "new left");	// debugging
//						printErrorVector(rightNew, "new right");	// debugging

						// update (remove or add) errors
						updateErrors(blkInd, codeInd, left, leftNew,
								isDecodeRows(blkInd));
						updateErrors(blkInd + 1, codeInd, right, rightNew,
								isDecodeRows(blkInd));
					}
				}
			} /* codes loop */
		} /* blocks loop */
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
		vecOld.push_back(*iterNew);
		addErrorToBlock(blkInd, codeInd, *iterNew, decodeRows);
		vecNew.erase(iterNew);
	}
//	printf(
//			"leaving update errors, blk %d, code %d, row/col %d, old len %lu, new len %lu\n",
//			blkInd, codeInd, decodeRows, vecOld.size(), vecNew.size());
}

/**
 * remove error from the transposed representation
 * of errors in the block, i.e.,
 * if called from rows, column errors are removed, and vice versa
 *
 */
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
		blocks[blkInd].colErrPos[e].push_back(codeInd);
	} else {
		blocks[blkInd].rowErrPos[e].push_back(codeInd);
	}
//	printf("leaving add error\n");
}
