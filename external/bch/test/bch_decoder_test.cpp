/*
 * bch_decoder_test.cpp
 *
 *  Created on: Dec 4, 2017
 *      Author: leizhang
 */

#include <cstdio>

#include "bchdecode.h"

static inline bool isErrorValid(unsigned int p, unsigned int i, unsigned int j, unsigned int k) {
	return p == i || p == j || p == k;
}
static inline unsigned int getSyndromeFromErrorPosition(unsigned int e) {
	GFel g = EXP[e % GFq];
	return (g << (2 * GFm)) ^ (Pow3[g] << GFm) ^ (Pow5[g]);
}

int main(int argc, char **argv) {
	int nPass = 0;
	int nRuns = 0;
	for (unsigned int i = 0; i < 1023; i++) {
		for (unsigned int j = i + 1; j < 1023; j++) {
			for (unsigned int k = j + 1; k < 1023; k++) {
				unsigned int synd = 0;
				synd ^= getSyndromeFromErrorPosition(i);
				synd ^= getSyndromeFromErrorPosition(j);
				synd ^= getSyndromeFromErrorPosition(k);
				unsigned int p1 = 0, p2 = 0, p3 = 0;
				int ret = bch_decode(synd, &p1, &p2, &p3);
//			printf("%u %u %u %u, (ret %d)\n", synd, p1, p2, p3, ret);
				if (ret == 3 && isErrorValid(p1, i, j, k)
						&& isErrorValid(p2, i, j, k)
						&& isErrorValid(p3, i, j, k)) {
					nPass++;
				}
				nRuns++;
			}
		}
	}

	printf("%d out of %d runs passed\n", nPass, nRuns);
	return 0;
}

