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
	type(NONE) {
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

int NoiseGeneratorNS::NoiseGenerator::generate(double p, uint32_t nSamples, std::vector<uint32_t> &locs) {
	if (nSamples == 0 ||
		p < 0.0) {
		return -1;
	}

	std::bernoulli_distribution randVar(p);
	for(uint32_t i = 0; i < nSamples; i++) {
		if(randVar(*mt)) {
			locs.push_back(i);
		}
	}
	return 0;
}
