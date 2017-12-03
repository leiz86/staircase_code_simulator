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
	ccParams = ComponentCodeNS::Params(15, 11, 1, 1); //(511, 484, 3, 1);	// testing only
	if(!ccParams.isValid) {
		printf("DM ERR: init: component code parameters invalid!\n");
		return -1;
	}

	// set noise generator parameters
	ngType = NoiseGeneratorNS::BERN;

	// set staircase code parameters
	scParams = StaircaseCodeNS::Params(7, 7, 8); //(255, 7, 8);	// testing only
	if(!scParams.isValid) {
		printf("DM ERR: init: staircase code parameters invalid!\n");
		return -1;
	}

	// set simulation parameters
	simParams = Params(0.5, 0.5, 0.01, 10, 100);

	return 0;
}
