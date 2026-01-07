/*
 * evon_lib_userdelay.c
 *
 *  Created on: 2022. 4. 19.
 *      Author: EVERON
 */


#include "egtn_lib_logging.h"
#include "egtn_lib_userdelay.h"

static volatile uint32_t gUserDelayTick = 0;


void EGTN_LIB_USERDELAY_tickcount(void)
{
	gUserDelayTick++;
}

uint32_t EGTN_LIB_USERDLEAY_gettick(void)
{
	return gUserDelayTick;
}

void EGTN_LIB_USERDELAY_set(gUserDelay *Delay, unsigned long delayvalue)
{
	unsigned long delay_to_tick = delayvalue * GUSERDELAY_PERIOD;

	if(delay_to_tick == 0)
	{
		Delay->nDelay = 0;
		return;
	}
	else
	{
		Delay->nDelay = delay_to_tick;
		//printf("delay : %ld\r\n", delay_to_tick);
	}

	Delay->state = DELAY_INACTIVE;
	Delay->uStartTick = delay_to_tick;
}

unsigned int EGTN_LIB_USERDELAY_start(gUserDelay *Delay, tUSERDELAYRENEWSTAT Renew)
{
	if(Renew == DELAY_RENEW_OFF)
	{
		if(Delay->state == DELAY_ACTIVE)		return 0;
	}

	Delay->state = DELAY_ACTIVE;
	Delay->uStartTick = gUserDelayTick;
	//printf("StartTick = %ld\r\n", gUserDelayTick);
	return 1;
}

void EGTN_LIB_USERDELAY_stop(gUserDelay *Delay)
{
	Delay->state = DELAY_INACTIVE;
}

unsigned long CheckDelayValue(unsigned long nStartTime)
{
	unsigned long uCurrentTick;
	//unsigned long starttime_to_tick = nStartTime;


	uCurrentTick = gUserDelayTick;

	if(uCurrentTick >= nStartTime)
	{
		return (uCurrentTick - nStartTime);
	}
	else
	{
		return (0xFFFFFFFF - nStartTime + 1 + uCurrentTick);
	}
}

unsigned int EGTN_LIB_USERDELAY_isfired(gUserDelay *Delay)
{
	if(Delay->state == DELAY_INACTIVE)
	{
		return 0;
	}
	if(CheckDelayValue(Delay->uStartTick) >= Delay->nDelay)
	{

		return 1;
	}
	else
	{
		return 0;
	}
}


