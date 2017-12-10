/*
 * bchdecode.h
 *
 *  Created on: Dec 4, 2017
 *      Author: leizhang
 */

#ifndef INC_BCHDECODE_H_
#define INC_BCHDECODE_H_

#include "GF1024Tables.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * decoder for (1023, 993, 7) BCH code
 *
 * @param syndrome input syndrome
 *
 * @param p1, p2, p3 pointers to be populated with flip locations
 *
 * @return number of bits flipped, -1 if error
 *
 */
int bch_decode(unsigned int syndrome,
              unsigned int *p1, unsigned int *p2, unsigned int *p3);

#ifdef __cplusplus
}
#endif

#endif /* INC_BCHDECODE_H_ */
