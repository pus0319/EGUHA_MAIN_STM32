/*
 * egtn_jumptoapp.c
 *
 *  Created on: Dec 15, 2025
 *      Author: USER
 */

#include "egtn_jumptoapp.h"

void EGTN_JUMPTOAPP_relocate_vector_table_to_ram(void)
{
	for (uint32_t i = 0; i < VECTOR_TABLE_SIZE; i++) {
		RAM_VECTOR_TABLE[i] = APP_VECTOR_TABLE[i];
	}
	__HAL_SYSCFG_REMAPMEMORY_SRAM();
}


