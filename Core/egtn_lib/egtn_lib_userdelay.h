/*
 * evon_lib_userdelay.h
 *
 *  Created on: 2022. 4. 19.
 *      Author: EVERON
 */

#ifndef EGTN_LIB_INC_EGTN_LIB_USERDELAY_H_
#define EGTN_LIB_INC_EGTN_LIB_USERDELAY_H_

#include "main.h"

#define GUSERDELAY_PERIOD		10		//unit : ms

// Delay status
typedef enum {DELAY_INACTIVE,DELAY_ACTIVE,USERDELAYSTAT_END}			tUSERDELAYSTAT;
typedef enum {DELAY_RENEW_OFF,DELAY_RENEW_ON,USERDELAYRENEWSTAT_END}	tUSERDELAYRENEWSTAT;

typedef struct SETDELAY{
	tUSERDELAYSTAT state;
	unsigned long uStartTick;
	unsigned long nDelay;
}gUserDelay;

void EGTN_LIB_USERDELAY_tickcount(void);
uint32_t EGTN_LIB_USERDLEAY_gettick(void);
void EGTN_LIB_USERDELAY_set(gUserDelay *Delay, unsigned long delayvalue);
unsigned int EGTN_LIB_USERDELAY_start(gUserDelay *Delay, tUSERDELAYRENEWSTAT Renew);
void EGTN_LIB_USERDELAY_stop(gUserDelay *Delay);
unsigned long CheckDelayValue(unsigned long nStartTime);
unsigned int EGTN_LIB_USERDELAY_isfired(gUserDelay *Delay);


#endif /* EGTN_LIB_INC_EGTN_LIB_USERDELAY_H_ */
