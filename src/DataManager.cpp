/*
 * DataManager.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#include <cstdio>

#include "DataManager.h"


DataManager::DataManager(){
}

DataManager::~DataManager() {
}


static std::vector<double> setChannelParameters(double m, double M, double s) {
	std::vector<double> pArray;
	double p = m;
	while (p < M + s) {	// to avoid numerical inaccuracy around M and losing M
		pArray.push_back(p);
		p += s;
	}
	return pArray;
}

int DataManager::init(const char* opts) {
	// todo: implement parsing and remove defaults

	// set component code parameters
	ccParams = ComponentCodeNS::Params(1023, 993, 3, 1);
//	ccParams = ComponentCodeNS::Params(15, 7, 2, 1);	// debugging only
	if(!ccParams.isValid) {
		printf("DM ERR: init: component code parameters invalid!\n");
		return -1;
	}

	// set noise generator parameters
	ngType = NoiseGeneratorNS::BERN;

	// set staircase code parameters
	scParams = StaircaseCodeNS::Params(511, 7, 6);
//	scParams = StaircaseCodeNS::Params(7, 3, 1); 	// debugging only
	if(!scParams.isValid) {
		printf("DM ERR: init: staircase code parameters invalid!\n");
		return -1;
	}

	// set simulation parameters
	simParams = SimulationNS::Params(0.0057, 0.0060, 5e-5, 100, 10000, 1000);
	scParams.setReportInterval(simParams.reportInterval);

	// set channel parameters
	channelParams = setChannelParameters(simParams.pMin, simParams.pMax, simParams.pStep);

	return 0;
}
