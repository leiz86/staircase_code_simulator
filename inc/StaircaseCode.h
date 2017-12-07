/*
 * StaircaseCode.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef INC_STAIRCASECODE_H_
#define INC_STAIRCASECODE_H_

#include <cstddef>
#include <cstdio>
#include <deque>
#include <vector>

#include "ComponentCode.h"
#include "DataManager.h"
#include "NoiseGenerator.h"

namespace StaircaseCodeNS {

struct Block {
	std::vector<std::vector<int>> rowErrPos;	// row error positions
	std::vector<std::vector<int>> colErrPos;	// column error positions

	void print(void) {
		printf("----- rows -----\n");
		for (int i = 0; i < (int) rowErrPos.size(); i++) {
			printf("%04d (%02lu):", i, rowErrPos[i].size());
			for (int j : rowErrPos[i]) {
				printf("%d ", j);
			}
			printf("\n");
		}
		printf("----- end rows ----- \n");
		printf("----- cols -----\n");
		for (int i = 0; i < (int) colErrPos.size(); i++) {
			printf("%04d (%02lu):", i, colErrPos[i].size());
			for (int j : colErrPos[i]) {
				printf("%d ", j);
			}
			printf("\n");
		}
		printf("----- end cols ----- \n");
	}
};

class StaircaseCode {
	Params params;
	SimulationNS::Params simParams;
	ComponentCodeNS::ComponentCode cc;
	std::deque<Block> blocks;

	uint64_t nBlocksDecoded = 0;
	uint32_t nBitErrors = 0;
	uint32_t nBlockErrors = 0;

	double ber;
	double bker;

	bool converged = false;

	void initBlocks(void);
	void resetErrorCounters(void);
	void countErrors(void);
	void updateConverged(void);
	void decode(void);
	void incrementBlocksDecoded(void);
	std::vector<int> & getLeftErrorVector(int, int);
	std::vector<int> & getRightErrorVector(int, int);
	void updateErrors(const int blkInd, const int codeInd,
			std::vector<int> &, std::vector<int> &, bool);
	void removeErrorFromBlock(const int, const int, const int, bool);
	void addErrorToBlock(const int, const int, const int, bool);

public:
	StaircaseCode();
	~StaircaseCode();

	/*
	 * function initializes staircase code
	 *
	 */
	void init(const DataManager & dm);

	/*
	 * function performs first iteration
	 * of staircase code simulation
	 *
	 * input:
	 * ng, reference to pre-set noise generator
	 *
	 */
	void firstBlocks(const NoiseGeneratorNS::NoiseGenerator &ng);

	/*
	 * function performs a subsequent iteration
	 * of staircase code simulation
	 *
	 * input:
	 * ng, reference to pre-set noise generator
	 *
	 */
	void nextBlock(const NoiseGeneratorNS::NoiseGenerator &ng);

	const bool isConverged(void) const {
		return converged;
	}

	double getBER(void) const {
		return ber;
	}

	double getBKER(void) const {
		return bker;
	}
};

} /* StaircaseCodeNS */

#endif /* INC_STAIRCASECODE_H_ */
