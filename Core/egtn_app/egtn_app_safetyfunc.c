/*
 * egtn_app_safetyfunc.c
 *
 *  Created on: Dec 19, 2025
 *      Author: USER
 */

#include "egtn_app_safetyfunc.h"

static gUserDelay gDelay_sftf_periodic_loop_time;

uint8_t EGTN_APP_SFTF_startup()
{
	uint8_t ret = 1;

	EGTN_LIB_USERDELAY_set(&gDelay_sftf_periodic_loop_time,5);

	return ret;
}

uint8_t EGTN_APP_SFTF_init()
{
	uint8_t ret = 1;


	return ret;
}

void EGTN_APP_SFTF_main()
{

}

void EGTN_APP_SFTF_process()
{
	EGTN_LIB_USERDELAY_start(&gDelay_sftf_periodic_loop_time, DELAY_RENEW_OFF);

    if(EGTN_LIB_USERDELAY_isfired(&gDelay_sftf_periodic_loop_time))
    {
    	EGTN_APP_SFTF_main();

	  	EGTN_LIB_USERDELAY_start(&gDelay_sftf_periodic_loop_time, DELAY_RENEW_ON);
    }
}
