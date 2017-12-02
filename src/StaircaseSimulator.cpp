/*
 * StaircaseSimulator.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#include <cstdio>

#include "StaircaseSimulator.h"

StaircaseSimulator::StaircaseSimulator() {

}

StaircaseSimulator::~StaircaseSimulator() {
}

StaircaseSimulator& StaircaseSimulator::GetInstance(void) {
	static StaircaseSimulator instance;
	return instance;
}

int StaircaseSimulator::init(const char *opts) {
	if(opts == NULL) {
		printf("SS ERR: init: no options string given!\n");
		return -1;
	}
	if(dm.init(opts) != 0) {
		printf("SS ERR: init: could not parse options string [%s]!\n", opts);
		return -1;
	}

	ng.init(dm.getNoiseGeneratorType());
	sc.init(dm);

	return 0;

}

int StaircaseSimulator::run(int state) {
	return 0;
}

