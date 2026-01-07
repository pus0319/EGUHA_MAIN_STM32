/*
 * egtn_app_nonos_loop.c
 *
 *  Created on: Dec 19, 2025
 *      Author: USER
 */

#include "egtn_app_nonos_loop.h"

static e_OPERATE_TYPE eguhaoperatetype = OPERATE_SYSTEM_STARTUP;

uint8_t EGUHAbooting(void)
{
	uint8_t ret = 0;
	static uint8_t is_startup = 0x00;
	uint8_t startup_complete = (1 << P_SYS_process) | (1 << P_SAFETY_FUNC_process) | (1 << P_CHARGING_process) | (1 << P_BLE_COMM_process);

	if(0x00 == (is_startup & (1 << P_SYS_process)))
	{
		if(1 == EGTN_APP_SYS_startup())
		{
			is_startup |= (1 << P_SYS_process);
		}
	}
	if(0x00 == (is_startup & (1 << P_SAFETY_FUNC_process)))
	{
		if(1 == EGTN_APP_SFTF_startup())
		{
			is_startup |= (1 << P_SAFETY_FUNC_process);
		}
	}
	if(0x00 == (is_startup & (1 << P_CHARGING_process)))
	{
		if(1 == EGTN_APP_CHRG_startup())
		{
			is_startup |= (1 << P_CHARGING_process);
		}
	}
	if(0x00 == (is_startup & (1 << P_BLE_COMM_process)))
	{
		if(1 == EGTN_APP_BLE_startup())
		{
			is_startup |= (1 << P_BLE_COMM_process);
		}
	}

	if(is_startup == startup_complete)
	{
		ret = 1;
	}

	return ret;
}

uint8_t EGUHAiniting(void)
{
	uint8_t ret = 0;
	static uint8_t is_init = 0x00;
	uint8_t init_complete = (1 << P_SYS_process) | (1 << P_SAFETY_FUNC_process) | (1 << P_CHARGING_process) | (1 << P_BLE_COMM_process);

	if(0x00 == (is_init & (1 << P_SYS_process)))
	{
		if(1 == EGTN_APP_SYS_init())
		{
			is_init |= (1 << P_SYS_process);
		}
	}
	if(0x00 == (is_init & (1 << P_SAFETY_FUNC_process)))
	{
		if(1 == EGTN_APP_SFTF_init())
		{
			is_init |= (1 << P_SAFETY_FUNC_process);
		}
	}
	if(0x00 == (is_init & (1 << P_CHARGING_process)))
	{
		if(1 == EGTN_APP_CHRG_init())
		{
			is_init |= (1 << P_CHARGING_process);
		}
	}
	if(0x00 == (is_init & (1 << P_BLE_COMM_process)))
	{
		if(1 == EGTN_APP_BLE_init())
		{
			printf("bleinitok\r\n");
			is_init |= (1 << P_BLE_COMM_process);
		}
	}

	if(is_init == init_complete)
	{
		ret = 1;
	}

	return ret;
}

void EGUHAmain(void)
{
	EGTN_APP_SYS_process();

	EGTN_APP_SFTF_process();

	EGTN_APP_CHRG_process();

	EGTN_APP_BLE_process();
}


void EGUHAsystem(void)
{
	printf("-----------------------------------\r\n");
	printf("----EGUHA_MAIN---------------------\r\n");
	printf("----VER : %s --\r\n",EGUHA_MAIN_VERSION);
	EGTN_LIB_LOGGING_print_date_time("----COMPILE : ");

	while(1)
	{
		HAL_IWDG_Refresh(&hiwdg);

		switch(eguhaoperatetype)
		{
			case OPERATE_SYSTEM_STARTUP :
				if(1 == EGUHAbooting())
				{
					printf("go to init\r\n");
					eguhaoperatetype = OPERATE_SYSTEM_INIT;
				}
			break;
			case OPERATE_SYSTEM_INIT :
				if(1 == EGUHAiniting())
				{
					printf("go to main\r\n");
					eguhaoperatetype = OPERATE_SYSTEM_ACT;
				}
			break;
			case OPERATE_SYSTEM_ACT :
				EGUHAmain();
			break;
			default :

			break;
		}
	}
}
