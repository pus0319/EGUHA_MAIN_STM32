/*
 * evon_mw_gpio.c
 *
 *  Created on: 2022. 5. 16.
 *      Author: EVERON
 */

#include "egtn_mw_gpio.h"
#include "egtn_lib_logging.h"

static s_GPO_TYPE gpo_list[E_GPO_MAX] =
{
		{RLED_GPIO_Port,RLED_Pin,C_BOOL_FALSE},//R_LEDBAR,
		{GLED_GPIO_Port,GLED_Pin,C_BOOL_FALSE},//G_LEDBAR,
		{BLED_GPIO_Port,BLED_Pin,C_BOOL_FALSE},//B_LEDBAR,
		{GMI_ENABLE_GPIO_Port,GMI_ENABLE_Pin,C_BOOL_FALSE},//GMI_ENABLE,
		{CCID_SELF_ENABLE_GPIO_Port,CCID_SELF_ENABLE_Pin,C_BOOL_FALSE},//CCID_SELF_ENABLE,
		{CP_RY_GPIO_Port,CP_RY_Pin,C_BOOL_FALSE},//CP_RY,
		{MC1_GPIO_Port,MC1_Pin,C_BOOL_FALSE},//MC,
		{STE_LED1_GPIO_Port,STE_LED1_Pin,C_BOOL_FALSE},//STE_LED1,
		{BLE_WAKEUP_IN_GPIO_Port,BLE_WAKEUP_IN_Pin,C_BOOL_FALSE},//BLE_WAKEUP_IN,
		{BLE_RST_GPIO_Port,BLE_RST_Pin,C_BOOL_FALSE}//BLE_RST,
};
static s_GPI_TYPE gpi_list[E_GPI_MAX] =
{
		{BLE_NET_STATUS_GPIO_Port,BLE_NET_STATUS_Pin},//BLE_NET_STATUS,
		{BLE_WAKEUP_OUT_GPIO_Port,BLE_WAKEUP_OUT_Pin},//BLE_WAKEUP_OUT,
		{I_EMG_GPIO_Port,I_EMG_Pin}//I_EMG,
};

void EGTN_MW_GPIO_init()
{
	EGTN_MW_GPIO_set_gpo(R_LEDBAR, GPIO_PIN_RESET);
	EGTN_MW_GPIO_set_gpo(G_LEDBAR, GPIO_PIN_RESET);
	EGTN_MW_GPIO_set_gpo(B_LEDBAR, GPIO_PIN_RESET);
	EGTN_MW_GPIO_set_gpo(GMI_ENABLE, GPIO_PIN_RESET);
	EGTN_MW_GPIO_set_gpo(CCID_SELF_ENABLE, GPIO_PIN_RESET);
	EGTN_MW_GPIO_set_gpo(CP_RY, GPIO_PIN_RESET);
	EGTN_MW_GPIO_set_gpo(MC, GPIO_PIN_RESET);
	EGTN_MW_GPIO_set_gpo(STE_LED1, GPIO_PIN_SET);
	EGTN_MW_GPIO_set_gpo(BLE_WAKEUP_IN, GPIO_PIN_RESET);
	EGTN_MW_GPIO_set_gpo(BLE_RST, GPIO_PIN_RESET);
}

#if 0
/*
 * return 0 : Fail
 * return 1 : Success
 * return 2 : is Locked
 */
uint8_t EGTN_MW_GPIO_set_gpo(e_GPO gpo_num, GPIO_PinState onoff, uint8_t lock)
{
	uint8_t ret = 1;

	if(gpo_num >= E_GPO_MAX)
	{
		ret = 0;
	}
	if(1 == gpo_list[gpo_num].CtlLock)
	{
		if((0 == lock) && (onoff == HAL_GPIO_ReadPin(gpo_list[gpo_num].GPOx, gpo_list[gpo_num].GPOpin)))
		{
			ret = 1;
		}
		else
		{
			ret = 2;
		}
	}

	if(1 == ret)
	{
		HAL_GPIO_WritePin(gpo_list[gpo_num].GPOx, gpo_list[gpo_num].GPOpin, onoff);
		gpo_list[gpo_num].CtlLock = lock;
	}

	return ret;
}
#else
uint8_t EGTN_MW_GPIO_set_gpo(e_GPO gpo_num, GPIO_PinState onoff)
{
	uint8_t ret = 1;

	if(gpo_num >= E_GPO_MAX)
	{
		ret = 0;
	}
	if(1 == gpo_list[gpo_num].CtlLock)
	{
		ret = 0;
	}

	if(1 == ret)
	{
		HAL_GPIO_WritePin(gpo_list[gpo_num].GPOx, gpo_list[gpo_num].GPOpin, onoff);
	}

	return ret;
}
uint8_t EGTN_MW_GPIO_lock_gpo(e_GPO gpo_num, uint8_t lock)
{
	uint8_t ret = 1;

	if(lock != gpo_list[gpo_num].CtlLock)
	{
		gpo_list[gpo_num].CtlLock = lock;
	}
	else
	{
		ret = 2;
	}

	return ret;
}
#endif
uint8_t EGTN_MW_GPIO_get_gpo(e_GPO gpo_num)
{
	uint8_t ret;

	if(GPIO_PIN_SET == HAL_GPIO_ReadPin(gpo_list[gpo_num].GPOx, gpo_list[gpo_num].GPOpin))
	{
		ret = 1;
	}
	else
	{
		ret = 0;
	}

	return ret;
}
uint8_t EGTN_MW_GPIO_get_gpi(e_GPI gpi_num)
{
	uint8_t ret;

	if(GPIO_PIN_SET == HAL_GPIO_ReadPin(gpi_list[gpi_num].GPIx, gpi_list[gpi_num].GPIpin))
	{
		ret = 1;
	}
	else
	{
		ret = 0;
	}

	return ret;
}

