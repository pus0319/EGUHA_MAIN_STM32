/*
 * egtn_app_sys.h
 *
 *  Created on: Dec 19, 2025
 *      Author: USER
 */

#ifndef EGTN_APP_EGTN_APP_SYS_H_
#define EGTN_APP_EGTN_APP_SYS_H_

#include "main.h"
#include "math.h"
#include "iwdg.h"

#include "egtn_lib_userdelay.h"

#include "egtn_embd_fs.h"
#include "egtn_mw_adc.h"
#include "egtn_mw_cp.h"
#include "egtn_mw_gpio.h"
#include "egtn_mw_indiled.h"
#include "egtn_mw_it.h"
#include "egtn_mw_ntc.h"
#include "egtn_mw_pwm.h"
#include "egtn_mw_relay.h"
#include "egtn_mw_serialflash.h"
#include "egtn_mw_uart.h"

/*
 * *************************************************************************
 *  AC_V,AC_I,ZCT calc
 *
 *  see "EGUHA_A_V_CCID20_RMS_schematic_equation" document
 *
 */
#define AC_ALL_CAL_DELTA_T_MAX	(167)
#define AC_ALL_CAL_DELTA_T_LIMIT	(200)

#define AC_V_MCU_V_SHIFT	(1.65f)
#define AC_I_MCU_V_SHIFT	(1.6405f)
#define ZCT_I_MCU_V_SHIFT	(1.978f)

#define AC_V_MCU_V_SHIFT_INT	(165)	// 10^7
#define AC_I_MCU_V_SHIFT_INT	(164)	// 10^7
#define ZCT_I_MCU_V_SHIFT_INT	(198)	// 10^7

// y = ax
// y : AC_V or I or ZCT_I
// a : ALPHA
// x : MCU_V_SHIFT_ABS

#define AC_V_TO_ALPHA		(248.05f)
#define AC_I_TO_ALPHA		(52.2876f)
#define ZCT_I_TO_ALPHA		(26.5816f)

#define AC_V_TO_ALPHA_INT		(248)
#define AC_I_TO_ALPHA_INT		(523)
#define ZCT_I_TO_ALPHA_INT		(266)

#define ZCT_I_MCU_LIMIT		(4071)
#define ZCT_I_LIMIT			(24.8f)
#define ZCT_I_MIN			(15.0f)
#define ZCT_INTERRUPT_T_CALC_MS(X)		((((-0.15f)*(X)) + (3.75f)) * (1000.0f))
/*
 ***********************************************************************
 */

typedef struct
{
	uint32_t ac_vrms;
	uint32_t ac_irms;
	uint32_t ac_zctrms;
}s_EGUHA_SYS_INFO;

uint32_t EGTN_APP_SYS_get_ac_vrms();
uint32_t EGTN_APP_SYS_get_ac_irms();
uint32_t EGTN_APP_SYS_get_ac_zctrms();

uint8_t EGTN_APP_SYS_startup();
uint8_t EGTN_APP_SYS_init();
void EGTN_APP_SYS_process();

#endif /* EGTN_APP_EGTN_APP_SYS_H_ */
