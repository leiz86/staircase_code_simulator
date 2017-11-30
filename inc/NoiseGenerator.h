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
	GEOM
} Type;

class NoiseGenerator {

public:
	NoiseGenerator();
	~NoiseGenerator();

	/*
	 * function initializes noise genereator
	 * of given type
	 *
	 * input:
	 * noise generator type
	 *
	 * return:
	 * 0, success
	 * -1, otherwise
	 *
	 */
	int init(Type t);
};

} /* NoiseGeneratorNS namespace */

#endif /* INC_NOISEGENERATOR_H_ */
