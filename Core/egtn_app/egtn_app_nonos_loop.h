/*
 * egtn_app_nonos_loop.h
 *
 *  Created on: Dec 19, 2025
 *      Author: USER
 */

#ifndef EGTN_APP_EGTN_APP_NONOS_LOOP_H_
#define EGTN_APP_EGTN_APP_NONOS_LOOP_H_

#include "main.h"

#include "egtn_mw_it.h"
#include "egtn_lib_userdelay.h"
#include "egtn_lib_logging.h"

#include "egtn_app_sys.h"
#include "egtn_app_safetyfunc.h"
#include "egtn_app_charging.h"
#include "egtn_app_blecomm.h"

typedef enum e_operate_type
{
	OPERATE_SYSTEM_STARTUP,
	OPERATE_SYSTEM_INIT,
	OPERATE_SYSTEM_ACT,
	OPERATE_TYPE_END
}e_OPERATE_TYPE;

void EGUHAsystem(void);

#endif /* EGTN_APP_EGTN_APP_NONOS_LOOP_H_ */
