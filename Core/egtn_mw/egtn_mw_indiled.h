/*
 * evon_mw_indiled.h
 *
 *  Created on: 2022. 5. 16.
 *      Author: EVERON
 */

#ifndef EGTN_MW_INC_EGTN_MW_INDILED_H_
#define EGTN_MW_INC_EGTN_MW_INDILED_H_


#include "main.h"

typedef enum e_evon_front_indi_led_color{
	BLACK,	//LED ALL OFF
	RED,
	GREEN,
	BLUE,
	YELLOW, // RED + GREEN
	SKY,	// GREEN + BLUE
	PURPLE, // BLUE + RED
	WHITE	// RED + GREEN + BLUE
}e_EGTN_INDI_LED_COLOR;


void EGTN_MW_INDILED_init();
uint8_t EGTN_MW_INDILED_sled_ctl(e_EGTN_INDI_LED_COLOR color);



#endif /* EGTN_MW_INC_EGTN_MW_INDILED_H_ */
