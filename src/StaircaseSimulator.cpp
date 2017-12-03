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
	sc.init(dm);

	return 0;

}

static std::vector<double> getChannelParameters(double m, double M, double s) {
	std::vector<double> pArray;
	double p = m;
	while (p < M + s) {	// to avoid numerical inaccuracy around M and losing M
		pArray.push_back(p);
		p += s;
	}
	return pArray;
}

int StaircaseSimulator::run(int state) {
	const Params &sp = dm.getSimulationParams();
	std::vector<double> p = getChannelParameters(sp.pMin, sp.pMax, sp.pStep);
//	printf("p array[");	// debugging
//	for(int i = 0; i < (int)p.size(); i++) {printf("%1.4f ", p[i]);}	// debugging
//	printf("] (%lu entries)\n", p.size());	// debugging

	std::vector<double> ber;
	std::vector<double> bker;
	for(double _p : p) {
		double _ber, _bker;
		runAtChannel(_p, _ber, _bker);
		ber.push_back(_ber);
		bker.push_back(_bker);
	}

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
void StaircaseSimulator::runAtChannel(double p, double &ber, double &bker) {
	// set noise generator
	ng.setChannelParam(p);

	// first generation
	sc.firstIteration(ng);

	// next iterations
	while(!sc.isConverged()) {
		sc.nextIteration(ng);
	}

	// set results
	dm.setResults(sc.getBER(), sc.getBKER());
}

int StaircaseSimulator::report(int type) {
	const Results &r = dm.getResults();
	if(type == 0) {
		printf("----- simulation results -----\n");
		printf("BER:\t %02.4e\n", r.ber);
		printf("BKER:\t %02.4e\n", r.bker);
		printf("----- end simulation results -----\n");
	} else if (type == 1) {
		// todo: save report to file
	}

	return 0;
}
