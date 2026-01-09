/*
 * egtn_app_charging.c
 *
 *  Created on: Dec 19, 2025
 *      Author: USER
 */

#include "egtn_app_charging.h"

static s_EGUHA_CHRG_INFO chrg_app;

static gUserDelay gDelay_chrg_periodic_loop_time;
static gUserDelay gDelay_chrg_evse_finish;

static SM_DEFINE(EGUHA_CHRG_SM, &chrg_app);
static EVENT_DECLARE(EGTN_APP_CHRG_handling,NoEventData);
static EVENT_DECLARE(EGTN_APP_CHRG_start,NoEventData);
static EVENT_DECLARE(EGTN_APP_CHRG_stop,NoEventData);
static EVENT_DECLARE(EGTN_APP_CHRG_fault,NoEventData);

static GET_DECLARE(EGTN_APP_CHRG_get_chrg_state, e_CHRG_STATE);

ENTRY_DECLARE(chrg_idle,NoEventData);
STATE_DECLARE(chrg_idle,NoEventData);
ENTRY_DECLARE(chrg_A1,NoEventData);
STATE_DECLARE(chrg_A1,NoEventData);
ENTRY_DECLARE(chrg_A2,NoEventData);
STATE_DECLARE(chrg_A2,NoEventData);
ENTRY_DECLARE(chrg_B1,NoEventData);
STATE_DECLARE(chrg_B1,NoEventData);
ENTRY_DECLARE(chrg_B2,NoEventData);
STATE_DECLARE(chrg_B2,NoEventData);
ENTRY_DECLARE(chrg_C1,NoEventData);
STATE_DECLARE(chrg_C1,NoEventData);
ENTRY_DECLARE(chrg_C2,NoEventData);
STATE_DECLARE(chrg_C2,NoEventData);
ENTRY_DECLARE(chrg_E_F,NoEventData);
STATE_DECLARE(chrg_E_F,NoEventData);

BEGIN_STATE_MAP_EX(s_EGUHA_CHRG_INFO)
	STATE_MAP_ENTRY_ALL_EX(ST_chrg_idle, 0, EN_chrg_idle, 0)	//ST_CHRG_IDLE,
	STATE_MAP_ENTRY_ALL_EX(ST_chrg_A1, 0, EN_chrg_A1, 0)		//ST_CHRG_A1,
	STATE_MAP_ENTRY_ALL_EX(ST_chrg_A2, 0, EN_chrg_A2, 0)		//ST_CHRG_A2,
	STATE_MAP_ENTRY_ALL_EX(ST_chrg_B1, 0, EN_chrg_B1, 0)		//ST_CHRG_B1,
	STATE_MAP_ENTRY_ALL_EX(ST_chrg_B2, 0, EN_chrg_B2, 0)		//ST_CHRG_B2,
	STATE_MAP_ENTRY_ALL_EX(ST_chrg_C1, 0, EN_chrg_C1, 0)		//ST_CHRG_C1,
	STATE_MAP_ENTRY_ALL_EX(ST_chrg_C2, 0, EN_chrg_C2, 0)		//ST_CHRG_C2,
	STATE_MAP_ENTRY_ALL_EX(ST_chrg_E_F, 0, EN_chrg_E_F, 0)		//ST_CHRG_E_F,
END_STATE_MAP_EX(s_EGUHA_CHRG_INFO)

void chrg_indiled_display()
{
	e_CHRG_STATE state = chrg_app.state;

	//TODO : change checklist(specLED) event doing logic
	switch(state)
	{
		case ST_CHRG_IDLE :
			EGTN_MW_INDILED_sled_ctl(PURPLE);
		break;
		case ST_CHRG_A1 :
		case ST_CHRG_A2 :
			EGTN_MW_INDILED_sled_ctl(WHITE);
		break;
		case ST_CHRG_B1 :
		case ST_CHRG_B2 :
			if(0)//TODO : A1(A2)->B1(B2) Edge detect
			{
				EGTN_MW_INDILED_sled_ctl(YELLOW);
			}
			else
			{
				EGTN_MW_INDILED_sled_ctl(BLUE);
			}
		break;
		case ST_CHRG_C1 :
		case ST_CHRG_C2 :
			if(0)//TODO : detection state is finish
			{
				EGTN_MW_INDILED_sled_ctl(SKY);
			}
			else
			{
				if(CHRG_SUPPLY_ACTIVE == chrg_app.supply_state)
				{
					EGTN_MW_INDILED_sled_ctl(GREEN);
				}
			}
		break;
		case ST_CHRG_E_F :
			EGTN_MW_INDILED_sled_ctl(RED);
		break;
		default :

		break;
	}

	if(CHRG_SUPPLY_FINISHING == chrg_app.supply_state)
	{
		EGTN_MW_INDILED_sled_ctl(SKY);
	}
}

void chrg_set_relay_cp(uint8_t ctl)
{
	EGTN_MW_RELAY_set_cp_ctl(ctl);
}
uint8_t chrg_get_relay_cp()
{
	uint8_t ret = 0;

	ret = EGTN_MW_RELAY_get_cp_ctl();

	return ret;
}

void chrg_set_relay_mc(uint8_t ctl)
{
	EGTN_MW_RELAY_set_mc_ctl(ctl);
}
uint8_t chrg_get_relay_mc()
{
	uint8_t ret = 0;

	ret = EGTN_MW_RELAY_get_mc_ctl();

	return ret;
}

void chrg_set_wake_up_seq(uint8_t mode)
{

}
void chrg_wake_up_seq_loop()
{

}
uint8_t chrg_get_user_button()
{
	uint8_t ret = 0;

	if(1 == EGTN_MW_GPIO_get_gpi(I_EMG))	// button unpressed
	{
		ret = 0;
	}
	else if(0 == EGTN_MW_GPIO_get_gpi(I_EMG)) // button pressed
	{
		ret = 1;
	}

	return ret;
}


void chrg_usercheck_mobile_loop()
{
	switch(chrg_app.usercheck_info.step[CHRG_USERCHECK_MOBILE])
	{
		case CHRG_USERCHECK_SEQ_NON :
			// TODO : BLE --> CHRG start certi
			if(0)
			{
				chrg_app.usercheck_info.step[CHRG_USERCHECK_MOBILE] = CHRG_USERCHECK_SEQ_CERTI;
			}
		break;
		case CHRG_USERCHECK_SEQ_CERTI :
			// TODO : BLE --> CHRG certi is success
			if(0)
			{
				chrg_app.usercheck_info.step[CHRG_USERCHECK_MOBILE] = CHRG_USERCHECK_SEQ_AUTH;
			}
			// TODO : BLE --> CHRG certi is fail
			if(0)
			{
				chrg_app.usercheck_info.step[CHRG_USERCHECK_MOBILE] = CHRG_USERCHECK_SEQ_NON;
			}
		break;
		case CHRG_USERCHECK_SEQ_AUTH :
			// TODO : BLE --> CHRG auth is exit
			if(0)
			{
				chrg_app.usercheck_info.step[CHRG_USERCHECK_MOBILE] = CHRG_USERCHECK_SEQ_DEAUTH;
			}
		break;
		case CHRG_USERCHECK_SEQ_DEAUTH :
			// TODO : BLE --> CHRG deauth is complete
			if(0)
			{
				chrg_app.usercheck_info.step[CHRG_USERCHECK_MOBILE] = CHRG_USERCHECK_SEQ_NON;
			}
		break;
		default :

		break;
	}
}

void chrg_usercheck_rfid_loop()
{

}

void chrg_usercheck_loop()
{
	if(1 == chrg_app.usercheck_info.mask[CHRG_USERCHECK_MOBILE])
	{
		chrg_usercheck_mobile_loop();
	}
	else
	{

	}

	if(1 == chrg_app.usercheck_info.mask[CHRG_USERCHECK_RFID])
	{
		chrg_usercheck_rfid_loop();
	}
	else
	{

	}
}

void chrg_set_active_ampe_to_pwm_duty(uint16_t ampe)
{
	chrg_app.cp_pwm_duty = EGTN_MW_CP_cal_ampe_to_duty(ampe);
}
void chrg_off_cp_pwm_duty()
{
	chrg_app.cp_pwm_duty = 100;
}

void chrg_set_cp_pwm_duty(int16_t duty)
{
	EGTN_MW_CP_set_duty(duty);
}

ENTRY_DEFINE(chrg_idle,NoEventData)
{
	SM_PRINTF("%s EN_CHRG_idle\r\n",self->name);

	chrg_set_relay_cp(EGTN_OFF);
	chrg_set_relay_mc(EGTN_OFF);
}
STATE_DEFINE(chrg_idle,NoEventData)
{
	//SM_PRINTF("%s ST_CHRG_idle\r\n",self->name);


}

ENTRY_DEFINE(chrg_A1,NoEventData)
{
	SM_PRINTF("%s EN_CHRG_A1\r\n",self->name);

	chrg_set_relay_cp(EGTN_ON);
	chrg_set_relay_mc(EGTN_OFF);

	EGTN_APP_CHRG_set_standby_charging();
}
STATE_DEFINE(chrg_A1,NoEventData)
{
	//SM_PRINTF("%s ST_CHRG_A1\r\n",self->name);

	//61851-1_seq1.1 --> B1
	if(DC_9V == chrg_app.cp_state)
	{
		SM_PRINTF("%s ST_CHRG_A1 --> B1\r\n",self->name);
		SM_InternalEvent(ST_CHRG_B1,NULL);
	}
	//61851-1_seq1.2 --> C1
	if(DC_6V == chrg_app.cp_state)
	{
		SM_PRINTF("%s ST_CHRG_A1 --> C1\r\n",self->name);
		SM_InternalEvent(ST_CHRG_C1,NULL);
	}
}

ENTRY_DEFINE(chrg_A2,NoEventData)
{
	SM_PRINTF("%s EN_CHRG_A2\r\n",self->name);

	chrg_set_relay_cp(EGTN_ON);
	chrg_set_relay_mc(EGTN_OFF);

	EGTN_APP_CHRG_set_finish_charging();
}
STATE_DEFINE(chrg_A2,NoEventData)
{
	//SM_PRINTF("%s CHRG_A2\r\n",self->name);

	//61851-1_seq1.1 --> B2
	if(PWM_9V == chrg_app.cp_state)
	{
		SM_PRINTF("%s ST_CHRG_A2 --> B2\r\n",self->name);
		SM_InternalEvent(ST_CHRG_B2,NULL);
	}
	//61851-1_seq1.2 --> C2
	if(PWM_6V == chrg_app.cp_state)
	{
		SM_PRINTF("%s ST_CHRG_A2 --> C2\r\n",self->name);
		SM_InternalEvent(ST_CHRG_C2,NULL);
	}
	//61851-1_seq9.3 --> A1
	if(DC_12V == chrg_app.cp_state)
	{
		SM_PRINTF("%s ST_CHRG_A2 --> A1\r\n",self->name);
		SM_InternalEvent(ST_CHRG_A1,NULL);
	}
}

ENTRY_DEFINE(chrg_B1,NoEventData)
{
	SM_PRINTF("%s EN_CHRG_B1\r\n",self->name);

	chrg_set_relay_cp(EGTN_ON);
	chrg_set_relay_mc(EGTN_OFF);
}
STATE_DEFINE(chrg_B1,NoEventData)
{
	//SM_PRINTF("%s ST_CHRG_B1\r\n",self->name);

	//61851-1_seq2.1 --> A1
	if(DC_12V == chrg_app.cp_state)
	{
		SM_PRINTF("%s ST_CHRG_B1 --> A1\r\n",self->name);
		SM_InternalEvent(ST_CHRG_A1,NULL);
	}
	//61851-1_seq3.1 --> B2
	//if(((PWM_9V == chrg_app.cp_state) || (PWM_6V == chrg_app.cp_state)) && (CHRG_SUPPLY_ACTIVE == chrg_app.supply_state))
	if(((PWM_9V == chrg_app.cp_state) || (PWM_6V == chrg_app.cp_state)))
	{
		SM_PRINTF("%s ST_CHRG_B1 --> B2\r\n",self->name);
		SM_InternalEvent(ST_CHRG_B2,NULL);
	}
}

ENTRY_DEFINE(chrg_B2,NoEventData)
{
	SM_PRINTF("%s EN_CHRG_B2\r\n",self->name);

	chrg_set_relay_cp(EGTN_ON);
	chrg_set_relay_mc(EGTN_OFF);
}
STATE_DEFINE(chrg_B2,NoEventData)
{
	//SM_PRINTF("%s ST_CHRG_B2\r\n",self->name);

	//61851-1_seq2.1 --> A2
	if(PWM_12V == chrg_app.cp_state)
	{
		SM_PRINTF("%s ST_CHRG_B2 --> A2\r\n",self->name);
		SM_InternalEvent(ST_CHRG_A2,NULL);
	}
	//61851-1_seq4 --> C2
	//if((PWM_6V == chrg_app.cp_state) && (CHRG_SUPPLY_ACTIVE == chrg_app.supply_state) && (5 < chrg_app.cp_pwm_duty))
	if((PWM_6V == chrg_app.cp_state) && (5 < chrg_app.cp_pwm_duty))
	{
		SM_PRINTF("%s ST_CHRG_B2 --> C2\r\n",self->name);
		SM_InternalEvent(ST_CHRG_C2,NULL);
	}
	//61851-1_seq9.2 --> B1
	//if((DC_9V == chrg_app.cp_state) && (CHRG_SUPPLY_ACTIVE != chrg_app.supply_state))
	if(DC_9V == chrg_app.cp_state)
	{
		SM_PRINTF("%s ST_CHRG_B2 --> B1\r\n",self->name);
		SM_InternalEvent(ST_CHRG_B1,NULL);
	}
}

ENTRY_DEFINE(chrg_C1,NoEventData)
{
	SM_PRINTF("%s EN_CHRG_C1\r\n",self->name);

	chrg_set_relay_cp(EGTN_ON);
	chrg_set_relay_mc(EGTN_OFF);
}
STATE_DEFINE(chrg_C1,NoEventData)
{
	//SM_PRINTF("%s ST_CHRG_C1\r\n",self->name);

	//61851-1_seq3.2 --> C2 : Available
	//if((PWM_6V == chrg_app.cp_state) && (CHRG_SUPPLY_ACTIVE == chrg_app.supply_state) && (5 < chrg_app.cp_pwm_duty))
	if((PWM_6V == chrg_app.cp_state) && (5 < chrg_app.cp_pwm_duty))
	{
		SM_PRINTF("%s ST_CHRG_C1 --> C2\r\n",self->name);
		SM_InternalEvent(ST_CHRG_C2,NULL);
	}
	//61851-1_seq10.1 --> B1
	//61851-1_seq8.2 --> B1
	if(DC_9V == chrg_app.cp_state)
	{
		SM_PRINTF("%s ST_CHRG_C1 --> B1\r\n",self->name);
		SM_InternalEvent(ST_CHRG_B1,NULL);
	}
	//61851-1_seq2.2 --> A1
	if(DC_12V == chrg_app.cp_state)
	{
		SM_PRINTF("%s ST_CHRG_C1 --> A1\r\n",self->name);
		SM_InternalEvent(ST_CHRG_A1,NULL);
	}
}

ENTRY_DEFINE(chrg_C2,NoEventData)
{
	SM_PRINTF("%s EN_CHRG_C2\r\n",self->name);

	chrg_set_relay_cp(EGTN_ON);
	chrg_set_relay_mc(EGTN_ON);
}
STATE_DEFINE(chrg_C2,NoEventData)
{
	static uint8_t is_diode_fail = 0;

	//SM_PRINTF("%s ST_CHRG_C2\r\n",self->name);

	//61851-1_seq5
	//61851-1_seq6
	//if(PWM_6V == chrg_app.cp_state)
	if(CHRG_SUPPLY_ACTIVE == chrg_app.supply_state)
	{
		//ZE-READY R9. Diode presence
		if((0 == is_diode_fail) && (CHRG_CP_L_V_LIMIT_UNDER <= chrg_app.cp_l_voltage))
		{
			is_diode_fail = 1;
		}
		else if((1 == is_diode_fail) && (CHRG_CP_L_V_LIMIT_UPPER >= chrg_app.cp_l_voltage))
		{
			is_diode_fail = 0;
		}
		if(1 == is_diode_fail)
		{
			if(EGTN_ON == chrg_get_relay_mc())
			{
				SM_PRINTF("%s ST_CHRG_C2 : ZE-READY R9. Diode is fail. mc off\r\n",self->name);
				chrg_set_relay_mc(EGTN_OFF);
			}
		}
		else
		{
			if(EGTN_OFF == chrg_get_relay_mc())
			{
				SM_PRINTF("%s ST_CHRG_C2 : ZE-READY R9. Diode is ok. mc on\r\n",self->name);
				chrg_set_relay_mc(EGTN_ON);
			}
		}
	}

	//61851-1_seq2.2 --> A2
	if(PWM_12V == chrg_app.cp_state)
	{
		SM_PRINTF("%s ST_CHRG_C2 --> A2\r\n",self->name);
		SM_InternalEvent(ST_CHRG_A2,NULL);
	}

	//61851-1_seq7 --> B2
	//61851-1_seq8.1 --> B2
	if(PWM_9V == chrg_app.cp_state)
	{
		SM_PRINTF("%s ST_CHRG_C2 --> B2\r\n",self->name);
		SM_InternalEvent(ST_CHRG_B2,NULL);
	}

	//61851-1_seq9.1 --> C1
	//61851-1_seq10.2 --> C1
	if(DC_6V == chrg_app.cp_state)
	{
		if(CHRG_SUPPLY_INACTIVE == chrg_app.supply_state)
		{
			EGTN_LIB_USERDELAY_stop(&gDelay_chrg_evse_finish);
			SM_PRINTF("%s ST_CHRG_C2 --> C1(charging pause by EVSE)\r\n",self->name);
			SM_InternalEvent(ST_CHRG_C1,NULL);
		}
		else if(CHRG_SUPPLY_FINISHING == chrg_app.supply_state)
		{
			//TODO : delay change ampe(max 3sec)
			EGTN_LIB_USERDELAY_start(&gDelay_chrg_evse_finish, DELAY_RENEW_OFF);
			if(EGTN_LIB_USERDELAY_isfired(&gDelay_chrg_evse_finish))
			{
				EGTN_LIB_USERDELAY_stop(&gDelay_chrg_evse_finish);
				SM_PRINTF("%s ST_CHRG_C2 --> C1(charging finish by EVSE)\r\n",self->name);
				SM_InternalEvent(ST_CHRG_C1,NULL);
			}
		}
		else
		{
			EGTN_LIB_USERDELAY_stop(&gDelay_chrg_evse_finish);
		}
	}
	if(DC_9V == chrg_app.cp_state)
	{
		EGTN_LIB_USERDELAY_stop(&gDelay_chrg_evse_finish);
		SM_PRINTF("%s ST_CHRG_C2 --> C1(charging finish by EV)\r\n",self->name);
		SM_InternalEvent(ST_CHRG_C1,NULL);
	}
	if(DC_12V == chrg_app.cp_state)
	{
		EGTN_LIB_USERDELAY_stop(&gDelay_chrg_evse_finish);
		SM_PRINTF("%s ST_CHRG_C2 --> C1(charging force finish by USER)\r\n",self->name);
		SM_InternalEvent(ST_CHRG_C1,NULL);
	}
}

ENTRY_DEFINE(chrg_E_F,NoEventData)
{
	SM_PRINTF("%s EN_CHRG_E_F\r\n",self->name);

	chrg_set_relay_cp(EGTN_ON);
	chrg_set_relay_mc(EGTN_OFF);

	EGTN_APP_CHRG_set_pause_charging();
}
STATE_DEFINE(chrg_E_F,NoEventData)
{
	//SM_PRINTF("%s ST_CHRG_E_F\r\n",self->name);

	//61851-1_seq12
	if(DC_12V == chrg_app.cp_state)
	{
		SM_PRINTF("%s ST_CHRG_E_F --> A1\r\n",self->name);
		SM_InternalEvent(ST_CHRG_A1,NULL);
	}
}

EVENT_DEFINE(EGTN_APP_CHRG_handling,NoEventData)
{
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY(ST_CHRG_IDLE)//<--ST_CHRG_IDLE,
		TRANSITION_MAP_ENTRY(ST_CHRG_A1)//<--ST_CHRG_A1,
		TRANSITION_MAP_ENTRY(ST_CHRG_A2)//<--ST_CHRG_A2,
		TRANSITION_MAP_ENTRY(ST_CHRG_B1)//<--ST_CHRG_B1,
		TRANSITION_MAP_ENTRY(ST_CHRG_B2)//<--ST_CHRG_B2,
		TRANSITION_MAP_ENTRY(ST_CHRG_C1)//<--ST_CHRG_C1,
		TRANSITION_MAP_ENTRY(ST_CHRG_C2)//<--ST_CHRG_C2,
		TRANSITION_MAP_ENTRY(ST_CHRG_E_F)//<--ST_CHRG_E_F,
	END_TRANSITION_MAP(s_EGUHA_CHRG_INFO,pEventData)
}
EVENT_DEFINE(EGTN_APP_CHRG_start,NoEventData)
{
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY(ST_CHRG_A1)//<--ST_CHRG_IDLE,
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)//<--ST_CHRG_A1,
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)//<--ST_CHRG_A2,
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)//<--ST_CHRG_B1,
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)//<--ST_CHRG_B2,
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)//<--ST_CHRG_C1,
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)//<--ST_CHRG_C2,
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)//<--ST_CHRG_E_F,
	END_TRANSITION_MAP(s_EGUHA_CHRG_INFO,pEventData)
}
EVENT_DEFINE(EGTN_APP_CHRG_stop,NoEventData)
{
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY(ST_CHRG_IDLE)//<--ST_CHRG_IDLE,
		TRANSITION_MAP_ENTRY(ST_CHRG_IDLE)//<--ST_CHRG_A1,
		TRANSITION_MAP_ENTRY(ST_CHRG_IDLE)//<--ST_CHRG_A2,
		TRANSITION_MAP_ENTRY(ST_CHRG_IDLE)//<--ST_CHRG_B1,
		TRANSITION_MAP_ENTRY(ST_CHRG_IDLE)//<--ST_CHRG_B2,
		TRANSITION_MAP_ENTRY(ST_CHRG_IDLE)//<--ST_CHRG_C1,
		TRANSITION_MAP_ENTRY(ST_CHRG_IDLE)//<--ST_CHRG_C2,
		TRANSITION_MAP_ENTRY(ST_CHRG_IDLE)//<--ST_CHRG_E_F,
	END_TRANSITION_MAP(s_EGUHA_CHRG_INFO,pEventData)
}
EVENT_DEFINE(EGTN_APP_CHRG_fault,NoEventData)
{
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY(ST_CHRG_E_F)//<--ST_CHRG_IDLE,
		TRANSITION_MAP_ENTRY(ST_CHRG_E_F)//<--ST_CHRG_A1,
		TRANSITION_MAP_ENTRY(ST_CHRG_E_F)//<--ST_CHRG_A2,
		TRANSITION_MAP_ENTRY(ST_CHRG_E_F)//<--ST_CHRG_B1,
		TRANSITION_MAP_ENTRY(ST_CHRG_E_F)//<--ST_CHRG_B2,
		TRANSITION_MAP_ENTRY(ST_CHRG_E_F)//<--ST_CHRG_C1,
		TRANSITION_MAP_ENTRY(ST_CHRG_E_F)//<--ST_CHRG_C2,
		TRANSITION_MAP_ENTRY(ST_CHRG_E_F)//<--ST_CHRG_E_F,
	END_TRANSITION_MAP(s_EGUHA_CHRG_INFO,pEventData)
}

GET_DEFINE(EGTN_APP_CHRG_get_chrg_state, e_CHRG_STATE)
{
	return self->currentState;
}

void chrg_update_pwm_loop()
{
	e_CHRG_STATE state = chrg_app.state;

	if(CHRG_SUPPLY_ACTIVE == chrg_app.supply_state)
	{
		if((ST_CHRG_A2 <= state) && (ST_CHRG_C2 >= state))
		{
			chrg_set_active_ampe_to_pwm_duty(chrg_app.active_irms);
		}
	}
	else
	{
		chrg_off_cp_pwm_duty();
	}

	chrg_set_cp_pwm_duty(chrg_app.cp_pwm_duty);
}

void EGTN_APP_CHRG_update_parameter_loop()
{
	int temp_cp_h = (int)(100 * EGTN_MW_CP_get_h_final_voltage());
	int temp_cp_l = (int)(100 * EGTN_MW_CP_get_l_final_voltage());

	chrg_app.state = SM_Get(EGUHA_CHRG_SM,EGTN_APP_CHRG_get_chrg_state);

	chrg_app.instant_vrms = EGTN_APP_SYS_get_ac_vrms();
	chrg_app.instant_irms = EGTN_APP_SYS_get_ac_irms();
	//chrg_app.instant_power;

	//chrg_app.active_energy;
	//chrg_app.startpoint_active_energy;
	//chrg_app.endpoint_active_energy;
	//chrg_app.use_active_energy;

	chrg_app.internal_temp = EGTN_MW_NTC_get_temp();
	chrg_app.cp_h_voltage = temp_cp_h;
	chrg_app.cp_l_voltage = temp_cp_l;
	chrg_app.cp_state = EGTN_MW_CP_get_cp_state();

	chrg_update_pwm_loop();
}
void EGTN_APP_CHRG_display_loop()
{
	chrg_indiled_display();
}

void EGTN_APP_CHRG_set_active_irms(uint16_t ampe)
{
	chrg_app.active_irms = ampe;
}
uint16_t EGTN_APP_CHRG_get_active_irms()
{
	return chrg_app.active_irms;
}
void EGTN_APP_CHRG_set_start_charging()
{
	printf("CHRG_APP : ######## start charging ######## \r\n");

	chrg_app.supply_state = CHRG_SUPPLY_ACTIVE;
}
void EGTN_APP_CHRG_set_pause_charging()
{
	printf("CHRG_APP : ######## pause charging ######## \r\n");

	chrg_app.supply_state = CHRG_SUPPLY_INACTIVE;
}
void EGTN_APP_CHRG_set_finish_charging()
{
	printf("CHRG_APP : ######## finish charging ######## \r\n");

	chrg_app.supply_state = CHRG_SUPPLY_FINISHING;
}
void EGTN_APP_CHRG_set_standby_charging()
{
	printf("CHRG_APP : ######## standby charging ######## \r\n");

	chrg_app.supply_state = CHRG_SUPPLY_STANDBY;
}
uint8_t EGTN_APP_CHRG_startup()
{
	uint8_t ret = 1;

	EGTN_LIB_USERDELAY_set(&gDelay_chrg_periodic_loop_time,5);
	EGTN_LIB_USERDELAY_set(&gDelay_chrg_evse_finish,2500);

	return ret;
}

uint8_t EGTN_APP_CHRG_init()
{
	uint8_t ret = 1;
	int i = 0;

	chrg_set_relay_cp(EGTN_OFF);
	chrg_set_relay_mc(EGTN_OFF);

	chrg_app.state = ST_CHRG_IDLE;
	chrg_app.detection_state = CHRG_DETECTION_STANDBY;
	EGTN_APP_CHRG_set_standby_charging();

	chrg_app.instant_vrms = 0;
	chrg_app.instant_irms = 0;
	chrg_app.instant_power = 0;

	chrg_app.active_energy = 0;
	chrg_app.startpoint_active_energy = 0;
	chrg_app.endpoint_active_energy = 0;
	chrg_app.use_active_energy = 0;

	chrg_app.internal_temp = 0;
	chrg_app.cp_h_voltage = 0;
	chrg_app.cp_l_voltage = 0;
	chrg_app.cp_state = default0;

	EGTN_APP_CHRG_set_active_irms(EGUHA_MAX_AMPE);
	chrg_off_cp_pwm_duty();

	chrg_app.usercheck_info.mask[CHRG_USERCHECK_MOBILE] = 1;
	chrg_app.usercheck_info.mask[CHRG_USERCHECK_RFID] = 0;
	chrg_app.usercheck_info.mask[CHRG_USERCHECK_BUTTON] = 0;
	for(i=0;i<CHRG_USERCHECK_TYPE_MAX;i++)
	{
		chrg_app.usercheck_info.step[i] = CHRG_USERCHECK_SEQ_NON;
		chrg_app.usercheck_info.certi_state[i] = CHRG_USERCHECK_CERTI_STANDBY;
	}
	memset(chrg_app.usercheck_info.auth_user_info,'\0',CHRG_USERCHECK_AUTH_INFO_MAX_LENGTH);
	memset(chrg_app.usercheck_info.auth_req_data,'\0',CHRG_USERCHECK_AUTH_INFO_MAX_LENGTH);

	printf("CHRG_APP : go to chrg_A1 \r\n");

	SM_Event(EGUHA_CHRG_SM,EGTN_APP_CHRG_start,NULL);

	return ret;
}

void EGTN_APP_CHRG_main()
{
	EGTN_APP_CHRG_update_parameter_loop();

	chrg_usercheck_loop();

	if(0)
	{
		SM_Event(EGUHA_CHRG_SM,EGTN_APP_CHRG_stop,NULL);
	}
	else if((DC_N12V == chrg_app.cp_state)
			|| (Err_PWMH == chrg_app.cp_state)
			|| (Err_PWML == chrg_app.cp_state)
			|| (Err_DC == chrg_app.cp_state))
	{
		SM_Event(EGUHA_CHRG_SM,EGTN_APP_CHRG_fault,NULL);
	}
	else
	{
		SM_Event(EGUHA_CHRG_SM,EGTN_APP_CHRG_handling,NULL);
	}

	chrg_wake_up_seq_loop();

	EGTN_APP_CHRG_display_loop();
}

void EGTN_APP_CHRG_process()
{
	EGTN_LIB_USERDELAY_start(&gDelay_chrg_periodic_loop_time, DELAY_RENEW_OFF);

    if(EGTN_LIB_USERDELAY_isfired(&gDelay_chrg_periodic_loop_time))
    {
    	EGTN_APP_CHRG_main();

	  	EGTN_LIB_USERDELAY_start(&gDelay_chrg_periodic_loop_time, DELAY_RENEW_ON);
    }
}
