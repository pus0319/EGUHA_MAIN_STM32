/*
 * evon_lib_complement.h
 *
 *  Created on: 2023. 2. 13.
 *      Author: MSI
 */

#ifndef EGTN_LIB_INC_EGTN_LIB_COMPLEMENT_H_
#define EGTN_LIB_INC_EGTN_LIB_COMPLEMENT_H_

#include "main.h"

uint8_t EGTN_LIB_COMPLEMENT_TWO_STM32_32bit(int32_t input, int32_t* output);
uint8_t EGTN_LIB_BYTE_TO_HEXASCII(uint8_t input, uint8_t* output);
uint8_t EGTN_LIB_HEXASCII_TO_BYTE(char* input, uint8_t* output);


#endif /* EGTN_LIB_INC_EGTN_LIB_COMPLEMENT_H_ */
