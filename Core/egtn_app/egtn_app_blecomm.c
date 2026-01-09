/*
 * egtn_app_blecomm.c
 *
 *  Created on: Dec 19, 2025
 *      Author: USER
 */

#include "egtn_app_blecomm.h"

static s_BLE_INFO ble_app =
{
		BLE_STAT_INIT,
		0
};

static gUserDelay gDelay_blecomm_periodic_loop_time;

void app_ble_change_state(e_BLE_STATE state)
{
	ble_app.state = state;
	ble_app.is_state_change = 1;
}
uint8_t app_ble_is_state_change()
{
	uint8_t ret = ble_app.is_state_change;
	ble_app.is_state_change = 0;

	return ret;
}

void EGTN_APP_BLE_peripheral_state_machine()
{
	switch(ble_app.state)
	{
		case BLE_STAT_INIT :
#if((__TEST_CHARGING_DEMO__)==1)
			if(1 == EGTN_MW_FC41D_ble_peripheral_init_demo())
			{
				ble_app.state = BLE_STAT_CONNECTED;
			}
#else
			if(0)
			{
				ble_app.state = BLE_STAT_STANDBY;
			}
#endif
		break;
		case BLE_STAT_STANDBY :
			if(1 == app_ble_is_state_change())
			{

			}

		break;
		case BLE_STAT_SCANNING :
			if(1 == app_ble_is_state_change())
			{

			}

		break;
		case BLE_STAT_ADVERTISING :
			if(1 == app_ble_is_state_change())
			{

			}

		break;
		case BLE_STAT_CONNECTED :
			if(1 == app_ble_is_state_change())
			{

			}

		break;
		default :

		break;
	}
}

uint8_t EGTN_APP_BLE_startup()
{
	uint8_t ret = 1;

	EGTN_MW_FC41D_startup();

	EGTN_LIB_USERDELAY_set(&gDelay_blecomm_periodic_loop_time,50);

	return ret;
}

uint8_t EGTN_APP_BLE_init()
{
	uint8_t ret = 1;

	ble_app.state = BLE_STAT_INIT;
	ble_app.is_state_change = 0;

	return ret;
}

void EGTN_APP_BLE_main()
{
	EGTN_APP_BLE_peripheral_state_machine();

	EGTN_MW_FC41D_ble_peripheral_loop();
}

void EGTN_APP_BLE_process()
{
	EGTN_LIB_USERDELAY_start(&gDelay_blecomm_periodic_loop_time, DELAY_RENEW_OFF);

    if(EGTN_LIB_USERDELAY_isfired(&gDelay_blecomm_periodic_loop_time))
    {
    	EGTN_APP_BLE_main();

	  	EGTN_LIB_USERDELAY_start(&gDelay_blecomm_periodic_loop_time, DELAY_RENEW_ON);
    }
}
