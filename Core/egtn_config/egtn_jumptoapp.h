/*
 * egtn_jumptoapp.h
 *
 *  Created on: Dec 15, 2025
 *      Author: USER
 */

#ifndef EGTN_APP_EGTN_JUMPTOAPP_H_
#define EGTN_APP_EGTN_JUMPTOAPP_H_

#include "main.h"

// https://community.st.com/t5/stm32-mcus-embedded-software/stm32f0x0-custom-bootloader/td-p/799560
// https://marcelojo.org/bootloader-on-stm32f0/

#define VECTOR_TABLE_SIZE 48  // Covers 0xC0 bytes (16 + IRQs)
#define APP_VECTOR_TABLE  ((uint32_t*)0x08010000)
#define RAM_VECTOR_TABLE  ((uint32_t*)0x20000000)

void EGTN_JUMPTOAPP_relocate_vector_table_to_ram(void);

#endif /* EGTN_APP_EGTN_JUMPTOAPP_H_ */
