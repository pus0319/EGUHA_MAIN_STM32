/*
 * egtn_mw_pwm.c
 *
 *  Created on: Dec 17, 2025
 *      Author: USER
 */

#include "egtn_mw_pwm.h"

static double pwm_duty = 0.0f;
static double pwm_dutybk = 0.0f;

#if((__TEST_DMA_GPIO_STE_LED__)==1)
uint32_t ste_led_pin[2] = {(uint32_t)STE_LED1_Pin , 0x80000000};
GPIO_TypeDef* ste_led_gpio = STE_LED1_GPIO_Port;
#endif

void EGTN_MW_PWM_init()
{
	HAL_TIM_OC_Start_IT(&PWM_TIM, TIM_CHANNEL_1);
	HAL_TIM_OC_Start_IT(&PWM_TIM, TIM_CHANNEL_2);
	HAL_TIM_OC_Start_IT(&PWM_TIM, TIM_CHANNEL_4);

	HAL_TIM_PWM_Start_IT(&PWM_TIM,PWM_CH);
	HAL_Delay(50);
	EGTN_MW_PWM_set_duty(100);

#if((__TEST_DMA_GPIO_STE_LED__)==1)
	HAL_DMA_Start(&hdma_tim7_up,(uint32_t)ste_led_pin,(uint32_t)&(ste_led_gpio->BSRR),2);
	HAL_TIM_Base_Start(&htim7);
	__HAL_TIM_ENABLE_DMA(&htim7, TIM_DMA_UPDATE);
#endif


}

void EGTN_MW_PWM_set_duty(double duty)
{
	pwm_duty = duty;
}
double EGTN_MW_PWM_get_duty(double duty)
{
	return pwm_dutybk;
}

/**
  * @writer pus0319@everon.co.kr
  * @brief  Set the PWM Duty
  * @param
  * @retval
  */
uint8_t EGTN_MW_PWM_reg_duty(uint8_t persent)
{
	TIM_OC_InitTypeDef sConfigOC = {0};
	uint16_t value = 0;
	uint16_t maxvalue = 23999;
	double unitvalue = 239.99;
	//uint16_t maxvalue = 20999;
	//double unitvalue = 209.99;

	if((persent < 0) || (persent > 100))
	{
		return 0;
	}

	value = (uint16_t)(maxvalue - (uint16_t)(unitvalue * persent));


	HAL_TIM_PWM_Stop(&PWM_TIM, PWM_CH);
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = value;
    if (HAL_TIM_PWM_ConfigChannel(&PWM_TIM, &sConfigOC, PWM_CH) != HAL_OK)
    {
	    Error_Handler();
    }
    if(HAL_TIM_PWM_Start(&PWM_TIM, PWM_CH) != HAL_OK)
    {
  	    Error_Handler();
    }

    return 1;
}

uint8_t EGTN_MW_PWM_change_duty()
{
	if(pwm_duty != pwm_dutybk)
	{
		if(0 == EGTN_MW_PWM_reg_duty(pwm_duty))
		{
			EGTN_LIB_LOGGING_print_file_line("EGTN_MW_PWM_ERROR");
		}
		else
		{
			pwm_dutybk = pwm_duty;
			return EGTN_TRUE;
		}
	}

	return EGTN_FALSE;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &PWM_TIM)
	{
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
		{
			EGTN_MW_PWM_change_duty();
		}
	}
}
