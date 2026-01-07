/*
 * egtn_mw_adc.c
 *
 *  Created on: Dec 17, 2025
 *      Author: USER
 */

#include "egtn_mw_adc.h"

__IO uint16_t gADCData[ADC_MAX_CH] = {0,};
__IO uint16_t gADCData_V_buf[AC_FREQ_HZ_100US] = {0,};
__IO uint16_t gADCData_I_buf[AC_FREQ_HZ_100US] = {0,};
__IO uint16_t gADCData_ZCT_buf[AC_FREQ_HZ_100US] = {0,};
__IO uint16_t gADCData_ALL_buf_index = 0;

void EGTN_MW_ADC_init()
{
	HAL_ADC_Start_DMA(&hadc, (uint32_t*)gADCData, ADC_MAX_CH);
}

#if 0
uint16_t EGTN_MW_ADC_get_value(e_ADC_CH ch)
{
	return gADCData[ch];
}
#endif

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim3)
	{
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{

			EGTN_MW_CP_average_adc(CP_SECTION_L, gADCData[ADC_CP_CAL]);

		}
		else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{

			EGTN_MW_CP_average_adc(CP_SECTION_H, gADCData[ADC_CP_CAL]);

		}

		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
		{

			// TODO : CCID20 Cut Will it run on 1ms ISR? is here
		}
	}
}
