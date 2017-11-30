/*
 * StaircaseCode.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef INC_STAIRCASECODE_H_
#define INC_STAIRCASECODE_H_

#include "ComponentCode.h"
#include "DataManager.h"

namespace StaircaseCodeNS {

class StaircaseCode {
public:
	StaircaseCode();
	~StaircaseCode();

	/*
	 * function initializes staircase code
	 *
	 */
	int init(DataManager & dm);
};

} /* StaircaseCodeNS */

#endif /* INC_STAIRCASECODE_H_ */
