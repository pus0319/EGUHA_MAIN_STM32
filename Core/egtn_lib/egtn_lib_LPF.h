/*
 * egtn_lib_LPF.h
 *
 *  Created on: 2023. 11. 17.
 *      Author: MSI
 */

#ifndef EGTN_LIB_INC_EGTN_LIB_LPF_H_
#define EGTN_LIB_INC_EGTN_LIB_LPF_H_


#include "main.h"

typedef struct s_egtn_lib_lpf
{
	uint16_t timeinterval;
	uint16_t tau;
	uint32_t value_bak;
	uint32_t value;
}s_LIB_LPF;

uint8_t EGTN_LIB_LPF_init(s_LIB_LPF* p_lpf, uint16_t timeinterval, uint16_t tau);
uint32_t EGTN_LIB_LPF_calc(s_LIB_LPF* p_lpf, uint32_t input_value);

#endif /* EGTN_LIB_INC_EGTN_LIB_LPF_H_ */
