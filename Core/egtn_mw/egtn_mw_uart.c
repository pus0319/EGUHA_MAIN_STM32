/*
 * evon_mw_uart.c
 *
 *  Created on: Apr 8, 2022
 *      Author: EVERON
 */

#include "egtn_mw_uart.h"

static uint8_t evon_it_rx01 = 0;
static uint8_t evon_it_rx03 = 0;
static uint8_t evon_it_rx05 = 0;

void EGTN_MW_UART_init(void)
{
	HAL_UART_Receive_IT(&huart1, &evon_it_rx01, 1);
	HAL_UART_Receive_IT(&huart3, &evon_it_rx03, 1);
	HAL_UART_Receive_IT(&huart5, &evon_it_rx05, 1);
}
void EGTN_MW_UART_tx01(uint8_t* tx_b, uint16_t tx_cnt)
{
	HAL_UART_Transmit(&huart1, tx_b, tx_cnt, 100);
}
void EGTN_MW_UART_tx03(uint8_t* tx_b, uint16_t tx_cnt)
{
	HAL_UART_Transmit(&huart3, tx_b, tx_cnt, 100);
}
void EGTN_MW_UART_tx05(uint8_t* tx_b, uint16_t tx_cnt)
{
	HAL_UART_Transmit(&huart5, tx_b, tx_cnt, 100);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		HAL_UART_Receive_IT(&huart1, &evon_it_rx01, 1);
		EGTN_MW_FC41D_push_ringbuffer(evon_it_rx01);
	}
	if(huart->Instance == USART3)
	{
		HAL_UART_Receive_IT(&huart3, &evon_it_rx03, 1);
		//EGTN_APP_DEBUG_push_ringbuffer(evon_it_rx03);
	}
	if(huart->Instance == USART5)
	{
		HAL_UART_Receive_IT(&huart5, &evon_it_rx05, 1);
		//EGTN_APP_RFID_push_ringbuffer(evon_it_rx05);
	}
}
