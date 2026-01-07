/*
 * egtn_mw_pwm.h
 *
 *  Created on: Dec 17, 2025
 *      Author: USER
 */

#ifndef EGTN_MW_EGTN_MW_PWM_H_
#define EGTN_MW_EGTN_MW_PWM_H_

#include "main.h"
#include "tim.h"

#include "egtn_lib_logging.h"

#define PWM_TIM	(htim3)
#define PWM_CH	(TIM_CHANNEL_3)

void EGTN_MW_PWM_init();
void EGTN_MW_PWM_set_duty(double duty);
double EGTN_MW_PWM_get_duty(double duty);

#endif /* EGTN_MW_EGTN_MW_PWM_H_ */
