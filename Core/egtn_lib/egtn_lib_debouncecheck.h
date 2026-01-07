/*
 * evon_lib_debouncecheck.h
 *
 *  Created on: 2022. 5. 16.
 *      Author: EVERON
 */

#ifndef EGTN_LIB_INC_EGTN_LIB_DEBOUNCECHECK_H_
#define EGTN_LIB_INC_EGTN_LIB_DEBOUNCECHECK_H_

#include "main.h"

void EGTN_LIB_DEBOUNCECHECK_init(uint8_t* dbuf, uint16_t dbuflength);
void EGTN_LIB_DEBOUNCECHECK_push(uint8_t* dbuf, int pdata);
void EGTN_LIB_DEBOUNCECHECK_shift(uint8_t* dbuf, uint16_t dbuflength);
uint8_t EGTN_LIB_DEBOUNCECHECK_compare(uint8_t* dbuf, uint16_t dbuflength, uint8_t value);



#endif /* EGTN_LIB_INC_EGTN_LIB_DEBOUNCECHECK_H_ */
