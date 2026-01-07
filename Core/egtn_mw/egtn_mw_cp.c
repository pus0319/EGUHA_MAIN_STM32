/*
 * evon_mw_cp.c
 *
 *  Created on: 2022. 5. 16.
 *      Author: EVERON
 */

#include <egtn_mw_cp.h>

static sCP CP;

void EGTN_MW_CP_init()
{
	EGTN_MW_CP_set_duty(100);
	//CP.PWM_DutyBK = EGTN_MW_CP_get_pwm_duty();

	CP.State = default0;
	EGTN_LIB_DEBOUNCECHECK_init(CP.DebounceCheckBuf, CP_ADC_DEBOUNCECHECKBUF_LENGTH);

	CP.H.ave_Volt = 0;
	CP.H.sum_Volt = 0;
	CP.H.val_Volt = 0;
	CP.H.val_ADC = 0;
	CP.H.sum_ADC = 0;
	CP.H.ave_ADC = 0;
	CP.H.ave_cnt = 0;
	CP.H.complete_ADC = 0;

	CP.L.ave_Volt = 0;
	CP.L.sum_Volt = 0;
	CP.L.val_Volt = 0;
	CP.L.val_ADC = 0;
	CP.L.sum_ADC = 0;
	CP.L.ave_ADC = 0;
	CP.L.ave_cnt = 0;
	CP.L.complete_ADC = 0;

    CP.State_bk = CP.State;

}

uint8_t EGTN_MW_CP_set_duty(double persent)
{
	if((persent < 0) || (persent > 100))
	{
		return EGTN_FALSE;
	}

	CP.PWM_Duty = persent;
	EGTN_MW_PWM_set_duty(CP.PWM_Duty);

	return EGTN_TRUE;
}

double EGTN_MW_CP_get_duty()
{
	return CP.PWM_Duty;
}
double EGTN_MW_CP_get_h_final_voltage()
{
	return CP.H.ave_Volt;
}
double EGTN_MW_CP_get_l_final_voltage()
{
	return CP.L.ave_Volt;
}

CP_StateDef EGTN_MW_CP_get_cp_state()
{
	return CP.State;
}

/* KC 61851-1 Table A.5  */
uint16_t EGTN_MW_CP_cal_ampe_to_duty(uint16_t Ampe)
{
	double temp_Ampe = (double)Ampe;
	double temp_Duty = 5;

	/* 6A ~ 51A */
	if((temp_Ampe > 5) && (temp_Ampe <= 51))
	{
		temp_Duty = temp_Ampe / 0.6F;
	}
	/* 51A ~ 80A */
	else if((temp_Ampe > 51) && (temp_Ampe <= 80))
	{
		temp_Duty = ( temp_Ampe / 2.5F + 64.0F );
	}

	return (uint16_t)temp_Duty;
}


uint8_t EGTN_MW_CP_print_cp_state()
{
	if(CP.State != CP.State_bk)
	{
		switch(CP.State)
		{
			case default0 :
				printf("@@@@ CP_ADC_State : default0 @@@@ \r\n");
			break;

			case DC_12V :
				printf("@@@@ CP_ADC_State : DC_12V @@@@ \r\n");
			break;

			case DC_9V :
				printf("@@@@ CP_ADC_State : DC_9V @@@@ \r\n");
			break;

			case DC_6V :
				printf("@@@@ CP_ADC_State : DC_6V @@@@ \r\n");
			break;

			case PWM_12V :
				printf("@@@@ CP_ADC_State : PWM_12V @@@@ \r\n");
			break;

			case PWM_9V :
				printf("@@@@ CP_ADC_State : PWM_9V @@@@ \r\n");
			break;

			case PWM_6V :
				printf("@@@@ CP_ADC_State : PWM_6V @@@@ \r\n");
			break;

			case DC_N12V :
				printf("@@@@ CP_ADC_State : DC_N12V @@@@ \r\n");
			break;

			case Err_PWMH :
			case Err_DC :
				printf("@@@@ CP_ADC_State : Err_H : %d / 100 @@@@ \r\n", ((int)EGTN_MW_CP_get_h_final_voltage() * 100));
			break;

			case Err_PWML :
				printf("@@@@ CP_ADC_State : Err_L : %d / 100 @@@@ \r\n", ((int)EGTN_MW_CP_get_l_final_voltage() * 100));
			break;

		}

		CP.State_bk = CP.State;
	}

	return EGTN_TRUE;
}

uint8_t EGTN_MW_CP_average_adc(uint8_t section, uint16_t adcvalue)
{
	switch(section)
	{
		case CP_SECTION_H:
			CP.H.val_ADC = adcvalue;

			if(CP.H.complete_ADC == 0)
			{
				CP.H.sum_ADC += CP.H.val_ADC;
				CP.H.ave_cnt++;
				if(CP.H.ave_cnt >= CP_ADC_AVE_BUF_LENGTH)
				{
					CP.H.ave_ADC = CP.H.sum_ADC * CP_ADC_AVE_BUF_LENGTH_REVERSE;

					CP.H.sum_ADC = 0;
					CP.H.ave_cnt = 0;

					CP.H.complete_ADC = 1;
					return EGTN_TRUE;
				}
				else
				{
					return EGTN_CONTINUE;
				}
			}
			else
			{
				return EGTN_FALSE;
			}
		break;
		case CP_SECTION_L:
			CP.L.val_ADC = adcvalue;

			if(CP.L.complete_ADC == 0)
			{
				CP.L.sum_ADC += CP.L.val_ADC;
				CP.L.ave_cnt++;
				if(CP.L.ave_cnt >= CP_ADC_AVE_BUF_LENGTH)
				{
					CP.L.ave_ADC = CP.L.sum_ADC * CP_ADC_AVE_BUF_LENGTH_REVERSE;

					CP.L.sum_ADC = 0;
					CP.L.ave_cnt = 0;

					CP.L.complete_ADC = 1;
					return EGTN_TRUE;
				}
				else
				{
					return EGTN_CONTINUE;
				}
			}
			else
			{
				return EGTN_FALSE;
			}
		break;
		default :
			return EGTN_FALSE;
		break;
	}
}

uint8_t CP_is_complete_ADC(uint8_t section)
{
	switch(section)
	{
		case CP_SECTION_H:
			if(CP.H.complete_ADC == 1)
			{
				return EGTN_TRUE;
			}
			else
			{
				return EGTN_CONTINUE;
			}
		break;
		case CP_SECTION_L:
			if(CP.L.complete_ADC == 1)
			{
				return EGTN_TRUE;
			}
			else
			{
				return EGTN_CONTINUE;
			}
		break;
		default :
			return EGTN_FALSE;
		break;
	}
}

void CP_reset_complete_ADC(uint8_t section)
{
	switch(section)
	{
		case CP_SECTION_H:
			CP.H.complete_ADC = 0;
		break;
		case CP_SECTION_L:
			CP.L.complete_ADC = 0;
		break;
		default :

		break;
	}
}

#if 0
uint8_t EGTN_MW_CP_calculate_adc()
{
	if(EGTN_TRUE == EGTN_MW_CP_get_cp_relay_state())
	{
		CP.H.val_Volt = CP_ADC_Resolution * (CP.H.val_ADC - CP_INPUT_LEVEL_CENTER_ADC_VALUE);
		CP.L.val_Volt = CP_ADC_Resolution * (CP.L.val_ADC - CP_INPUT_LEVEL_CENTER_ADC_VALUE);

		CP.H.sum_Volt += CP.H.val_Volt;
		CP.L.sum_Volt += CP.L.val_Volt;
		CP.ave_cnt++;

		if(CP.ave_cnt >= CP_ADC_AVE_BUF_LENGTH)
		{
			CP.H.ave_Volt = CP.H.sum_Volt * CP_ADC_AVE_BUF_LENGTH_REVERSE;
			CP.L.ave_Volt = CP.L.sum_Volt * CP_ADC_AVE_BUF_LENGTH_REVERSE;

			CP.H.sum_Volt = 0;
			CP.L.sum_Volt = 0;
			CP.ave_cnt = 0;

			return EGTN_TRUE;
		}
	}
	else
	{
		EGTN_LIB_DEBOUNCECHECK_init(CP.DebounceCheckBuf, CP_ADC_DEBOUNCECHECKBUF_LENGTH);

		CP.State = default0;

		CP.H.val_Volt = 0;
		CP.L.val_Volt = 0;
		CP.H.sum_Volt = 0;
		CP.L.sum_Volt = 0;
		CP.H.ave_Volt = 0;
		CP.L.ave_Volt = 0;
		CP.ave_cnt = 0;
	}
	return EGTN_CONTINUE;
}
#else
uint8_t EGTN_MW_CP_calculate_adc()
{
	uint8_t cp_section_h_complete_adc = CP_is_complete_ADC(CP_SECTION_H);
	uint8_t cp_section_l_complete_adc = CP_is_complete_ADC(CP_SECTION_L);

	int32_t temp_CP_H_ave = 0;
	int32_t temp_CP_L_ave = 0;
	double CP_H_mcu_v = 0.0f;
	double CP_L_mcu_v = 0.0f;

	if(EGTN_TRUE == EGTN_MW_RELAY_get_cp_ctl())
	{
		if((EGTN_TRUE == cp_section_h_complete_adc) && (EGTN_TRUE == cp_section_l_complete_adc))
		{

			temp_CP_H_ave = (int32_t)CP.H.ave_ADC;
			CP_H_mcu_v = (double)ADC_TO_ALPHA * (double)temp_CP_H_ave;
			CP.H.ave_Volt = ((CP_V_SHIFT - CP_H_mcu_v) * CP_V_ALPHA);

			//EGTN_LIB_LOGGING_printf("H : %d\r\n", (uint16_t)(CP.H.ave_Volt * 100));

			temp_CP_L_ave = (int32_t)CP.L.ave_ADC;
			CP_L_mcu_v = (double)ADC_TO_ALPHA * (double)temp_CP_L_ave;
			CP.L.ave_Volt = ((CP_V_SHIFT - CP_L_mcu_v) * CP_V_ALPHA);

			//EGTN_LIB_LOGGING_printf("L : %d\r\n", (uint16_t)(CP.L.ave_Volt * 100));

			CP_reset_complete_ADC(CP_SECTION_H);
			CP_reset_complete_ADC(CP_SECTION_L);

			return EGTN_TRUE;
		}
	}
	else
	{
		EGTN_LIB_DEBOUNCECHECK_init(CP.DebounceCheckBuf, CP_ADC_DEBOUNCECHECKBUF_LENGTH);

		CP.State = default0;

		CP.H.val_Volt = 0;
		CP.L.val_Volt = 0;
		CP.H.sum_Volt = 0;
		CP.L.sum_Volt = 0;
		CP.H.ave_Volt = 0;
		CP.L.ave_Volt = 0;
	}
	return EGTN_CONTINUE;
}
#endif

uint8_t EGTN_MW_CP_calculate_state()
{
	double temp_pwm_duty = EGTN_MW_CP_get_duty();
	double temp_h_final_volt = EGTN_MW_CP_get_h_final_voltage();
#if ((CP_N_VOLTAGE_CHECK)==1)
#if 0
	double temp_l_final_volt = EGTN_MW_CP_get_l_final_voltage();
#endif
#endif

	EGTN_LIB_DEBOUNCECHECK_shift(CP.DebounceCheckBuf, CP_ADC_DEBOUNCECHECKBUF_LENGTH);

	if(temp_pwm_duty > 0)
	{
		if(temp_h_final_volt >= CP_P12V_MINIMUM)
		{
			if(temp_pwm_duty != 100)	EGTN_LIB_DEBOUNCECHECK_push(CP.DebounceCheckBuf, PWM_12V);
			else						EGTN_LIB_DEBOUNCECHECK_push(CP.DebounceCheckBuf, DC_12V);
		}
		else if(temp_h_final_volt >= CP_P9V_MINIMUM)
		{
			if(temp_pwm_duty != 100)	EGTN_LIB_DEBOUNCECHECK_push(CP.DebounceCheckBuf, PWM_9V);
			else						EGTN_LIB_DEBOUNCECHECK_push(CP.DebounceCheckBuf, DC_9V);
		}
		else if(temp_h_final_volt >= CP_P6V_MINIMUM)
		{
			if(temp_pwm_duty != 100)	EGTN_LIB_DEBOUNCECHECK_push(CP.DebounceCheckBuf, PWM_6V);
			else						EGTN_LIB_DEBOUNCECHECK_push(CP.DebounceCheckBuf, DC_6V);
		}
		else
		{
			if(temp_pwm_duty != 100)	EGTN_LIB_DEBOUNCECHECK_push(CP.DebounceCheckBuf, Err_PWMH);
			else						EGTN_LIB_DEBOUNCECHECK_push(CP.DebounceCheckBuf, Err_DC);
		}

#if ((CP_N_VOLTAGE_CHECK)==1)
#if 0
		if(temp_l_final_volt > CP_N12V_MINIMUM)
		{
			if(temp_pwm_duty != 100)	EGTN_LIB_DEBOUNCECHECK_push(CP.DebounceCheckBuf, Err_PWML);
		}
#endif
#endif

	}

	if(EGTN_TRUE == EGTN_LIB_DEBOUNCECHECK_compare(CP.DebounceCheckBuf, CP_ADC_DEBOUNCECHECKBUF_LENGTH, 0))
	{
		CP.State = CP.DebounceCheckBuf[CP_ADC_VALUE_INDEX];
#if ((__CP_DEBUG__)==1)
		EGTN_MW_CP_print_cp_state();
#endif
		return EGTN_TRUE;
	}

	return EGTN_CONTINUE;
}

void EGTN_MW_CP_main()
{
	if(EGTN_TRUE == EGTN_MW_CP_calculate_adc())
	{
		EGTN_MW_CP_calculate_state();
	}
}


