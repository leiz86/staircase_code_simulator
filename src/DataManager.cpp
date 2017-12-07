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
	simParams = SimulationNS::Params(0.2, 0.2, 0.01, 10, 100);

	return 0;
}
