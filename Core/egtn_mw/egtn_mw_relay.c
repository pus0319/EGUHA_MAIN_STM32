/*
 * egtn_mw_relay.c
 *
 *  Created on: Dec 18, 2025
 *      Author: USER
 */

#include "egtn_mw_relay.h"

#define MC_PIN_BSRR_SET 	(MC1_Pin)
#define MC_PIN_BSRR_RESET 	((MC_PIN_BSRR_SET) << 16)

static uint32_t mc_pin[2] = {0,};
GPIO_TypeDef* mc_gpio = MC1_GPIO_Port;

uint8_t EGTN_MW_RELAY_set_cp_ctl(uint8_t value)
{
	uint8_t ret = 0;

	if(value == EGTN_OFF)
	{
		if(EGTN_MW_GPIO_get_gpo(CP_RY) == EGTN_ON)
		{
			if(1 == EGTN_MW_GPIO_set_gpo(CP_RY, GPIO_PIN_RESET))
			{
#if ((__RELAY_DEBUG__)==1)
				EGTN_LIB_LOGGING_printf("CP_RELAY : ON -> OFF \r\n");
#endif
				ret = 1;
			}
			else
			{
#if ((__RELAY_DEBUG__)==1)
				EGTN_LIB_LOGGING_printf("CP_RELAY : ON -> ON \r\n");
#endif
			}
		}
		else
		{
#if ((__RELAY_DEBUG__)==1)
				EGTN_LIB_LOGGING_printf("CP_RELAY : OFF -> OFF \r\n");
#endif
		}
	}
	else	//value == _ON_
	{
		if(EGTN_MW_GPIO_get_gpo(CP_RY) == EGTN_OFF)
		{
			if(1 == EGTN_MW_GPIO_set_gpo(CP_RY, GPIO_PIN_SET))
			{
#if ((__RELAY_DEBUG__)==1)
				EGTN_LIB_LOGGING_printf("CP_RELAY : OFF -> ON \r\n");
#endif
				ret = 1;
			}
			else
			{
#if ((__RELAY_DEBUG__)==1)
				EGTN_LIB_LOGGING_printf("CP_RELAY : OFF -> OFF \r\n");
#endif
			}

		}
		else
		{
#if ((__RELAY_DEBUG__)==1)
				EGTN_LIB_LOGGING_printf("CP_RELAY : ON -> ON \r\n");
#endif
		}
	}

	return ret;
}
uint8_t EGTN_MW_RELAY_get_cp_ctl()
{
	if(EGTN_MW_GPIO_get_gpo(CP_RY) == EGTN_ON)
	{
		return EGTN_ON;
	}
	else	//if(EGTN_MW_GPIO_get_gpo(CP_RY) == EGTN_OFF)
	{
		return EGTN_OFF;
	}
}

static uint8_t mc_ctl_value = 0;
static uint8_t mc_ctl_bak_value = 0;
static uint8_t mc_ctl_step = 0;

gUserDelay gDelay_mc_rated_to_holding;

#if 0
uint8_t EGTN_MW_RELAY_set_mc_ctl(uint8_t value)
{
	uint8_t ret = EGTN_CONTINUE;

	mc_ctl_value = value;

	if(mc_ctl_bak_value == mc_ctl_value)	return EGTN_FALSE;

	if(EGTN_ON == mc_ctl_value)
	{
		switch(mc_ctl_step)
		{
			case 0 :
				mc_ctl_step = 1;
				EGTN_LIB_USERDELAY_start(&gDelay_mc_rated_to_holding, DELAY_RENEW_OFF);
			break;
			case 1 :
				if(1 == EGTN_LIB_USERDELAY_isfired(&gDelay_mc_rated_to_holding))
				{
					EGTN_LIB_USERDELAY_stop(&gDelay_mc_rated_to_holding);
					mc_ctl_step = 2;
				}
			break;
			case 2 :
				ret = EGTN_TRUE;
			break;
			default :

			break;
		}
	}
	else if(EGTN_OFF == mc_ctl_value)
	{
		mc_ctl_step = 0;
		EGTN_LIB_USERDELAY_stop(&gDelay_mc_rated_to_holding);
		ret = EGTN_TRUE;
	}
	else
	{
		ret = EGTN_FALSE;
	}

	if(EGTN_TRUE == ret)
	{
		mc_ctl_bak_value = mc_ctl_value;
	}

	return ret;
}
#else
uint8_t EGTN_MW_RELAY_set_mc_ctl(uint8_t value)
{
	uint8_t ret = EGTN_TRUE;

	mc_ctl_value = value;

	return ret;
}
#endif
uint8_t EGTN_MW_RELAY_get_mc_ctl()
{
	if(mc_ctl_bak_value == EGTN_ON)
	{
		return EGTN_ON;
	}
	else
	{
		return EGTN_OFF;
	}
}

void EGTN_MW_RELAY_mc_ctl_loop()
{
	uint8_t ret = EGTN_CONTINUE;

	if(mc_ctl_bak_value == mc_ctl_value)	return;

	if(EGTN_ON == mc_ctl_value)
	{
		switch(mc_ctl_step)
		{
			case 0 :
				mc_ctl_step = 1;
				EGTN_LIB_USERDELAY_start(&gDelay_mc_rated_to_holding, DELAY_RENEW_OFF);
			break;
			case 1 :
				mc_pin[0] = (uint32_t)MC_PIN_BSRR_SET;
				mc_pin[1] = (uint32_t)MC_PIN_BSRR_SET;
				if(1 == EGTN_LIB_USERDELAY_isfired(&gDelay_mc_rated_to_holding))
				{
					EGTN_LIB_USERDELAY_stop(&gDelay_mc_rated_to_holding);
					mc_ctl_step = 2;
				}
			break;
			case 2 :
				mc_pin[0] = (uint32_t)MC_PIN_BSRR_SET;
				mc_pin[1] = (uint32_t)MC_PIN_BSRR_RESET;
				ret = EGTN_TRUE;
			break;
			default :

			break;
		}
	}
	else if(EGTN_OFF == mc_ctl_value)
	{
		mc_pin[0] = (uint32_t)MC_PIN_BSRR_RESET;
		mc_pin[1] = (uint32_t)MC_PIN_BSRR_RESET;
		mc_ctl_step = 0;
		EGTN_LIB_USERDELAY_stop(&gDelay_mc_rated_to_holding);
		ret = EGTN_TRUE;
	}
	else
	{
		ret = EGTN_FALSE;
	}



	if(EGTN_TRUE == ret)
	{
		mc_ctl_bak_value = mc_ctl_value;
	}
}

void EGTN_MW_RELAY_init()
{
	EGTN_MW_RELAY_set_cp_ctl(EGTN_OFF);
	EGTN_MW_RELAY_set_mc_ctl(EGTN_OFF);

	mc_pin[0] = (uint32_t)MC_PIN_BSRR_RESET;
	mc_pin[1] = (uint32_t)MC_PIN_BSRR_RESET;

	HAL_DMA_Start(&hdma_tim7_up,(uint32_t)mc_pin,(uint32_t)&(mc_gpio->BSRR),2);
	HAL_TIM_Base_Start(&htim7);
	__HAL_TIM_ENABLE_DMA(&htim7, TIM_DMA_UPDATE);

	EGTN_LIB_USERDELAY_set(&gDelay_mc_rated_to_holding, 1000);
}

void EGTN_MW_RELAY_main()
{
	EGTN_MW_RELAY_mc_ctl_loop();
}

