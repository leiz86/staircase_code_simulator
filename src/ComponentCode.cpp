/*
 * ComponentCode.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#include "ComponentCode.h"
#include "bchdecode.h"

static inline unsigned int getSyndromeFromErrorPosition(unsigned int e) {
	GFel g = EXP[e % GFq];
	return (g << (2 * GFm)) ^ (Pow3[g] << GFm) ^ (Pow5[g]);
}
static inline unsigned int getSyndrome(const std::vector<int> &locs) {
	unsigned int synd = 0;
	if(locs.size() == 0) {
		return synd;
	}
	for(int e : locs) {
		synd ^= getSyndromeFromErrorPosition(static_cast<unsigned int>(e));
	}
	return synd;
}


int ComponentCodeNS::ComponentCode::decode(const std::vector<int>& locs,
		std::vector<int>& decLocs) {

	decLocs.clear();

	unsigned int s = getSyndrome(locs);

	if(s == 0) {
		return 0;
	}

	// decode
	unsigned int p1 = 0, p2 = 0, p3 = 0;
	int ret = bch_decode(s, &p1, &p2, &p3);

	if(ret <= 0) {
		return ret;
	}

	if (p1 >= params.n || p2 >= params.n || p3 >= params.n) {
		// bit flip in shortened bits, detected mis-correction
		return -1;
	}

	if(ret >= 1) {
		decLocs.push_back(p1);
	}
	if(ret >= 2) {
		decLocs.push_back(p2);
	}
	if(ret >= 3) {
		decLocs.push_back(p3);
	}
	return ret;
}
