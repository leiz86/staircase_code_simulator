/*
 * ComponentCodeParams.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef INC_COMPONENTCODE_H_
#define INC_COMPONENTCODE_H_

#include <cmath>

namespace ComponentCodeNS {

struct ComponentCodeParams {
	uint16_t n;		// length
	uint16_t k;		// dimension
	uint16_t s;		// shorten
	uint16_t nC;	// un-shortened length
	uint16_t kC; 	// un-shortened dimension

	uint16_t m;		// field extension degree

	uint16_t d;		// min distance
	uint16_t t;		// unique correction radius

	ComponentCodeParams() :
			n(0), k(0), t(0), nC(0), kC(0) {
		s = 0;
		m = 0;
		d = 0;
	}

	ComponentCodeParams::ComponentCodeParams(int _nC, int _kC, int _t, int _s =
			0) :
			ComponentCodeParams() {
		t = _t;
		s = _s;

		nC = _nC;
		kC = _kC;

		n = nC - s;
		k = kC - s;

		d = t * 2 + 1;
		m = (uint16_t) log2((double) (nC + 1));
	}

	/*
	 * validate code parameters
	 */
	bool validate(void);
};

class ComponentCode {
	// todo: populate members, need params, decoder, what else??

};

} /* ComponentCodeNS namespace */

#endif /* INC_COMPONENTCODE_H_ */
