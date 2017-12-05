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
 * @param syndrom
 */
int bch_decode(unsigned int syndrome,
              unsigned int *p1, unsigned int *p2, unsigned int *p3);

#ifdef __cplusplus
}
#endif

#endif /* INC_BCHDECODE_H_ */
