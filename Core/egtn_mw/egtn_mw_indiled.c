/*
 * evon_mw_indiled.c
 *
 *  Created on: 2022. 5. 16.
 *      Author: EVERON
 */


#include "egtn_mw_indiled.h"
#include "egtn_mw_gpio.h"

void EGTN_MW_INDILED_init()
{
	//EGTN_MW_INDILED_bdled_ctl(BLACK);
	EGTN_MW_INDILED_sled_ctl(PURPLE);
}

uint8_t EGTN_MW_INDILED_sled_ctl(e_EGTN_INDI_LED_COLOR color)
{
	switch(color)
	{
		case RED :
			EGTN_MW_GPIO_set_gpo(R_LEDBAR, GPIO_PIN_SET);
			EGTN_MW_GPIO_set_gpo(G_LEDBAR, GPIO_PIN_RESET);
			EGTN_MW_GPIO_set_gpo(B_LEDBAR, GPIO_PIN_RESET);
		break;

		case GREEN :
			EGTN_MW_GPIO_set_gpo(R_LEDBAR, GPIO_PIN_RESET);
			EGTN_MW_GPIO_set_gpo(G_LEDBAR, GPIO_PIN_SET);
			EGTN_MW_GPIO_set_gpo(B_LEDBAR, GPIO_PIN_RESET);
		break;

		case BLUE :
			EGTN_MW_GPIO_set_gpo(R_LEDBAR, GPIO_PIN_RESET);
			EGTN_MW_GPIO_set_gpo(G_LEDBAR, GPIO_PIN_RESET);
			EGTN_MW_GPIO_set_gpo(B_LEDBAR, GPIO_PIN_SET);
		break;

		case YELLOW :
			EGTN_MW_GPIO_set_gpo(R_LEDBAR, GPIO_PIN_SET);
			EGTN_MW_GPIO_set_gpo(G_LEDBAR, GPIO_PIN_SET);
			EGTN_MW_GPIO_set_gpo(B_LEDBAR, GPIO_PIN_RESET);
		break;

		case SKY :
			EGTN_MW_GPIO_set_gpo(R_LEDBAR, GPIO_PIN_RESET);
			EGTN_MW_GPIO_set_gpo(G_LEDBAR, GPIO_PIN_SET);
			EGTN_MW_GPIO_set_gpo(B_LEDBAR, GPIO_PIN_SET);
		break;

		case PURPLE :
			EGTN_MW_GPIO_set_gpo(R_LEDBAR, GPIO_PIN_SET);
			EGTN_MW_GPIO_set_gpo(G_LEDBAR, GPIO_PIN_RESET);
			EGTN_MW_GPIO_set_gpo(B_LEDBAR, GPIO_PIN_SET);
		break;

		case WHITE :
			EGTN_MW_GPIO_set_gpo(R_LEDBAR, GPIO_PIN_SET);
			EGTN_MW_GPIO_set_gpo(G_LEDBAR, GPIO_PIN_SET);
			EGTN_MW_GPIO_set_gpo(B_LEDBAR, GPIO_PIN_SET);
		break;

		case BLACK :
		default :	// Black
			EGTN_MW_GPIO_set_gpo(R_LEDBAR, GPIO_PIN_RESET);
			EGTN_MW_GPIO_set_gpo(G_LEDBAR, GPIO_PIN_RESET);
			EGTN_MW_GPIO_set_gpo(B_LEDBAR, GPIO_PIN_RESET);
		break;
	}

	return EGTN_TRUE;
}


