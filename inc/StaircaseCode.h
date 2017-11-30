/*
 * StaircaseCode.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef INC_STAIRCASECODE_H_
#define INC_STAIRCASECODE_H_

#include <cstddef>

#include "ComponentCode.h"
#include "DataManager.h"

namespace StaircaseCodeNS {

class Block {
	// todo: define contents here!!!
};

class StaircaseCode {

	Block *scBlocks = NULL;
	int nScBlocks = 0;

	int maxIters = 0;
	void createBlocks(const int, const int);

public:
	StaircaseCode();
	~StaircaseCode();

	/*
	 * function initializes staircase code
	 *
	 */
	void init(DataManager & dm);
};

} /* StaircaseCodeNS */

#endif /* INC_STAIRCASECODE_H_ */
