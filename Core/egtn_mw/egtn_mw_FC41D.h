/*
 * egtn_mw_FC41D.h
 *
 *  Created on: Dec 29, 2025
 *      Author: USER
 */

#ifndef EGTN_MW_EGTN_MW_FC41D_H_
#define EGTN_MW_EGTN_MW_FC41D_H_

#include "main.h"
#include "string.h"

#include "egtn_mw_uart.h"
#include "egtn_mw_gpio.h"

#include "egtn_lib_string.h"
#include "egtn_lib_u8queue.h"
#include "egtn_lib_userdelay.h"

#define FC41D_RING_BUFFER_SIZE 300

#define FC41D_AT_CMD_RESP_PIPELINE_MAX	3
#define FC41D_AT_CMD_FINAL_RESP_SIZE 30
#define FC41D_AT_CMD_INTER_URC_RESP_SIZE 100
#define FC41D_AT_CMD_RAW_DATA_SIZE 600
#define FC41D_AT_CMD_GATT_UUID_MAX_LENGTH	20
#define FC41D_AT_GATT_MAP_MAX_LENGTH		10

#define FC41D_AT_CMD_IS_OK			'O'
#define FC41D_AT_CMD_IS_ERROR		'E'
//#define FC41D_AT_CMD_IS_READY		"r"
#define FC41D_AT_CMD_IS_INTER_URC	'+'
#define FC41D_AT_CMD_IS_APP_DATA	'#'
#define FC41D_AT_CMD_IS_END_STR		"\r\n"
#define FC41D_AT_CMD_IS_END_CHR		'\n'

#define FC41D_AT_CMD_TASK_QUEUE_MAX_LENGTH	30
#define FC41D_AT_CMD_RESPONSE_TIMOUT_MS		3000

#define _TEST_GATT_CHARACTERISITC_UUID_MAP_		1

typedef enum e_fc41d_at_cmd_type
{
	FC41D_AT_CMD_TYPE_TEST,
	FC41D_AT_CMD_TYPE_READ,
	FC41D_AT_CMD_TYPE_WRITE,
	FC41D_AT_CMD_TYPE_EXECUTION,
	FC41D_AT_CMD_TYPE_URC,
	FC41D_AT_CMD_TYPE_END
}e_FC41D_AT_CMD_TYPE;

typedef enum e_fc41d_at_cmd_list
{
	FC41D_AT_CMD_NON,
	FC41D_CMD_OK,
	FC41D_CMD_ERROR,
	FC41D_CMD_DELAY,
	FC41D_AT_QRST,
	FC41D_AT_QVERSION,
	FC41D_AT_QECHO,
	FC41D_AT_QURCCFG,
	FC41D_AT_QLOWPOWER,
	FC41D_AT_QDEEPSLEEP,
	FC41D_AT_QWLMAC,
	FC41D_AT_QBLEINIT,
	FC41D_AT_QBLEADDR,
	FC41D_AT_QBLENAME,
	FC41D_AT_QBLEADVPARAM,
	FC41D_AT_QBLEADVDATA,
	FC41D_AT_QBLEGATTSSRV,
	FC41D_AT_QBLEGATTSCHAR,
	FC41D_AT_QBLEADVSTART,
	FC41D_AT_QBLEADVSTOP,
	FC41D_AT_QBLEGATTSNTFY,
	FC41D_AT_LIST_END,
	FC41D_URC_QBLESTAT,
	FC41D_URC_QBLEMTU,
	FC41D_URC_QBLEINFO,
	FC41D_URC_LIST_END,
	FC41D_CMD_ALL_LIST_END
}e_FC41D_AT_CMD_LIST;

typedef enum e_fc41d_at_cmd_resp_type
{
	FC41D_AT_RESP_NON,
	FC41D_AT_RESP_FINAL,
	FC41D_AT_RESP_INTER_URC,
	FC41D_AT_RESP_RAW_DATA,
	FC41D_AT_RESP_END
}e_FC41D_AT_CMD_RESP_TYPE;

/*
 * AT Command Syntax
 *
 * All command lines must start with AT or at and end with <CR>.
 *
 * Information responses and result codes always start and end with a carriage return character and a line feed character:
 *
 * <CR><LF><response><CR><LF>
 *
 *
 * AT Command responses example
 *
 *
 * AT+CMD1
 *
 * <CR><LF>+CMD1:<parameters><CR><LF>
 * <CR><LF>OK<CR><LF>
 *
 * or
 *
 * <CR><LF><parameters><CR><LF>
 * <CR><LF>OK<CR><LF>
 *
 * or
 *
 * <CR><LF>ERROR<CR><LF>
 *
 */

#define FC41D_QRST_STR			"+QRST"
#define FC41D_QVERSION_STR		"+QVERSION"
#define FC41D_QECHO_STR			"+QECHO"
#define FC41D_QURCCFG_STR		"+QURCCFG"
#define FC41D_QLOWPOWER_STR		"+QLOWPOWER"
#define FC41D_QDEEPSLEEP_STR	"+QDEEPSLEEP"
#define FC41D_QWLMAC_STR		"+QWLMAC"
#define FC41D_QBLEINIT_STR		"+QBLEINIT"
#define FC41D_QBLEADDR_STR		"+QBLEADDR"
#define FC41D_QBLENAME_STR		"+QBLENAME"
#define FC41D_QBLEADVPARAM_STR	"+QBLEADVPARAM"
#define FC41D_QBLEADVDATA_STR	"+QBLEADVDATA"
#define FC41D_QBLEGATTSSRV_STR	"+QBLEGATTSSRV"
#define FC41D_QBLEGATTSCHAR_STR	"+QBLEGATTSCHAR"
#define FC41D_QBLEADVSTART_STR	"+QBLEADVSTART"
#define FC41D_QBLEADVSTOP_STR	"+QBLEADVSTOP"
#define FC41D_QBLEGATTSNTFY_STR	"+QBLEGATTSNTFY"
#define FC41D_URC_QBLESTAT_STR	"+QBLESTAT"
#define FC41D_URC_QBLEMTU_STR	"+QBLEMTU"
#define FC41D_URC_QBLEINFO_STR	"+QBLEINFO"

typedef struct s_fc41d_at_cmd_task
{
	char* at_cmd;
	uint8_t (*at_cmd_start_task)(uint8_t*);
	uint8_t (*at_cmd_resp_task)(uint8_t*);
}s_FC41D_AT_CMD_TASK;

typedef struct s_mw_fc41d_ble
{
	e_FC41D_AT_CMD_LIST cmd_task_queue[FC41D_AT_CMD_TASK_QUEUE_MAX_LENGTH];
	uint8_t cmd_task_queue_head;
	uint8_t cmd_task_queue_tail;
	e_FC41D_AT_CMD_LIST cmd_in_progress;
	s_FC41D_AT_CMD_TASK cmd_task_list[FC41D_CMD_ALL_LIST_END];

	char cmd_resp_final_buf[FC41D_AT_CMD_FINAL_RESP_SIZE];
	uint16_t cmd_resp_final_len;
	char cmd_resp_raw_data_buf[FC41D_AT_CMD_RAW_DATA_SIZE];
	uint16_t cmd_resp_raw_data_len;
	char cmd_resp_inter_urc_buf[FC41D_AT_CMD_INTER_URC_RESP_SIZE];
	uint16_t cmd_resp_inter_urc_len;

	char cmd_gatt_data_buf[FC41D_AT_CMD_RAW_DATA_SIZE];
	char cmd_gatt_uuid[FC41D_AT_CMD_GATT_UUID_MAX_LENGTH];

	char gatt_uuid_map[FC41D_AT_GATT_MAP_MAX_LENGTH][FC41D_AT_CMD_GATT_UUID_MAX_LENGTH];
	uint16_t gatt_uuid_map_len;

}s_MW_FC41D_BLE;

void EGTN_MW_FC41D_push_ringbuffer(uint8_t comdt);

uint8_t EGTN_MW_FC41D_startup();
uint8_t EGTN_MW_FC41D_ble_peripheral_init();
void EGTN_MW_FC41D_ble_peripheral_loop();

#endif /* EGTN_MW_EGTN_MW_FC41D_H_ */
