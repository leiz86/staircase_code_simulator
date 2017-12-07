/*
 * NoiseGenerator.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#include <cstddef>
#include <ctime>

#include "NoiseGenerator.h"

using namespace NoiseGeneratorNS;

NoiseGenerator::NoiseGenerator() :
	type(NONE), p(0.0) {
	mt = new std::mt19937(time(NULL));
}

NoiseGenerator::~NoiseGenerator() {
	if(mt != NULL) {
		delete mt;
		mt = NULL;
	}
}

int NoiseGeneratorNS::NoiseGenerator::init(Type t) {
	type = t;
	return 0;
}

void NoiseGeneratorNS::NoiseGenerator::generate(uint32_t nSamples, std::vector<uint32_t> &locs) const {
	if (nSamples == 0) {
		return;
	}

	std::bernoulli_distribution randVar(p);
	for(uint32_t i = 0; i < nSamples; i++) {
		if(randVar(*mt)) {
			locs.push_back(i);
		}
	}

//	printf("----- noise -----\n");	// debug
//	for (int i = 0; i < (int) locs.size(); i++) {
//		printf("%04u ", locs[i]);
//		if (((i + 1) % 10) == 0) {
//			printf("\n");
//		}
//	}
//	printf("\n");
//	printf("----- end noise -----\n");

}
