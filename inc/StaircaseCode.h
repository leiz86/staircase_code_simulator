/*
 * StaircaseCode.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef INC_STAIRCASECODE_H_
#define INC_STAIRCASECODE_H_

#include <cstddef>
#include <map>
#include <vector>

#include "ComponentCode.h"
#include "DataManager.h"

namespace StaircaseCodeNS {

struct Block {
	std::map<int, std::vector<int>> rowErrPos;	// row error positions
	std::map<int, std::vector<int>> colErrPos;	// column error positions


};

class StaircaseCode {
	StaircaseCodeNS::Params params;
	Block *blocks = NULL;

	double ber;
	double bker;

	bool converged = false;

	void initBlocks(void);

public:
	StaircaseCode();
	~StaircaseCode();

	/*
	 * function initializes staircase code
	 *
	 */
	void init(const DataManager & dm);

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
