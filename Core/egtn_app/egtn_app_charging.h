/*
 * egtn_app_charging.h
 *
 *  Created on: Dec 19, 2025
 *      Author: USER
 */

#ifndef EGTN_APP_EGTN_APP_CHARGING_H_
#define EGTN_APP_EGTN_APP_CHARGING_H_

#include "main.h"

#include "egtn_app_sys.h"

#include "egtn_mw_cp.h"
#include "egtn_mw_gpio.h"
#include "egtn_mw_indiled.h"

#include "egtn_lib_userdelay.h"
#include "lib_statemachine/egtn_lib_StateMachine.h"

/*
 ********************** EGUHA Charging State enum*********************************
 */
typedef enum e_chrg_state
{
	ST_CHRG_IDLE,
	ST_CHRG_A1,
	ST_CHRG_A2,
	ST_CHRG_B1,
	ST_CHRG_B2,
	ST_CHRG_C1,
	ST_CHRG_C2,
	ST_CHRG_E_F,
	ST_CHRG_MAX_STATE
}e_CHRG_STATE;

/*
 *********************************************************************************
 */

typedef enum e_chrg_wake_up_seq
{
	NON,
	START_TIMEOUT,
	CP_OFF,
	PWM_DISABLE,
	FINISH,
}e_CHRG_WAKE_UP_SEQ;

typedef enum e_chrg_detection_state
{
	CHRG_DETECTION_STANDBY,
	CHRG_DETECTION_START,
	CHRG_DETECTION_STABLE,
	CHRG_DETECTION_FULL,
	CHRG_DETECTION_END
}e_CHRG_DETECTION_STATE;

typedef enum e_chrg_supply_state
{
	CHRG_SUPPLY_STANDBY,
	CHRG_SUPPLY_ACTIVE,
	CHRG_SUPPLY_INACTIVE,
	CHRG_SUPPLY_FINISHING,
	CHRG_SUPPLY_END
}e_CHRG_SUPPLY_STATE;

typedef struct
{
	e_CHRG_STATE state;
	CP_StateDef cp_state;

	e_CHRG_WAKE_UP_SEQ		wake_up_seq_step;
	uint8_t 				wake_up_seq_flag;					// 0 : wake up seq not disable  ,  1 : wake up seq enable
	uint8_t					wake_up_seq_start_flag;
	uint8_t					wake_up_seq_finish_flag;

	e_CHRG_DETECTION_STATE	detection_state;
	e_CHRG_SUPPLY_STATE supply_state;

	uint32_t instant_vrms;
	uint32_t instant_irms;
	uint32_t instant_power;
	uint16_t active_irms;

	int32_t active_energy;
	int32_t startpoint_active_energy;
	int32_t endpoint_active_energy;
	int32_t use_active_energy;

	int16_t internal_temp;
	int16_t cp_h_voltage;
	int16_t cp_l_voltage;
	uint16_t cp_pwm_duty;

	uint16_t timeout_usercheck_to_connect;

}s_EGUHA_CHRG_INFO;

void EGTN_APP_CHRG_set_active_irms(uint16_t ampe);
uint16_t EGTN_APP_CHRG_get_active_irms();
uint8_t EGTN_APP_CHRG_startup();
uint8_t EGTN_APP_CHRG_init();
void EGTN_APP_CHRG_process();

#endif /* EGTN_APP_EGTN_APP_CHARGING_H_ */
