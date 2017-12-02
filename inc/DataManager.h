/*
 * DataManager.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef INC_DATAMANAGER_H_
#define INC_DATAMANAGER_H_

#include "ParamStructures.h"
#include "NoiseGenerator.h"

class DataManager {
	NoiseGeneratorNS::Type ngType = NoiseGeneratorNS::NONE;
	ComponentCodeNS::Params ccParams;
	StaircaseCodeNS::Params scParams;
	Params simParams;

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

	NoiseGeneratorNS::Type getNoiseGeneratorType(void) const {
		return ngType;
	}

	const ComponentCodeNS::Params &getComponentCodeParams(void) const {
		return ccParams;
	}

	const StaircaseCodeNS::Params &getStaircaseCodeParams(void) const {
		return scParams;
	}

	const Params &getSimulationParams(void) const {
		return simParams;
	}
};

#endif /* INC_DATAMANAGER_H_ */
