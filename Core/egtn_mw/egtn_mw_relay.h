/*
 * egtn_mw_relay.h
 *
 *  Created on: Dec 18, 2025
 *      Author: USER
 */

#ifndef EGTN_MW_EGTN_MW_RELAY_H_
#define EGTN_MW_EGTN_MW_RELAY_H_

#include "main.h"

#include "egtn_lib_userdelay.h"
#include "egtn_mw_gpio.h"
#include "egtn_mw_pwm.h"

void EGTN_MW_RELAY_init();
uint8_t EGTN_MW_RELAY_set_cp_ctl(uint8_t value);
uint8_t EGTN_MW_RELAY_get_cp_ctl();
uint8_t EGTN_MW_RELAY_set_mc_ctl(uint8_t value);
uint8_t EGTN_MW_RELAY_get_mc_ctl();
void EGTN_MW_RELAY_main();

#endif /* EGTN_MW_EGTN_MW_RELAY_H_ */
