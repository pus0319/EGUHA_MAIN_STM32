/*
 * egtn_mw_adc.h
 *
 *  Created on: Dec 17, 2025
 *      Author: USER
 */

#ifndef EGTN_MW_EGTN_MW_ADC_H_
#define EGTN_MW_EGTN_MW_ADC_H_

#include "main.h"
#include "adc.h"
#include "tim.h"
#include "dma.h"

#include "egtn_mw_pwm.h"
#include "egtn_mw_cp.h"

typedef enum e_adc_ch
{
	ADC_GMI,
	ADC_TEMP,
	ADC_V,
	ADC_I,
	ADC_ZCT,
	ADC_WD_L2,
	ADC_WD_L1,
	ADC_CP_CAL,
	ADC_MAX_CH
}e_ADC_CH;

#define ADC_TO_ALPHA		(0.0008057f)		// = 3.3 / 4096
#define ADC_TO_ALPHA_INT	(8057)	// = 3.3 / 4096 * 10000000

extern __IO uint16_t gADCData[ADC_MAX_CH];
extern __IO uint16_t gADCData_V_buf[AC_FREQ_HZ_100US];
extern __IO uint16_t gADCData_I_buf[AC_FREQ_HZ_100US];
extern __IO uint16_t gADCData_ZCT_buf[AC_FREQ_HZ_100US];
extern __IO uint16_t gADCData_ALL_buf_index;

void EGTN_MW_ADC_init();
uint16_t EGTN_MW_ADC_get_value(e_ADC_CH ch);

#endif /* EGTN_MW_EGTN_MW_ADC_H_ */
