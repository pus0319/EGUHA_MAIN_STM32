/*
 * egtn_mw_ntc.h
 *
 *  Created on: 2025. 7. 31.
 *      Author: USER
 */

#ifndef EGTN_MW_EGTN_MW_NTC_H_
#define EGTN_MW_EGTN_MW_NTC_H_

#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"

#include "egtn_lib_logging.h"
#include "egtn_mw_adc.h"

#define __NTC_DEBUG__			0

#define NTC_TEMP_ADC_LENGTH		10

int EGTN_MW_NTC_cal_ntc(uint16_t i_temp);				//TSM1A103F34D1RZ
uint8_t EGTN_MW_NTC_store_value(uint16_t ADC_value);
int16_t EGTN_MW_NTC_get_temp();
uint8_t EGTN_MW_NTC_cal_temp();
uint8_t EGTN_MW_NTC_loop();

#endif /* EGTN_MW_EGTN_MW_NTC_H_ */
