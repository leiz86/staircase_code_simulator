/*
 * DataManager.h
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#ifndef INC_DATAMANAGER_H_
#define INC_DATAMANAGER_H_

#include <vector>

#include "ParamStructures.h"
#include "NoiseGenerator.h"

class DataManager {
	NoiseGeneratorNS::Type ngType = NoiseGeneratorNS::NONE;
	ComponentCodeNS::Params ccParams;
	StaircaseCodeNS::Params scParams;
	SimulationNS::Params simParams;
	std::vector<double> channelParams;
	std::vector<SimulationNS::Result> results;

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

	const SimulationNS::Params &getSimulationParams(void) const {
		return simParams;
	}

	const std::vector<double> &getChannelParameters(void) const {
		return channelParams;
	}

	void setResults(double _ber, double _bker) {
		results.push_back(SimulationNS::Result(_ber, _bker));
	}

	const std::vector<SimulationNS::Result> &getResults(void) const {
		return results;
	}
};

#endif /* INC_DATAMANAGER_H_ */
