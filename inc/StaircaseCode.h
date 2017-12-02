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

	StaircaseCodeNS::Params params;
	Block *blocks = NULL;

	void initBlocks(void);

public:
	StaircaseCode();
	~StaircaseCode();

	/*
	 * function initializes staircase code
	 *
	 */
	void init(const DataManager & dm);
};

} /* StaircaseCodeNS */

#endif /* INC_STAIRCASECODE_H_ */
