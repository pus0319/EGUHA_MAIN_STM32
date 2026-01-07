/*
 * evon_mw_uart.h
 *
 *  Created on: Apr 8, 2022
 *      Author: EVERON
 */

#ifndef EGTN_MW_INC_EGTN_MW_UART_H_
#define EGTN_MW_INC_EGTN_MW_UART_H_

#include "main.h"
#include "usart.h"

#include "egtn_app_blecomm.h"

void EGTN_MW_UART_init(void);
void EGTN_MW_UART_tx01(uint8_t* tx_b, uint16_t tx_cnt);
void EGTN_MW_UART_tx03(uint8_t* tx_b, uint16_t tx_cnt);
void EGTN_MW_UART_tx05(uint8_t* tx_b, uint16_t tx_cnt);


#endif /* EGTN_MW_INC_EGTN_MW_UART_H_ */
