/*
 * ComponentCodeParams.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef INC_COMPONENTCODE_H_
#define INC_COMPONENTCODE_H_

#include "ParamStructures.h"

namespace ComponentCodeNS {

class ComponentCode {
	Params params;

	// todo: add decoder
public:
	ComponentCode();
	~ComponentCode();

	void setParams(const Params &_params) {
		params = _params;
	}

	const Params &getParams(void) const {
		return params;
	}
};

} /* ComponentCodeNS namespace */

#endif /* INC_COMPONENTCODE_H_ */
