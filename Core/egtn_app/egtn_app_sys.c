/*
 * egtn_app_sys.c
 *
 *  Created on: Dec 19, 2025
 *      Author: USER
 */

#include "egtn_app_sys.h"

static s_EGUHA_SYS_INFO sys_app;

static gUserDelay gDelay_sys_periodic_loop_time;

uint32_t calc_delta_t_100us(uint32_t prev, uint32_t t)
{
	if(t >= prev)
	{
		return (t - prev);
	}
	else
	{
		return (0xFFFFFFFF - prev + 1 + t);
	}
}

#if 0
uint8_t app_sys_cal_vrms_loop()
{
	uint8_t ret = 0;

	double adc_value = 0.0;
	double mcu_v = 0.0;
	double mcv_v_s_a = 0.0;
	double ac_v_inst = 0.0;
	double ac_v_inst_square = 0.0;
	static double integral_ac_v_inst_square = 0.0;
	double per_t_integral_ac_v_inst_square = 0.0;

	double ac_vrms = 0.0;

	static uint32_t delta_t_bak = 0;
	uint32_t delta_t_curr = 0;
	uint32_t delta_t_inst = 0;
	static uint32_t delta_t_total = 0;


	//1. delta t calc & check limit over with 1 step
	if(0 == delta_t_bak)// init stat.
	{
		integral_ac_v_inst_square = 0;
		delta_t_total = 0;
		delta_t_bak = EGTN_LIB_USERDLEAY_gettick();
		return 0;
	}
#if 0
	delta_t_curr = EGTN_LIB_USERDLEAY_gettick();
	delta_t_inst = calc_delta_t_100us(delta_t_bak, delta_t_curr);
	delta_t_total += delta_t_inst;
	delta_t_bak = delta_t_curr;
	//2. calc integral_ac_v_inst_square
	if(AC_ALL_CAL_DELTA_T_LIMIT > delta_t_total)
	{
		//#0 get adc_value
		adc_value = (double)gADCData[ADC_V];
		//#1 adc -> mcu_v
		mcu_v = ADC_TO_ALPHA * adc_value;
		//#2 mcu_v -> mcv_v_shift_abs(= mcv_v_s_a)
		mcv_v_s_a = fabs(mcu_v - AC_V_MCU_V_SHIFT);
		//#3 mcv_v_s_a -> AC_V
		ac_v_inst = AC_V_TO_ALPHA * mcv_v_s_a;
		//#4 AC_V -> AC_V(RMS)
		ac_v_inst_square = ac_v_inst * ac_v_inst;

		integral_ac_v_inst_square += (ac_v_inst_square * ((double)delta_t_inst));
	}
	//3. calc rms
	if(AC_ALL_CAL_DELTA_T_MAX <= delta_t_total)
	{
		per_t_integral_ac_v_inst_square = (integral_ac_v_inst_square / ((double)delta_t_total));
		ac_vrms = sqrt(per_t_integral_ac_v_inst_square);

		uint32_t ac_vrms_u32 = (uint32_t)(ac_vrms * 100);

		printf("vrms : %ld dt : %d\r\n",ac_vrms_u32,delta_t_total);

		delta_t_bak = 0;
		ret = 1;
	}
#else
	if(gADCData_ALL_buf_index >= AC_FREQ_HZ_100US)
	{
		for(int i = 0;i<AC_FREQ_HZ_100US;i++)
		{
			//#0 get adc_value
			adc_value = (double)gADCData_V_buf[i];
			//#1 adc -> mcu_v
			mcu_v = ADC_TO_ALPHA * adc_value;
			//#2 mcu_v -> mcv_v_shift_abs(= mcv_v_s_a)
			mcv_v_s_a = fabs(mcu_v - AC_V_MCU_V_SHIFT);
			//#3 mcv_v_s_a -> AC_V
			ac_v_inst = AC_V_TO_ALPHA * mcv_v_s_a;
			//#4 AC_V -> AC_V(RMS)
			ac_v_inst_square = ac_v_inst * ac_v_inst;

			integral_ac_v_inst_square += ac_v_inst_square;
		}

		per_t_integral_ac_v_inst_square = (integral_ac_v_inst_square / (AC_FREQ_HZ_100US - 1));
		ac_vrms = sqrt(per_t_integral_ac_v_inst_square);

		uint32_t ac_vrms_u32 = (uint32_t)(ac_vrms * 100);

		printf("vrms : %ld\r\n",ac_vrms_u32);

		gADCData_ALL_buf_index = 0;
		delta_t_bak = 0;
		ret = 1;
	}
#endif

	return ret;
}
uint8_t app_sys_cal_irms_loop()
{
	uint8_t ret = 0;

	double adc_value = 0.0;
	double mcu_i = 0.0;
	double mcv_i_s_a = 0.0;
	double ac_i_inst = 0.0;
	double ac_i_inst_square = 0.0;
	static double integral_ac_i_inst_square = 0.0;
	double per_t_integral_ac_i_inst_square = 0.0;

	double ac_irms = 0.0;

	static uint32_t delta_t_bak = 0;
	uint32_t delta_t_curr = 0;
	uint32_t delta_t_inst = 0;
	static uint32_t delta_t_total = 0;

	//1. delta t calc & check limit over with 1 step
	if(0 == delta_t_bak)// init stat.
	{
		integral_ac_i_inst_square = 0;
		delta_t_total = 0;
		delta_t_bak = EGTN_LIB_USERDLEAY_gettick();
		return 0;
	}
	delta_t_curr = EGTN_LIB_USERDLEAY_gettick();
	delta_t_inst = calc_delta_t_100us(delta_t_bak, delta_t_curr);
	delta_t_total += delta_t_inst;
	delta_t_bak = delta_t_curr;
	//2. calc integral_ac_i_inst_square
	if(AC_ALL_CAL_DELTA_T_LIMIT > delta_t_total)
	{
		//#0 get adc_value
		adc_value = (double)gADCData[ADC_I];
		//#1 adc -> mcu_v
		mcu_i = ADC_TO_ALPHA * adc_value;
		//#2 mcu_v -> mcv_v_shift_abs(= mcv_v_s_a)
		mcv_i_s_a = fabs(mcu_i - AC_I_MCU_V_SHIFT);
		//#3 mcv_v_s_a -> AC_V
		ac_i_inst = AC_I_TO_ALPHA * mcv_i_s_a;
		//#4 AC_V -> AC_V(RMS)
		ac_i_inst_square = ac_i_inst * ac_i_inst;

		integral_ac_i_inst_square += (ac_i_inst_square * ((double)delta_t_inst));
	}
	//3. calc rms
	if(AC_ALL_CAL_DELTA_T_MAX <= delta_t_total)
	{
		per_t_integral_ac_i_inst_square = (integral_ac_i_inst_square / ((double)delta_t_total));
		ac_irms = sqrt(per_t_integral_ac_i_inst_square);

		//ac_irms_u32 = (uint32_t)(ac_irms * 1000);

		delta_t_bak = 0;
		ret = 1;
	}

	return ret;
}
uint8_t app_sys_cal_zct_loop()
{
	//TODO : (ISR)if, over 3.28V, fast stop!
	uint8_t ret = 0;

	double adc_value = 0.0;
	double mcu_zct = 0.0;
	double mcv_zct_s_a = 0.0;
	double ac_zct_inst = 0.0;
	double ac_zct_inst_square = 0.0;
	static double integral_ac_zct_inst_square = 0.0;
	double per_t_integral_ac_zct_inst_square = 0.0;

	double ac_zct = 0.0;

	static uint32_t delta_t_bak = 0;
	uint32_t delta_t_curr = 0;
	uint32_t delta_t_inst = 0;
	static uint32_t delta_t_total = 0;

	static uint32_t fibrillating_t_total = 0;
	uint32_t fibrillating_t_inst = 0;
	double interrupt_t_max = 0;

	//1. delta t calc & check limit over with 1 step
	if(0 == delta_t_bak)// init stat.
	{
		integral_ac_zct_inst_square = 0;
		delta_t_total = 0;
		delta_t_bak = EGTN_LIB_USERDLEAY_gettick();
		return 0;
	}
	delta_t_curr = EGTN_LIB_USERDLEAY_gettick();
	delta_t_inst = calc_delta_t_100us(delta_t_bak, delta_t_curr);
	delta_t_total += delta_t_inst;
	delta_t_bak = delta_t_curr;
	//2. calc integral_ac_i_inst_square
	if(AC_ALL_CAL_DELTA_T_LIMIT > delta_t_total)
	{
		//#0 get adc_value
		adc_value = (double)gADCData[ADC_ZCT];
		//#1 adc -> mcu_v
		mcu_zct = ADC_TO_ALPHA * adc_value;
		//#2 mcu_v -> mcv_v_shift_abs(= mcv_v_s_a)
		mcv_zct_s_a = fabs(mcu_zct - ZCT_I_MCU_V_SHIFT);
		//#3 mcv_v_s_a -> ZCT_I
		ac_zct_inst = ZCT_I_TO_ALPHA * mcv_zct_s_a;
		//#4 AC_V -> AC_V(RMS)
		ac_zct_inst_square = ac_zct_inst * ac_zct_inst;

		integral_ac_zct_inst_square += (ac_zct_inst_square * ((double)delta_t_inst));
	}
	//3. calc rms
	if(AC_ALL_CAL_DELTA_T_MAX <= delta_t_total)
	{
		per_t_integral_ac_zct_inst_square = (integral_ac_zct_inst_square / ((double)delta_t_total));
		ac_zct = sqrt(per_t_integral_ac_zct_inst_square);

		if(ZCT_I_LIMIT < ac_zct) //@1 if, over 24.8mA, fast stop!
		{
			//TODO : fast stop!!
		}
		else if(ZCT_I_MIN >= ac_zct) //@2 if, under 15mA, fibrillating_t_total reset, fibrillating_t_inst = 0;
		{
			fibrillating_t_total = 0;
			fibrillating_t_inst = 0;
		}
		else //@3 calc, interrupt_t_max
		{
			fibrillating_t_inst = delta_t_total;
			fibrillating_t_total += fibrillating_t_inst;
			interrupt_t_max = ZCT_INTERRUPT_T_CALC_MS(ac_zct);

			//@4 if interrupt_t_max <= fibrillating_t_total, fast stop!
			if(interrupt_t_max <= ((double)fibrillating_t_total))
			{
				//TODO : fast stop!!
			}
		}

		delta_t_bak = 0;
		ret = 1;
	}

	return ret;
}
#endif

#if 0
uint8_t app_sys_cal_rms_loop()
{
	uint8_t ret = 0;

	double mcu_v_adc_value = 0.0;
	double mcu_i_adc_value = 0.0;
	double mcu_zct_adc_value = 0.0;

	double mcu_v = 0.0;
	double mcv_v_s_a = 0.0;
	double ac_v_inst = 0.0;
	double ac_v_inst_square = 0.0;
	static double integral_ac_v_inst_square = 0.0;
	double per_t_integral_ac_v_inst_square = 0.0;

	double mcu_i = 0.0;
	double mcv_i_s_a = 0.0;
	double ac_i_inst = 0.0;
	double ac_i_inst_square = 0.0;
	static double integral_ac_i_inst_square = 0.0;
	double per_t_integral_ac_i_inst_square = 0.0;

	double mcu_zct = 0.0;
	double mcv_zct_s_a = 0.0;
	double ac_zct_inst = 0.0;
	double ac_zct_inst_square = 0.0;
	static double integral_ac_zct_inst_square = 0.0;
	double per_t_integral_ac_zct_inst_square = 0.0;

	double ac_vrms = 0.0;
	double ac_irms = 0.0;
	double ac_zct = 0.0;

	static uint32_t fibrillating_t_total = 0;
	uint32_t fibrillating_t_inst = 0;
	double interrupt_t_max = 0;

	static uint32_t delta_t_bak = 0;
	uint32_t delta_t_curr = 0;
	uint32_t delta_t_inst = 0;
	static uint32_t delta_t_total = 17;


	//1. delta t calc & check limit over with 1 step
	if(0 == delta_t_bak)// init stat.
	{
		integral_ac_v_inst_square = 0;
		integral_ac_i_inst_square = 0;
		integral_ac_zct_inst_square = 0;
		delta_t_bak = EGTN_LIB_USERDLEAY_gettick();
		return 0;
	}

	if(gADCData_ALL_buf_index >= AC_FREQ_HZ_100US)
	{
		for(int i = 0;i<AC_FREQ_HZ_100US;i++)
		{
			//#0 get adc_value
			mcu_v_adc_value = (double)gADCData_V_buf[i];
			mcu_i_adc_value = (double)gADCData_I_buf[i];
			mcu_zct_adc_value = (double)gADCData_ZCT_buf[i];

			//CCID_ZCT_
			if(0)
			{
				// TODO : CCID20 Fast stop_adc_value is over
			}

			//#1 adc -> mcu_v
			mcu_v = ADC_TO_ALPHA * mcu_v_adc_value;
			mcu_i = ADC_TO_ALPHA * mcu_i_adc_value;
			mcu_zct = ADC_TO_ALPHA * mcu_zct_adc_value;
			//#2 mcu_v -> mcv_v_shift_abs(= mcv_v_s_a)
			mcv_v_s_a = fabs(mcu_v - AC_V_MCU_V_SHIFT);
			mcv_i_s_a = fabs(mcu_i - AC_I_MCU_V_SHIFT);
			mcv_zct_s_a = fabs(mcu_zct - ZCT_I_MCU_V_SHIFT);
			//#3 mcv_v_s_a -> AC_V
			ac_v_inst = AC_V_TO_ALPHA * mcv_v_s_a;
			ac_i_inst = AC_I_TO_ALPHA * mcv_i_s_a;
			ac_zct_inst = ZCT_I_TO_ALPHA * mcv_zct_s_a;
			//#4 AC_V -> AC_V(RMS)
			ac_v_inst_square = ac_v_inst * ac_v_inst;
			ac_i_inst_square = ac_i_inst * ac_i_inst;
			ac_zct_inst_square = ac_zct_inst * ac_zct_inst;

			integral_ac_v_inst_square += ac_v_inst_square;
			integral_ac_i_inst_square += ac_i_inst_square;
			integral_ac_zct_inst_square += ac_zct_inst_square;
		}

		per_t_integral_ac_v_inst_square = (integral_ac_v_inst_square / (AC_FREQ_HZ_100US-1));
		ac_vrms = sqrt(per_t_integral_ac_v_inst_square);
		per_t_integral_ac_i_inst_square = (integral_ac_i_inst_square / (AC_FREQ_HZ_100US));
		ac_irms = sqrt(per_t_integral_ac_i_inst_square);
		per_t_integral_ac_zct_inst_square = (integral_ac_zct_inst_square / (AC_FREQ_HZ_100US));
		ac_zct = sqrt(per_t_integral_ac_zct_inst_square);

#if 1
		uint32_t ac_vrms_u32 = (uint32_t)(ac_vrms);
		uint32_t ac_irms_u32 = (uint32_t)(ac_irms);
		uint32_t ac_zctrms_u32 = (uint32_t)(ac_zct);

		ac_vrms_u32 = 1;
		ac_irms_u32 = 1;
		ac_zctrms_u32 = 1;


		//printf("%ld %ld %ld \r\n",ac_vrms_u32,ac_irms_u32,ac_zctrms_u32);
#endif


		if(ZCT_I_LIMIT < ac_zct) //@1 if, over 24.8mA, fast stop!
		{
			//TODO : fast stop!!
		}
		else if(ZCT_I_MIN >= ac_zct) //@2 if, under 15mA, fibrillating_t_total reset, fibrillating_t_inst = 0;
		{
			fibrillating_t_total = 0;
			fibrillating_t_inst = 0;
		}
		else //@3 calc, interrupt_t_max
		{
			fibrillating_t_inst = delta_t_total;
			fibrillating_t_total += fibrillating_t_inst;
			interrupt_t_max = ZCT_INTERRUPT_T_CALC_MS(ac_zct);

			//@4 if interrupt_t_max <= fibrillating_t_total, fast stop!
			if(interrupt_t_max <= ((double)fibrillating_t_total))
			{
				//TODO : fast stop!!
			}
		}

		gADCData_ALL_buf_index = 0;
		delta_t_bak = 0;
		ret = 1;
	}

	return ret;
}
#else
uint8_t app_sys_cal_rms_loop()
{
	uint8_t ret = 0;

	int mcu_v_adc_value = 0;
	int mcu_i_adc_value = 0;
	int mcu_zct_adc_value = 0;

	int mcu_v = 0;
	int mcv_v_s_a = 0;
	int ac_v_inst = 0;
	int ac_v_inst_square = 0;
	static long long int integral_ac_v_inst_square = 0;
	double per_t_integral_ac_v_inst_square = 0;

	int mcu_i = 0;
	int mcv_i_s_a = 0;
	int ac_i_inst = 0;
	int ac_i_inst_square = 0;
	static long long int integral_ac_i_inst_square = 0;
	double per_t_integral_ac_i_inst_square = 0;

	int mcu_zct = 0;
	int mcv_zct_s_a = 0;
	int ac_zct_inst = 0;
	int ac_zct_inst_square = 0;
	static long long int integral_ac_zct_inst_square = 0;
	double per_t_integral_ac_zct_inst_square = 0;

	double ac_vrms = 0;
	double ac_irms = 0;
	double ac_zct = 0;

	uint32_t ac_vrms_u32 = 0;
	uint32_t ac_irms_u32 = 0;
	uint32_t ac_zctrms_u32 = 0;

	static uint32_t fibrillating_t_total = 0;
	uint32_t fibrillating_t_inst = 0;
	int32_t interrupt_t_max = 0;

	static uint32_t delta_t_bak = 0;
	//uint32_t delta_t_curr = 0;
	//uint32_t delta_t_inst = 0;
	static uint32_t delta_t_total = 17;


	//1. delta t calc & check limit over with 1 step
	if(0 == delta_t_bak)// init stat.
	{
		integral_ac_v_inst_square = 0;
		integral_ac_i_inst_square = 0;
		integral_ac_zct_inst_square = 0;
		delta_t_bak = EGTN_LIB_USERDLEAY_gettick();
		return 0;
	}

	if(gADCData_ALL_buf_index >= AC_FREQ_HZ_100US)
	{
		for(int i = 0;i<AC_FREQ_HZ_100US;i++)
		{
			//#0 get adc_value
			mcu_v_adc_value = gADCData_V_buf[i];
			mcu_i_adc_value = gADCData_I_buf[i];
			mcu_zct_adc_value = gADCData_ZCT_buf[i];

			//CCID_ZCT_
			if(0)
			{
				// TODO : CCID20 Fast stop_adc_value is over
			}

			//#1 adc -> mcu_v
			//mcu_v = ADC_TO_ALPHA_INT * mcu_v_adc_value;
			//mcu_i = ADC_TO_ALPHA_INT * mcu_i_adc_value;
			//mcu_zct = ADC_TO_ALPHA_INT * mcu_zct_adc_value;
			mcu_v = (int)((330 * mcu_v_adc_value) / 4096);
			mcu_i = (int)((330 * mcu_i_adc_value) / 4096);
			mcu_zct = (int)((330 * mcu_zct_adc_value) / 4096);
			//#2 mcu_v -> mcv_v_shift_abs(= mcv_v_s_a)
			mcv_v_s_a = abs(mcu_v - AC_V_MCU_V_SHIFT_INT);
			mcv_i_s_a = abs(mcu_i - AC_I_MCU_V_SHIFT_INT);
			mcv_zct_s_a = abs(mcu_zct - ZCT_I_MCU_V_SHIFT_INT);
			//#3 mcv_v_s_a -> AC_V
			ac_v_inst = AC_V_TO_ALPHA_INT * mcv_v_s_a;
			ac_i_inst = AC_I_TO_ALPHA_INT * mcv_i_s_a;
			ac_zct_inst = ZCT_I_TO_ALPHA_INT * mcv_zct_s_a;
			//#4 AC_V -> AC_V(RMS)
			ac_v_inst_square = ac_v_inst * ac_v_inst;
			ac_i_inst_square = ac_i_inst * ac_i_inst;
			ac_zct_inst_square = ac_zct_inst * ac_zct_inst;

			integral_ac_v_inst_square += ac_v_inst_square;
			integral_ac_i_inst_square += ac_i_inst_square;
			integral_ac_zct_inst_square += ac_zct_inst_square;
		}

		per_t_integral_ac_v_inst_square = ((double)integral_ac_v_inst_square / (double)(AC_FREQ_HZ_100US-1));
		ac_vrms = sqrt(per_t_integral_ac_v_inst_square);
		per_t_integral_ac_i_inst_square = ((double)integral_ac_i_inst_square / (double)(AC_FREQ_HZ_100US));
		ac_irms = sqrt(per_t_integral_ac_i_inst_square);
		per_t_integral_ac_zct_inst_square = ((double)integral_ac_zct_inst_square / (double)(AC_FREQ_HZ_100US));
		ac_zct = sqrt(per_t_integral_ac_zct_inst_square);

		ac_vrms_u32 = (uint32_t)(ac_vrms);
		ac_irms_u32 = (uint32_t)(ac_irms);
		ac_zctrms_u32 = (uint32_t)(ac_zct);

		sys_app.ac_vrms = ac_vrms_u32;
		sys_app.ac_irms = ac_irms_u32;
		sys_app.ac_zctrms = ac_zctrms_u32;

#if 0
		printf("%ld %ld %ld \r\n",ac_vrms_u32,ac_irms_u32,ac_zctrms_u32);
#endif


		// TODO : CCID20 Cut Will it run on 1ms ISR?
		if(ZCT_I_LIMIT < ac_zct) //@1 if, over 24.8mA, fast stop!
		{
			//TODO : fast stop!!
		}
		else if(ZCT_I_MIN >= ac_zct) //@2 if, under 15mA, fibrillating_t_total reset, fibrillating_t_inst = 0;
		{
			fibrillating_t_total = 0;
			fibrillating_t_inst = 0;
		}
		else //@3 calc, interrupt_t_max
		{
			fibrillating_t_inst = delta_t_total;
			fibrillating_t_total += fibrillating_t_inst;
			interrupt_t_max = ZCT_INTERRUPT_T_CALC_MS(ac_zct);

			//@4 if interrupt_t_max <= fibrillating_t_total, fast stop!
			if(interrupt_t_max <= ((double)fibrillating_t_total))
			{
				//TODO : fast stop!!
			}
		}

		gADCData_ALL_buf_index = 0;
		delta_t_bak = 0;
		ret = 1;
	}

	return ret;
}
#endif

void EGTN_APP_SYS_metering_loop()
{
#if 0
	app_sys_cal_vrms_loop();
	app_sys_cal_irms_loop();
	app_sys_cal_zct_loop();
#else
	app_sys_cal_rms_loop();
#endif
}

uint32_t EGTN_APP_SYS_get_ac_vrms()
{
	uint32_t ret = 0;

	ret = sys_app.ac_vrms;

	return ret;
}
uint32_t EGTN_APP_SYS_get_ac_irms()
{
	uint32_t ret = 0;

	ret = sys_app.ac_irms;

	return ret;
}
uint32_t EGTN_APP_SYS_get_ac_zctrms()
{
	uint32_t ret = 0;

	ret = sys_app.ac_zctrms;

	return ret;
}

uint8_t EGTN_APP_SYS_startup()
{
	uint8_t ret = 1;

	EGTN_MW_IT_init();
	EGTN_MW_UART_init();
	EGTN_MW_GPIO_init();
	EGTN_MW_INDILED_init();
	EGTN_MW_ADC_init();
	EGTN_MW_PWM_init();
	EGTN_MW_CP_init();
	EGTN_MW_RELAY_init();

	EGTN_LIB_USERDELAY_set(&gDelay_sys_periodic_loop_time,5);

	return ret;
}

uint8_t EGTN_APP_SYS_init()
{
	uint8_t ret = 1;

	return ret;
}

void EGTN_APP_SYS_main()
{

	static uint32_t test_blink = 0;
	static uint32_t gmi_toggle = 0;
	static uint32_t mc_toggle = 0;
	static uint32_t ledbar_tick = 0;
	static uint32_t ledbar_step = 0;

#if 0
	int temp_cp_h = (int)(100 * EGTN_MW_CP_get_h_final_voltage());
	int temp_cp_l = (int)(100 * EGTN_MW_CP_get_l_final_voltage());

	if(100 < test_blink)
	{
		printf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \r\n",
				gADCData[ADC_GMI],
				gADCData[ADC_TEMP],
				gADCData[ADC_V],
				gADCData[ADC_I],
				gADCData[ADC_ZCT],
				gADCData[ADC_WD_L2],
				gADCData[ADC_WD_L1],
				gADCData[ADC_CP_CAL],
				EGTN_MW_GPIO_get_gpi(I_EMG),
				temp_cp_h,
				temp_cp_l);
		HAL_GPIO_TogglePin(STE_LED1_GPIO_Port, STE_LED1_Pin);
		test_blink = 0;
	}
	else
	{
		test_blink++;
	}
#endif
#if 0
	if(800 < gmi_toggle)
	{
		HAL_GPIO_TogglePin(GMI_ENABLE_GPIO_Port, GMI_ENABLE_Pin);
		gmi_toggle = 0;
	}
	else
	{
		gmi_toggle++;
	}
#endif
#if 0
	if(1000 < mc_toggle)
	{
		if(EGTN_OFF == EGTN_MW_RELAY_get_mc_ctl())
		{
			EGTN_MW_RELAY_set_mc_ctl(EGTN_ON);
			printf("mc_on\r\n");
		}
		else if(EGTN_ON == EGTN_MW_RELAY_get_mc_ctl())
		{
			EGTN_MW_RELAY_set_mc_ctl(EGTN_OFF);
			printf("mc_off\r\n");
		}
		mc_toggle = 0;
	}
	else
	{
		mc_toggle++;
	}
#endif
#if 0
	if(200 < ledbar_tick)
	{
		switch(ledbar_step)
		{
			case 0 :
				EGTN_MW_INDILED_sled_ctl(BLACK);
				ledbar_step++;
			break;
			case 1 :
				EGTN_MW_INDILED_sled_ctl(RED);
				ledbar_step++;
			break;
			case 2 :
				EGTN_MW_INDILED_sled_ctl(GREEN);
				ledbar_step++;
			break;
			case 3 :
				EGTN_MW_INDILED_sled_ctl(BLUE);
				ledbar_step++;
			break;
			case 4 :
				EGTN_MW_INDILED_sled_ctl(YELLOW);
				ledbar_step++;
			break;
			case 5 :
				EGTN_MW_INDILED_sled_ctl(SKY);
				ledbar_step++;
			break;
			case 6 :
				EGTN_MW_INDILED_sled_ctl(PURPLE);
				ledbar_step++;
			break;
			case 7 :
				EGTN_MW_INDILED_sled_ctl(WHITE);
				ledbar_step = 0;
			break;
			default :
				ledbar_step = 0;
			break;
		}


		ledbar_tick = 0;
	}
	else
	{
		ledbar_tick++;
	}
#endif


	//printf("s:%d\r\n",EGTN_LIB_USERDLEAY_gettick());
	EGTN_MW_CP_main();
	EGTN_MW_NTC_loop();
	EGTN_MW_RELAY_main();
	EGTN_APP_SYS_metering_loop();
	//printf("e:%d\r\n",EGTN_LIB_USERDLEAY_gettick());
}

void EGTN_APP_SYS_process()
{
	EGTN_LIB_USERDELAY_start(&gDelay_sys_periodic_loop_time, DELAY_RENEW_OFF);

    if(EGTN_LIB_USERDELAY_isfired(&gDelay_sys_periodic_loop_time))
    {
    	EGTN_APP_SYS_main();

	  	EGTN_LIB_USERDELAY_start(&gDelay_sys_periodic_loop_time, DELAY_RENEW_ON);
    }
}
