/*
 * NoiseGenerator.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef INC_NOISEGENERATOR_H_
#define INC_NOISEGENERATOR_H_

namespace NoiseGeneratorNS {

typedef enum {
	NONE = 0,
	BERN,
	GEO
} Type;

class NoiseGenerator {

public:
	NoiseGenerator();
	~NoiseGenerator();
};

} /* NoiseGeneratorNS namespace */

#endif /* INC_NOISEGENERATOR_H_ */
