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
	ComponentCodeNS::ComponentCode cc;
	std::deque<Block> blocks;

	double ber;
	double bker;

	bool converged = false;

	void initBlocks(void);
	void decode(void);
	std::vector<int> & StaircaseCodeNS::StaircaseCode::getLeftErrorVector(int, int);
	std::vector<int> & StaircaseCodeNS::StaircaseCode::getRightErrorVector(int, int);


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
	void firstIteration(const NoiseGeneratorNS::NoiseGenerator &ng);

	/*
	 * function performs a subsequent iteration
	 * of staircase code simulation
	 *
	 * input:
	 * ng, reference to pre-set noise generator
	 *
	 */
	void nextIteration(const NoiseGeneratorNS::NoiseGenerator &ng);

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
