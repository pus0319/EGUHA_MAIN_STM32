/*
 * egtn_app_blecomm.h
 *
 *  Created on: Dec 19, 2025
 *      Author: USER
 */

#ifndef EGTN_APP_EGTN_APP_BLECOMM_H_
#define EGTN_APP_EGTN_APP_BLECOMM_H_

#include "main.h"

#include "egtn_lib_userdelay.h"
#include "egtn_lib_u8queue.h"

#include "egtn_mw_FC41D.h"

typedef enum e_ble_state
{
	BLE_STAT_INIT,
	BLE_STAT_STANDBY,
	BLE_STAT_SCANNING,
	BLE_STAT_ADVERTISING,
	BLE_STAT_CONNECTED,
	BLE_STAT_END
}e_BLE_STATE;

typedef struct s_ble_info
{
	e_BLE_STATE state;
	uint8_t	is_state_change;
}s_BLE_INFO;

uint8_t EGTN_APP_BLE_startup();
uint8_t EGTN_APP_BLE_init();
void EGTN_APP_BLE_process();

#endif /* EGTN_APP_EGTN_APP_BLECOMM_H_ */
