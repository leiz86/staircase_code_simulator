/*
 * StaircaseSimulator.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: leizhang
 */

#include <cstdio>

#include "StaircaseSimulator.h"
#include "ParamStructures.h"

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

	return 0;

}

int StaircaseSimulator::run(int state) {
	std::vector<double> p = dm.getChannelParameters();
//	printf("p array[");	// debugging
//	for(int i = 0; i < (int)p.size(); i++) {printf("%1.4f ", p[i]);}	// debugging
//	printf("] (%lu entries)\n", p.size());	// debugging

	for(double _p : p) { runAtChannel(_p); }
	return 0;
}

/*
 * function runs simulation at given channel parameter
 *
 * outputs:
 * ber, average bit error
 * bker, average block error
 *
 */
void StaircaseSimulator::runAtChannel(double p) {
	// set noise generator
	ng.setChannelParam(p);
	printf("----- simulating at p=%02.4e -----\n", p);

	// get staircase code
	StaircaseCodeNS::StaircaseCode sc;
	sc.init(dm);

	sc.firstBlocks(ng);			// first block
	while(!sc.isConverged()) {	// next blocks
		sc.nextBlock(ng);
	}

	// set results
	dm.setResults(sc.getBER(), sc.getBKER());
	printf("ber %02.4e, bker %02.4e\n", sc.getBER(), sc.getBKER());
}

int StaircaseSimulator::report(int type) {
	const std::vector<double> &p = dm.getChannelParameters();				// channel parameters
	const std::vector<SimulationNS::Result> &results = dm.getResults();		// results

	if(type == 0) {
		printf("----- simulation results -----\n");
		printf("p \t BER \t BKER\n");
		for(int i = 0; i < (int)p.size(); i++) {
			printf ("%02.4e \t %02.4e \t %02.4e\n",
					p[i], results[i].ber, results[i].bker);
		}
		printf("----- end simulation results -----\n");
	} else if (type == 1) {
		// todo: save report to file
	}

	return 0;
}
