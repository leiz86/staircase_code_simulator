/*
 * DataManager.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#include <cstdio>

#include "DataManager.h"


DataManager::DataManager() :
	ngType(NoiseGeneratorNS::Type::NONE){
}

DataManager::~DataManager() {
}

int DataManager::init(const char* opts) {
	// todo: implement parsing and remove defaults

	// set component code params
	ccParams = ComponentCodeNS::Params(511, 484, 3, 1);	// testing only
	if(!ccParams.isValid) {
		printf("DM ERR: init: component code parameters invalid!\n");
		return -1;
	}

	// set staircase code params
	scParams = StaircaseCodeNS::Params(255, 7, 8);	// testing only
	if(!scParams.isValid) {
		printf("DM ERR: init: staircase code parameters invalid!\n");
		return -1;
	}

	return 0;
}
