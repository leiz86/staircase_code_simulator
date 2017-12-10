/*
 * ComponentCodeParams.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef INC_COMPONENTCODE_H_
#define INC_COMPONENTCODE_H_

#include <vector>

#include "ParamStructures.h"

namespace ComponentCodeNS {

class ComponentCode {
	Params params;

public:
	ComponentCode() {};
	~ComponentCode() {};

	void setParams(const Params &_params) {
		params = _params;
	}

	const Params &getParams(void) const {
		return params;
	}

	/**
	 * decode component code with given positions
	 * flipped
	 *
	 * @param locs locations of bit flips
	 *
	 * @param decLocs reference to vector of decoded locations
	 *
	 * @return number of bits modified by decoder, -1 if error,
	 *
	 */
	int decode(const std::vector<int> &locs, std::vector<int> &decLocs);
};

} /* ComponentCodeNS namespace */

#endif /* INC_COMPONENTCODE_H_ */
