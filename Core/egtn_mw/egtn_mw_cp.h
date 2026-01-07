/*
 * egtn_mw_cp.h
 *
 *  Created on: 2022. 5. 16.
 *      Author: EVERON
 */

#ifndef EGTN_MW_INC_EGTN_MW_CP_H_
#define EGTN_MW_INC_EGTN_MW_CP_H_


#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"

#include <egtn_lib_debouncecheck.h>
#include <egtn_lib_logging.h>
#include <egtn_lib_userdelay.h>

#include <egtn_mw_gpio.h>
#include <egtn_mw_pwm.h>
#include <egtn_mw_relay.h>
#include <egtn_mw_adc.h>

#define __CP_DEBUG__			1

#define CP_ADC_DEBOUNCECHECKBUF_LENGTH		3
#define CP_ADC_VALUE_INDEX					((CP_ADC_DEBOUNCECHECKBUF_LENGTH)-(1))

#define ADC_CP_INDEX_		0
//#define ADC_PD_INDEX_		3
#define ADC_TEMP_INDEX_		2
#define ADC_ZCT_INDEX_		1
#define MAX_ADC_CH			3

/*
 * CP Control ADC Sampling
 *
 * See "EGUHA_CP_schematic_equation_251222" Document
 *
 */

#define CP_V_SHIFT							(1.09755f)
#define CP_V_ALPHA							(14.0904f)
#define CP_ADC_AVE_BUF_LENGTH				(8)
#define CP_ADC_AVE_BUF_LENGTH_REVERSE		(0.125F)	// (1 / _CP_ADC_AVE_BUF_LENGTH_)

#define CP_P12V_MINIMUM						(10.5F)
#define CP_P9V_MINIMUM						(7.5F)
#define CP_P6V_MINIMUM						(1.5F)//(4.5F)	//250630 PES _ EV6
#define CP_N12V_MINIMUM						(-9.5F)

#define CP_SECTION_H						0
#define CP_SECTION_L						1

#define CP_N_VOLTAGE_CHECK					1

#define MCCTL_DELAY							200

typedef enum
{
    default0 = 0,
    DC_12V,
    DC_9V,
    DC_6V,
    PWM_12V,
    PWM_9V,
    PWM_6V,
    DC_N12V,
    Err_PWMH,
    Err_PWML,
    Err_DC
} CP_StateDef;

struct sCalVolt
{
    uint16_t     val_ADC;
    uint16_t     sum_ADC;
    uint16_t     ave_ADC;
    uint16_t 	 ave_cnt;
    uint8_t 	 complete_ADC;
    double       val_Volt;
    double       sum_Volt;
    double       ave_Volt;
};

typedef struct
{
    double          	PWM_Duty;
    double          	PWM_DutyBK;

    CP_StateDef    		State;
    CP_StateDef         DebounceCheckBuf[CP_ADC_DEBOUNCECHECKBUF_LENGTH];

    struct sCalVolt      H;
    struct sCalVolt      L;
    //uint16_t 	 		 ave_cnt;

    CP_StateDef    		State_bk;

}sCP;

//extern sCP CP;

void EGTN_MW_CP_init();
uint8_t EGTN_MW_CP_set_duty(double persent);
double EGTN_MW_CP_get_pwm_duty();
double EGTN_MW_CP_get_h_final_voltage();
double EGTN_MW_CP_get_l_final_voltage();
uint8_t EGTN_MW_CP_change_duty(TIM_HandleTypeDef *htim, uint32_t cp_channel);
uint8_t EGTN_MW_CP_cp_relay_ctl(int value);
uint8_t EGTN_MW_CP_mc_relay_ctl(int value);
uint8_t EGTN_MW_CP_mc_relay_clear();
uint8_t EGTN_MW_CP_mc_relay_off_fast();
uint8_t EGTN_MW_CP_get_cp_relay_state();
uint8_t EGTN_MW_CP_get_mc_relay_state();
CP_StateDef EGTN_MW_CP_get_cp_state();
uint16_t EGTN_MW_CP_cal_ampe_to_duty(uint16_t Ampe);
uint8_t EGTN_MW_CP_print_cp_state();
uint8_t EGTN_MW_CP_average_adc(uint8_t section, uint16_t adcvalue);
uint8_t EGTN_MW_CP_calculate_adc();
uint8_t EGTN_MW_CP_calculate_state();
void EGTN_MW_CP_main();



#endif /* EGTN_MW_INC_EGTN_MW_CP_H_ */
