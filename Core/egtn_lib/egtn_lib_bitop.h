/*
 * evon_lib_bitop.h
 *
 *  Created on: 2022. 5. 16.
 *      Author: EVERON
 */

#ifndef EGTN_LIB_INC_EGTN_LIB_BITOP_H_
#define EGTN_LIB_INC_EGTN_LIB_BITOP_H_

#include "main.h"

#define _FILED_LSB_		0
#define _FILED_MSB_		1

uint8_t EGTN_LIB_BITOP_ext_u16_to_u8one(uint16_t var, uint16_t offset);
uint16_t EGTN_LIB_BITOP_combi_u8two_to_u16(uint8_t msb, uint8_t lsb);
short EGTN_LIB_BITOP_bcd_to_short(short bcd);
unsigned int EGTN_LIB_BITOP_bcd_to_uint(unsigned int bcd);


#endif /* EGTN_LIB_INC_EGTN_LIB_BITOP_H_ */
