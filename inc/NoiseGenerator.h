/*
 * NoiseGenerator.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef INC_NOISEGENERATOR_H_
#define INC_NOISEGENERATOR_H_

#include <cstdint>
#include <vector>
#include <random>

namespace NoiseGeneratorNS {

typedef enum {
	NONE = 0,
	BERN,
	GEOM
} Type;

class NoiseGenerator {
	std::mt19937 *mt;
	Type type;

public:
	NoiseGenerator();
	~NoiseGenerator();

	/*
	 * function initializes noise generator
	 *
	 * input:
	 * t, type of generator to use
	 *
	 * return:
	 * 0, success
	 * -1, otherwise
	 *
	 */
	int init(Type t);

	/*
	 * function generates binary noise samples
	 *
	 * input:
	 * p, Bern param
	 * nSamples, number of samples of noise to generate
	 *
	 * output:
	 * locs, locations within [0, .., nSamples -1] where the noise value is 1
	 *
	 * return:
	 * 0, success
	 * -1, error
	 *
	 */
	int generate(double p, uint32_t nSamples, std::vector<uint32_t> &locs);

};

} /* NoiseGeneratorNS namespace */

#endif /* INC_NOISEGENERATOR_H_ */
