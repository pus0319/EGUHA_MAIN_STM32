/*
 * evon_mw_it.c
 *
 *  Created on: Sep 6, 2022
 *      Author: EVERON
 */

#include "egtn_mw_it.h"

void EGTN_MW_IT_init()
{
	HAL_TIM_Base_Start_IT(&htim6);

	EGTN_MW_UART_init();
	EGTN_MW_ADC_init();
	EGTN_MW_PWM_init();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim6)
	{
		EGTN_LIB_USERDELAY_tickcount();

#if 1
		if(gADCData_ALL_buf_index < AC_FREQ_HZ_100US)
		{	gADCData_V_buf[gADCData_ALL_buf_index] = gADCData[ADC_V];
			gADCData_I_buf[gADCData_ALL_buf_index] = gADCData[ADC_I];
			gADCData_ZCT_buf[gADCData_ALL_buf_index] = gADCData[ADC_ZCT];
			gADCData_ALL_buf_index++;
		}
#endif
	}
}
