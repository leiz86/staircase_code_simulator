/*
 * DataManager.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef INC_DATAMANAGER_H_
#define INC_DATAMANAGER_H_

#include "StaircaseCode.h"
#include "NoiseGenerator.h"

class DataManager {
	NoiseGeneratorNS::Type ngType;
//	ComponentCodeNS::ComponentCodeParams ccParams;


public:
	DataManager();
	~DataManager();

	/*
	 * function parses options and parameters string
	 *
	 * inputs:
	 * opts, NULL-terminated c-string of options and parameters
	 *
	 * return:
	 * 0, success
	 * -1, error
	 *
	 */
	int init(const char *opts);

	NoiseGeneratorNS::Type getNoiseGeneratorType(void) {
		return ngType;
	}
};

#endif /* INC_DATAMANAGER_H_ */
