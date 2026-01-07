/*
 * evon_mw_gpio.h
 *
 *  Created on: 2022. 5. 16.
 *      Author: EVERON
 */

#ifndef EGTN_MW_INC_EGTN_MW_GPIO_H_
#define EGTN_MW_INC_EGTN_MW_GPIO_H_


#include "main.h"

typedef enum e_gpo
{
	R_LEDBAR,
	G_LEDBAR,
	B_LEDBAR,
	GMI_ENABLE,
	CCID_SELF_ENABLE,
	CP_RY,
	MC,
	STE_LED1,
	BLE_WAKEUP_IN,
	BLE_RST,
	E_GPO_MAX
}e_GPO;

typedef enum e_gpi
{
	BLE_NET_STATUS,
	BLE_WAKEUP_OUT,
	I_EMG,
	E_GPI_MAX
}e_GPI;

typedef struct
{
	GPIO_TypeDef* 		GPOx;
	uint16_t	  		GPOpin;
	uint8_t				CtlLock;
}s_GPO_TYPE;
typedef struct
{
	GPIO_TypeDef* GPIx;
	uint16_t	  GPIpin;
}s_GPI_TYPE;


#if 0
#define GPO_STUS_LED_01_ON			HAL_GPIO_WritePin(STUS_LED_01_GPIO_Port, STUS_LED_01_Pin, GPIO_PIN_RESET)
#define GPO_STUS_LED_01_OFF			HAL_GPIO_WritePin(STUS_LED_01_GPIO_Port, STUS_LED_01_Pin, GPIO_PIN_SET)

#define GPI_SET_SW_01_IN			HAL_GPIO_ReadPin(DIPSW_1_GPIO_Port, DIPSW_1_Pin)
#define GPI_SET_SW_02_IN			HAL_GPIO_ReadPin(DIPSW_2_GPIO_Port, DIPSW_2_Pin)

#define CHARGSERV_READ_DEV						(0 == GPI_DEV_IN)
#else

#endif

void EGTN_MW_GPIO_init();
#if 0
uint8_t EGTN_MW_GPIO_set_gpo(e_GPO gpo_num, GPIO_PinState onoff, uint8_t lock);
#else
uint8_t EGTN_MW_GPIO_set_gpo(e_GPO gpo_num, GPIO_PinState onoff);
uint8_t EGTN_MW_GPIO_lock_gpo(e_GPO gpo_num, uint8_t lock);
#endif
uint8_t EGTN_MW_GPIO_get_gpo(e_GPO gpo_num);
uint8_t EGTN_MW_GPIO_get_gpi(e_GPI gpi_num);


#endif /* EGTN_MW_INC_EGTN_MW_GPIO_H_ */
