/*
 * eguha_bootloader_config.h
 *
 *  Created on: 2025. 12. 16.
 *      Author: USER
 */

#ifndef EGTN_CONFIG_EGUHA_BOOTLOADER_CONFIG_H_
#define EGTN_CONFIG_EGUHA_BOOTLOADER_CONFIG_H_

#define EGTN_ON 		0x01
#define EGTN_OFF		0x00
#define EGTN_CONTINUE	0x02

#define EGTN_TRUE 		0x01
#define EGTN_FALSE		0x00

#define EGUHA_MAIN_VERSION		"010101"

#define __TEST_DMA_GPIO_STE_LED__		0

#define AC_FREQ_HZ_100US		167

typedef enum e_customtype_bool
{
	C_BOOL_FALSE,
	C_BOOL_TRUE,
	C_BOOL_END
}e_CUSTOMTYPE_BOOL;

typedef enum e_process_priority
{
	P_SYS_process,
	P_SAFETY_FUNC_process,
	P_CHARGING_process,
	P_BLE_COMM_process
}e_PROCESS_PRIORITY;

#endif /* EGTN_CONFIG_EGUHA_BOOTLOADER_CONFIG_H_ */
