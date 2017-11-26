/*
 * StaircaseSimulator.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#include "StaircaseSimulator.h"

StaircaseSimulator::StaircaseSimulator() {

}

StaircaseSimulator::~StaircaseSimulator() {
}

StaircaseSimulator& StaircaseSimulator::GetInstance(void) {
	static StaircaseSimulator instance;
	return instance;
}

