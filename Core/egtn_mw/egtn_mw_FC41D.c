/*
 * egtn_mw_FC41D.c
 *
 *  Created on: Dec 29, 2025
 *      Author: USER
 */

#include "egtn_mw_FC41D.h"

static uint8_t fc41d_rx_ring_buffer[FC41D_RING_BUFFER_SIZE];
static s_EGTN_LIB_QUEUE fc41d_rx_queue = {fc41d_rx_ring_buffer, FC41D_RING_BUFFER_SIZE, 0, 0, 0};

static gUserDelay gTimeout_fc41d_at_cmd;
static gUserDelay gDelay_fc41d_cmd_delay;
static gUserDelay gDelay_fc41d_poweron;
static gUserDelay gDelay_fc41d_hardware_reset;
static gUserDelay gDelay_fc41d_wakeup;
static gUserDelay gDelay_fc41d_software_reset;

uint8_t fc41d_cmd_delay(uint8_t* value);
uint8_t fc41d_resp_delay(uint8_t* value);
uint8_t fc41d_cmd_reset(uint8_t* value);
uint8_t fc41d_resp_reset(uint8_t* value);
uint8_t fc41d_cmd_get_firmware_version(uint8_t* value);
uint8_t fc41d_resp_get_firmware_version(uint8_t* value);
uint8_t fc41d_cmd_able_echo(uint8_t* value);
uint8_t fc41d_resp_able_echo(uint8_t* value);
uint8_t fc41d_cmd_able_urc(uint8_t* value);
uint8_t fc41d_resp_able_urc(uint8_t* value);
uint8_t fc41d_cmd_enter_low_power_mode(uint8_t* value);
uint8_t fc41d_resp_enter_low_power_mode(uint8_t* value);
uint8_t fc41d_cmd_enter_deep_sleep_mode(uint8_t* value);
uint8_t fc41d_resp_enter_deep_sleep_mode(uint8_t* value);
uint8_t fc41d_cmd_get_mac_addr(uint8_t* value);
uint8_t fc41d_resp_get_mac_addr(uint8_t* value);
uint8_t fc41d_cmd_init_ble(uint8_t* value);
uint8_t fc41d_resp_init_ble(uint8_t* value);
uint8_t fc41d_cmd_query_ble_device_addr(uint8_t* value);
uint8_t fc41d_resp_query_ble_device_addr(uint8_t* value);
uint8_t fc41d_cmd_set_ble_name(uint8_t* value);
uint8_t fc41d_resp_set_ble_name(uint8_t* value);
uint8_t fc41d_cmd_config_ble_advertising_parameter(uint8_t* value);
uint8_t fc41d_resp_config_ble_advertising_parameter(uint8_t* value);
uint8_t fc41d_cmd_set_ble_advertising_data(uint8_t* value);
uint8_t fc41d_resp_set_ble_advertising_data(uint8_t* value);
uint8_t fc41d_cmd_establish_ble_service(uint8_t* value);
uint8_t fc41d_resp_establish_ble_service(uint8_t* value);
uint8_t fc41d_cmd_set_ble_characteristic_uuid(uint8_t* value);
uint8_t fc41d_resp_set_ble_characteristic_uuid(uint8_t* value);
uint8_t fc41d_cmd_start_ble_advertising(uint8_t* value);
uint8_t fc41d_resp_start_ble_advertising(uint8_t* value);
uint8_t fc41d_cmd_stop_ble_advertising(uint8_t* value);
uint8_t fc41d_resp_stop_ble_advertising(uint8_t* value);
uint8_t fc41d_cmd_send_gatt_data(uint8_t* value);
uint8_t fc41d_resp_send_gatt_data(uint8_t* value);
uint8_t fc41d_resp_urc_ble_state_change(uint8_t* value);
uint8_t fc41d_resp_urc_ble_mtu_change(uint8_t* value);
uint8_t fc41d_resp_urc_ble_info(uint8_t* value);

static s_MW_FC41D_BLE m_fc41d_ble =
{
		{FC41D_AT_CMD_NON, },//e_FC41D_AT_CMD_LIST cmd_task_queue[FC41D_AT_CMD_TASK_QUEUE_MAX_LENGTH];
		0,//uint8_t cmd_task_queue_head;
		0,//uint8_t cmd_task_queue_tail;
		FC41D_AT_CMD_NON,//e_FC41D_AT_CMD_LIST cmd_in_progress;
		{					//s_FC41D_AT_CMD_TASK cmd_task_list[FC41D_AT_CMD_LIST_END];
				{NULL, NULL, NULL},
				{NULL, NULL, NULL},
				{NULL, NULL, NULL},
				{NULL, fc41d_cmd_delay, fc41d_resp_delay},
				{FC41D_QRST_STR, fc41d_cmd_reset, fc41d_resp_reset},
				{FC41D_QVERSION_STR, fc41d_cmd_get_firmware_version, fc41d_resp_get_firmware_version},
				{FC41D_QECHO_STR, fc41d_cmd_able_echo, fc41d_resp_able_echo},
				{FC41D_QURCCFG_STR, fc41d_cmd_able_urc, fc41d_resp_able_urc},
				{FC41D_QLOWPOWER_STR, fc41d_cmd_enter_low_power_mode, fc41d_resp_enter_low_power_mode},
				{FC41D_QDEEPSLEEP_STR, fc41d_cmd_enter_deep_sleep_mode, fc41d_resp_enter_deep_sleep_mode},
				{FC41D_QWLMAC_STR, fc41d_cmd_get_mac_addr, fc41d_resp_get_mac_addr},
				{FC41D_QBLEINIT_STR, fc41d_cmd_init_ble, fc41d_resp_init_ble},
				{FC41D_QBLEADDR_STR, fc41d_cmd_query_ble_device_addr, fc41d_resp_query_ble_device_addr},
				{FC41D_QBLENAME_STR, fc41d_cmd_set_ble_name, fc41d_resp_set_ble_name},
				{FC41D_QBLEADVPARAM_STR, fc41d_cmd_config_ble_advertising_parameter, fc41d_resp_config_ble_advertising_parameter},
				{FC41D_QBLEADVDATA_STR, fc41d_cmd_set_ble_advertising_data, fc41d_resp_set_ble_advertising_data},
				{FC41D_QBLEGATTSSRV_STR, fc41d_cmd_establish_ble_service, fc41d_resp_establish_ble_service},
				{FC41D_QBLEGATTSCHAR_STR, fc41d_cmd_set_ble_characteristic_uuid, fc41d_resp_set_ble_characteristic_uuid},
				{FC41D_QBLEADVSTART_STR, fc41d_cmd_start_ble_advertising, fc41d_resp_start_ble_advertising},
				{FC41D_QBLEADVSTOP_STR, fc41d_cmd_stop_ble_advertising, fc41d_resp_stop_ble_advertising},
				{FC41D_QBLEGATTSNTFY_STR, fc41d_cmd_send_gatt_data, fc41d_resp_send_gatt_data},
				{NULL, NULL, NULL},
				{FC41D_URC_QBLESTAT_STR, NULL, fc41d_resp_urc_ble_state_change},
				{FC41D_URC_QBLEMTU_STR, NULL, fc41d_resp_urc_ble_mtu_change},
				{FC41D_URC_QBLEINFO_STR, NULL, fc41d_resp_urc_ble_info},
				{NULL, NULL, NULL},
		},
		{'\0', },//char cmd_resp_final_buf[FC41D_AT_CMD_FINAL_RESP_SIZE];
		0,//uint16_t cmd_resp_final_len;
		{'\0', },//char cmd_resp_raw_data_buf[FC41D_AT_CMD_RAW_DATA_SIZE];
		0,//uint16_t cmd_resp_raw_data_len;
		{'\0', },//char cmd_resp_inter_urc_buf[FC41D_AT_CMD_RESP_PIPELINE_MAX][FC41D_AT_CMD_INTER_URC_RESP_SIZE];
		0,
		{'\0', },//char cmd_gatt_data_buf[FC41D_AT_CMD_RAW_DATA_SIZE];
		{'\0', },//char cmd_gatt_uuid[FC41D_AT_CMD_GATT_UUID_MAX_LENGTH];
		{
			{'\0', },	//uint16_t gatt_uuid_map[FC41D_AT_GATT_MAP_MAX_LENGTH][FC41D_AT_CMD_GATT_UUID_MAX_LENGTH];
			{'\0', },
			{'\0', },
			{'\0', },
			{'\0', },
			{'\0', },
			{'\0', },
			{'\0', },
			{'\0', },
			{'\0', },
		},
		0//uint16_t gatt_uuid_map_len;
};

void fc41d_send_data(uint8_t* data, uint16_t len)
{
	EGTN_MW_UART_tx01(data, len);
}

uint8_t fc41d_cmd_delay(uint8_t* value)
{
	uint8_t ret = 1;

	EGTN_LIB_USERDELAY_start(&gDelay_fc41d_cmd_delay, DELAY_RENEW_OFF);

	return ret;
}
uint8_t fc41d_resp_delay(uint8_t* value)
{
	uint8_t ret = 2;

	//TODO :
	if(EGTN_LIB_USERDELAY_isfired(&gDelay_fc41d_cmd_delay))
	{
		EGTN_LIB_USERDELAY_stop(&gDelay_fc41d_cmd_delay);

		ret = 1;
	}

	return ret;
}

uint8_t fc41d_cmd_reset(uint8_t* value)
{
	uint8_t ret = 1;

	char temp[30];

	memset(temp,'\0',30);
	sprintf(temp,"AT+QRST\r");

	fc41d_send_data((uint8_t *)temp,strlen(temp));
	printf("FC41D_send : %s \r\n",temp);

	return ret;
}
uint8_t fc41d_resp_reset(uint8_t* value)
{
	uint8_t ret = 2;

	//TODO :
	if(FC41D_AT_CMD_IS_OK == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 1;

	}
	else if(FC41D_AT_CMD_IS_ERROR == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 0;
	}

	return ret;
}
uint8_t fc41d_cmd_get_firmware_version(uint8_t* value)
{
	uint8_t ret = 1;

	char temp[30];

	memset(temp,'\0',30);
	sprintf(temp,"AT+QVERSION\r");

	fc41d_send_data((uint8_t *)temp,strlen(temp));
	printf("FC41D_send : %s \r\n",temp);

	return ret;
}
uint8_t fc41d_resp_get_firmware_version(uint8_t* value)
{
	uint8_t ret = 2;
	char * inter;

	if(FC41D_AT_CMD_IS_OK == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		inter = strstr((char *)m_fc41d_ble.cmd_resp_inter_urc_buf,FC41D_QVERSION_STR);

		if(NULL != inter)
		{
			//TODO : save ble module version

			printf("fc41d_fwvr : %s",inter);
			ret = 1;
		}
	}
	else if(FC41D_AT_CMD_IS_ERROR == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 0;
	}

	return ret;
}
uint8_t fc41d_cmd_able_echo(uint8_t* value)
{
	uint8_t ret = 1;

	return ret;
}
uint8_t fc41d_resp_able_echo(uint8_t* value)
{
	uint8_t ret = 2;

	//TODO :

	if(0)
	{
		ret = 1;
	}

	return ret;
}
uint8_t fc41d_cmd_able_urc(uint8_t* value)
{
	uint8_t ret = 1;

	char temp[30];

	memset(temp,'\0',30);
	sprintf(temp,"AT+QURCCFG=1\r");

	fc41d_send_data((uint8_t *)temp,strlen(temp));
	printf("FC41D_send : %s \r\n",temp);

	return ret;
}
uint8_t fc41d_resp_able_urc(uint8_t* value)
{
	uint8_t ret = 2;

	if(FC41D_AT_CMD_IS_OK == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 1;

	}
	else if(FC41D_AT_CMD_IS_ERROR == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 0;
	}

	return ret;
}
uint8_t fc41d_cmd_enter_low_power_mode(uint8_t* value)
{
	uint8_t ret = 1;

	return ret;
}
uint8_t fc41d_resp_enter_low_power_mode(uint8_t* value)
{
	uint8_t ret = 2;

	//TODO :

	if(0)
	{
		ret = 1;
	}

	return ret;
}
uint8_t fc41d_cmd_enter_deep_sleep_mode(uint8_t* value)
{
	uint8_t ret = 1;

	return ret;
}
uint8_t fc41d_resp_enter_deep_sleep_mode(uint8_t* value)
{
	uint8_t ret = 2;

	//TODO :

	if(0)
	{
		ret = 1;
	}

	return ret;
}
uint8_t fc41d_cmd_get_mac_addr(uint8_t* value)
{
	uint8_t ret = 1;

	return ret;
}
uint8_t fc41d_resp_get_mac_addr(uint8_t* value)
{
	uint8_t ret = 2;

	//TODO :

	if(0)
	{
		ret = 1;
	}

	return ret;
}
uint8_t fc41d_cmd_init_ble(uint8_t* value)
{
	uint8_t ret = 1;

	char temp[30];

	memset(temp,'\0',30);
	sprintf(temp,"AT+QBLEINIT=2\r");

	fc41d_send_data((uint8_t *)temp,strlen(temp));
	printf("FC41D_send : %s \r\n",temp);

	return ret;
}
uint8_t fc41d_resp_init_ble(uint8_t* value)
{
	uint8_t ret = 2;

	if(FC41D_AT_CMD_IS_OK == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 1;
	}
	else if(FC41D_AT_CMD_IS_ERROR == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 0;
	}

	return ret;
}
uint8_t fc41d_cmd_query_ble_device_addr(uint8_t* value)
{
	uint8_t ret = 1;

	char temp[30];

	memset(temp,'\0',30);
	sprintf(temp,"AT+QBLEADDR?\r\n");

	fc41d_send_data((uint8_t *)temp,strlen(temp));
	printf("FC41D_send : %s \r\n",temp);

	return ret;
}
uint8_t fc41d_resp_query_ble_device_addr(uint8_t* value)
{
	uint8_t ret = 2;
	char *inter;

	if(FC41D_AT_CMD_IS_OK == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		inter = strstr((char *)m_fc41d_ble.cmd_resp_inter_urc_buf,FC41D_QBLEADDR_STR);

		if(NULL != inter)
		{
			//TODO : save ble module version

			printf("fc41d_resp : %s",inter);
			ret = 1;
		}
	}
	else if(FC41D_AT_CMD_IS_ERROR == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 0;
	}

	return ret;
}
uint8_t fc41d_cmd_set_ble_name(uint8_t* value)
{
	uint8_t ret = 1;

	char temp[30];

	memset(temp,'\0',30);
	sprintf(temp,"AT+QBLENAME=EGUHA48\r");

	fc41d_send_data((uint8_t *)temp,strlen(temp));
	printf("FC41D_send : %s \r\n",temp);

	return ret;
}
uint8_t fc41d_resp_set_ble_name(uint8_t* value)
{
	uint8_t ret = 2;

	if(FC41D_AT_CMD_IS_OK == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 1;

	}
	else if(FC41D_AT_CMD_IS_ERROR == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 0;
	}

	return ret;
}
uint8_t fc41d_cmd_config_ble_advertising_parameter(uint8_t* value)
{
	uint8_t ret = 1;

	char temp[30];

	memset(temp,'\0',30);
	sprintf(temp,"AT+QBLEADVPARAM=150,150\r");

	fc41d_send_data((uint8_t *)temp,strlen(temp));
	printf("FC41D_send : %s \r\n",temp);

	return ret;
}
uint8_t fc41d_resp_config_ble_advertising_parameter(uint8_t* value)
{
	uint8_t ret = 2;

	if(FC41D_AT_CMD_IS_OK == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 1;

	}
	else if(FC41D_AT_CMD_IS_ERROR == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 0;
	}

	return ret;
}
uint8_t fc41d_cmd_set_ble_advertising_data(uint8_t* value)
{
	uint8_t ret = 1;

	return ret;
}
uint8_t fc41d_resp_set_ble_advertising_data(uint8_t* value)
{
	uint8_t ret = 2;

	//TODO :

	if(0)
	{
		ret = 1;
	}

	return ret;
}
uint8_t fc41d_cmd_establish_ble_service(uint8_t* value)
{
	uint8_t ret = 1;

	char temp[30];

	memset(temp,'\0',30);
	sprintf(temp,"AT+QBLEGATTSSRV=fff1\r");

	fc41d_send_data((uint8_t *)temp,strlen(temp));
	printf("FC41D_send : %s \r\n",temp);

	return ret;
}
uint8_t fc41d_resp_establish_ble_service(uint8_t* value)
{
	uint8_t ret = 2;

	if(FC41D_AT_CMD_IS_OK == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 1;

	}
	else if(FC41D_AT_CMD_IS_ERROR == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 0;
	}

	return ret;
}
uint8_t fc41d_cmd_set_ble_characteristic_uuid(uint8_t* value)
{
	uint8_t ret = 1;

	char temp[100];

	memset(temp,'\0',100);
	sprintf(temp,"AT+QBLEGATTSCHAR=%s\r",&(m_fc41d_ble.gatt_uuid_map[*value][0]));

	fc41d_send_data((uint8_t *)temp,strlen(temp));
	printf("FC41D_send : %s \r\n",temp);

	return ret;
}
uint8_t fc41d_resp_set_ble_characteristic_uuid(uint8_t* value)
{
	uint8_t ret = 2;

	if(FC41D_AT_CMD_IS_OK == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 1;

	}
	else if(FC41D_AT_CMD_IS_ERROR == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 0;
	}

	return ret;
}
uint8_t fc41d_cmd_start_ble_advertising(uint8_t* value)
{
	uint8_t ret = 1;

	char temp[30];

	memset(temp,'\0',30);
	sprintf(temp,"AT+QBLEADVSTART\r");

	fc41d_send_data((uint8_t *)temp,strlen(temp));
	printf("FC41D_send : %s \r\n",temp);

	return ret;
}
uint8_t fc41d_resp_start_ble_advertising(uint8_t* value)
{
	uint8_t ret = 2;

	if(FC41D_AT_CMD_IS_OK == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 1;

	}
	else if(FC41D_AT_CMD_IS_ERROR == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 0;
	}

	return ret;
}
uint8_t fc41d_cmd_stop_ble_advertising(uint8_t* value)
{
	uint8_t ret = 1;

	return ret;
}
uint8_t fc41d_resp_stop_ble_advertising(uint8_t* value)
{
	uint8_t ret = 2;

	//TODO :

	if(0)
	{
		ret = 1;
	}

	return ret;
}
uint8_t fc41d_cmd_send_gatt_data(uint8_t* value)
{
	uint8_t ret = 1;
	char temp[FC41D_AT_CMD_RAW_DATA_SIZE+100];
	int data_len = strlen(m_fc41d_ble.cmd_gatt_data_buf);
	int uuid_len = strlen(m_fc41d_ble.cmd_gatt_uuid);

	if((0 >= data_len) && (FC41D_AT_CMD_RAW_DATA_SIZE < data_len))
	{
		//printf("data_len is 0\r\n");
		return 0;
	}
	if((0 >= uuid_len) && (FC41D_AT_CMD_GATT_UUID_MAX_LENGTH < data_len))
	{
		//printf("uuid_len is 0\r\n");
		return 0;
	}

	memset(temp,'\0',(FC41D_AT_CMD_RAW_DATA_SIZE+100));
	sprintf(temp,"AT+QBLEGATTSNTFY=%s,%s\r", m_fc41d_ble.cmd_gatt_uuid, m_fc41d_ble.cmd_gatt_data_buf);

	fc41d_send_data((uint8_t *)temp,strlen(temp));
	printf("FC41D_send : %s \r\n",temp);

	return ret;
}
uint8_t fc41d_resp_send_gatt_data(uint8_t* value)
{
	uint8_t ret = 2;

	memset(m_fc41d_ble.cmd_gatt_uuid,'\0',FC41D_AT_CMD_GATT_UUID_MAX_LENGTH);
	memset(m_fc41d_ble.cmd_gatt_data_buf,'\0',FC41D_AT_CMD_RAW_DATA_SIZE);

	if(FC41D_AT_CMD_IS_OK == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 1;

	}
	else if(FC41D_AT_CMD_IS_ERROR == m_fc41d_ble.cmd_resp_final_buf[0])
	{
		ret = 0;
	}

	return ret;
}

uint8_t fc41d_resp_urc_ble_state_change(uint8_t* value)
{
	uint8_t ret = 2;
	char *inter;

	inter = strstr((char *)m_fc41d_ble.cmd_resp_inter_urc_buf,FC41D_URC_QBLESTAT_STR);

	if(NULL != inter)
	{
		//TODO : save ble state

		printf("fc41d_URC_BLE STATE : %s",inter);
		ret = 1;
	}

	return ret;
}
uint8_t fc41d_resp_urc_ble_mtu_change(uint8_t* value)
{
	uint8_t ret = 2;
	char *inter;

	inter = strstr((char *)m_fc41d_ble.cmd_resp_inter_urc_buf,FC41D_URC_QBLEMTU_STR);

	if(NULL != inter)
	{
		//TODO : save ble state

		printf("fc41d_URC_BLE MTU : %s",inter);
		ret = 1;
	}

	return ret;
}
uint8_t fc41d_resp_urc_ble_info(uint8_t* value)
{
	uint8_t ret = 2;
	char *inter;

	inter = strstr((char *)m_fc41d_ble.cmd_resp_inter_urc_buf,FC41D_URC_QBLEINFO_STR);

	if(NULL != inter)
	{
		//TODO : save ble state

		printf("fc41d_URC_BLE INFO : %s",inter);
		ret = 1;
	}

	return ret;
}

void EGTN_MW_FC41D_push_ringbuffer(uint8_t comdt)
{
	EGTN_LIB_U8QUEUE_push_ring(&fc41d_rx_queue, comdt);
}

void EGTN_MW_FC41D_set_cen_high()
{
	EGTN_MW_GPIO_set_gpo(BLE_RST, GPIO_PIN_SET);
}
void EGTN_MW_FC41D_set_cen_low()
{
	EGTN_MW_GPIO_set_gpo(BLE_RST, GPIO_PIN_RESET);
}
void EGTN_MW_FC41D_set_wakeup_in_high()
{
	EGTN_MW_GPIO_set_gpo(BLE_WAKEUP_IN, GPIO_PIN_SET);
}
void EGTN_MW_FC41D_set_wakeup_in_low()
{
	EGTN_MW_GPIO_set_gpo(BLE_WAKEUP_IN, GPIO_PIN_RESET);
}
uint8_t EGTN_MW_FC41D_get_wakeup_out()
{
	uint8_t ret = 0;

	ret = EGTN_MW_GPIO_get_gpi(BLE_WAKEUP_OUT);

	return ret;
}
uint8_t EGTN_MW_FC41D_get_net_status()
{
	uint8_t ret = 0;

	ret = EGTN_MW_GPIO_get_gpi(BLE_NET_STATUS);

	return ret;
}

uint8_t EGTN_MW_FC41D_ble_peripheral_send_data()
{
	uint8_t ret = 0;

	return ret;
}
uint8_t EGTN_MW_FC41D_ble_peripheral_recive_data()
{
	uint8_t ret = 0;

	return ret;
}

uint8_t EGTN_MW_FC41D_cmd_task_queue_is_contain()
{
	uint8_t ret = 0;

	if(m_fc41d_ble.cmd_task_queue_head >= m_fc41d_ble.cmd_task_queue_tail)
	{
		ret = m_fc41d_ble.cmd_task_queue_head - m_fc41d_ble.cmd_task_queue_tail;
	}
	else
	{
		ret = FC41D_AT_CMD_TASK_QUEUE_MAX_LENGTH - m_fc41d_ble.cmd_task_queue_tail + m_fc41d_ble.cmd_task_queue_head;
	}

	return ret;
}

void EGTN_MW_FC41D_push_cmd_task_queue(e_FC41D_AT_CMD_LIST cmd)
{
	if(FC41D_CMD_OK == cmd)	return;
	if(FC41D_CMD_ERROR == cmd)	return;
	if(FC41D_AT_LIST_END == cmd)	return;
	if(FC41D_URC_LIST_END == cmd)	return;
	if(FC41D_CMD_ALL_LIST_END == cmd)	return;

	m_fc41d_ble.cmd_task_queue[m_fc41d_ble.cmd_task_queue_head++] = cmd;
	if(FC41D_AT_CMD_TASK_QUEUE_MAX_LENGTH <= m_fc41d_ble.cmd_task_queue_head)	m_fc41d_ble.cmd_task_queue_head = 0;
}

void fc41d_rx_framesearch()
{
	uint8_t rxdata = 0x00;
	uint16_t rxlen = 0;
	uint16_t rxdata_current_pointer = 0;
	uint8_t rxbuf[FC41D_RING_BUFFER_SIZE];
	uint16_t rxbuf_len = 0;
	char *cmd_end;
	e_FC41D_AT_CMD_RESP_TYPE is_cmd_resp_type = FC41D_AT_RESP_NON;
	int i = 0;

	uint8_t is_cmd_resp_final_filled = 0;
	uint8_t is_cmd_resp_raw_data_filled = 0;
	uint8_t is_cmd_resp_inter_urc_filled = 0;

	rxlen = EGTN_LIB_U8QUEUE_comLen(&fc41d_rx_queue);

#if 0
	if(0 < rxlen)
	{
		//printf("fc41d_rx : ");
		for(i=0;i<rxlen;i++)
		{
			rxdata = EGTN_LIB_U8QUEUE_get_byte(&fc41d_rx_queue);
			printf("%c",rxdata);
		}
		printf("\n");
	}
#endif

	if(2 > rxlen)	return;

	rxdata_current_pointer = fc41d_rx_queue.action_pointer;

	for(i=0;i<rxlen;i++)
	{
		rxbuf[rxbuf_len++] = EGTN_LIB_U8QUEUE_get_byte(&fc41d_rx_queue);
	}
	//rxbuf[rxbuf_len] = '\0';

#if 0
	printf("rxlen:%d\r\n",rxlen);
	for(i=0;i<rxbuf_len;i++)
	{
		printf("0x%02x\r\n",rxbuf[i]);
	}
	printf("\n");
#endif


	fc41d_rx_queue.action_pointer = rxdata_current_pointer;

	//cmd_end = strstr((char *)rxbuf,FC41D_AT_CMD_IS_END_STR);
	cmd_end = memchr(rxbuf,FC41D_AT_CMD_IS_END_CHR,FC41D_RING_BUFFER_SIZE);

	if(NULL == cmd_end)
	{
		//printf("fs1\r\n");
		return;
	}

	if(0 != m_fc41d_ble.cmd_resp_final_len)
	{
		is_cmd_resp_final_filled = 1;
	}
	if(0 != m_fc41d_ble.cmd_resp_raw_data_len)
	{
		is_cmd_resp_raw_data_filled = 1;
	}
	if(0 != m_fc41d_ble.cmd_resp_inter_urc_len)
	{
		is_cmd_resp_inter_urc_filled = 1;
	}

	//printf("FC41D_Framesearch\r\n");
	//printf("S: %s\r\n",rxbuf);

	for(i=0;i<rxlen;i++)
	{
		rxdata_current_pointer = fc41d_rx_queue.action_pointer;

		rxdata = EGTN_LIB_U8QUEUE_get_byte(&fc41d_rx_queue);
		//printf("%c",rxdata);

		if(FC41D_AT_RESP_NON == is_cmd_resp_type)
		{
			switch(rxdata)
			{
				case FC41D_AT_CMD_IS_INTER_URC :
					if(is_cmd_resp_inter_urc_filled)
					{
						printf("FC41D_cmd_resp_inter_urc_is_filled.wait!\r\n");
						fc41d_rx_queue.action_pointer = rxdata_current_pointer;
						return;
					}
					is_cmd_resp_type = FC41D_AT_RESP_INTER_URC;
				break;
				case FC41D_AT_CMD_IS_OK :
				case FC41D_AT_CMD_IS_ERROR :
					if(is_cmd_resp_final_filled)
					{
						printf("FC41D_cmd_resp_final_is_filled.wait!\r\n");
						fc41d_rx_queue.action_pointer = rxdata_current_pointer;
						return;
					}
					is_cmd_resp_type = FC41D_AT_RESP_FINAL;
				break;
				case FC41D_AT_CMD_IS_APP_DATA :
					if(is_cmd_resp_raw_data_filled)
					{
						printf("FC41D_cmd_resp_raw_data_is_filled.wait!\r\n");
						fc41d_rx_queue.action_pointer = rxdata_current_pointer;
						return;
					}
					is_cmd_resp_type = FC41D_AT_RESP_RAW_DATA;
				break;
				default :

				break;
			}
		}

		if(FC41D_AT_RESP_FINAL == is_cmd_resp_type)
		{
			m_fc41d_ble.cmd_resp_final_buf[m_fc41d_ble.cmd_resp_final_len++] = rxdata;
		}
		else if(FC41D_AT_RESP_INTER_URC == is_cmd_resp_type)
		{
			m_fc41d_ble.cmd_resp_inter_urc_buf[m_fc41d_ble.cmd_resp_inter_urc_len++] = rxdata;
		}
		else if(FC41D_AT_RESP_RAW_DATA == is_cmd_resp_type)
		{
			m_fc41d_ble.cmd_resp_raw_data_buf[m_fc41d_ble.cmd_resp_raw_data_len++] = rxdata;
		}

		if((FC41D_AT_RESP_NON != is_cmd_resp_type) & (FC41D_AT_CMD_IS_END_CHR == rxdata))
		{
			//printf("FC41D_Framesearch_OK\r\n");

			is_cmd_resp_type = FC41D_AT_RESP_NON;

			if(FC41D_AT_RESP_FINAL == is_cmd_resp_type)
			{
				m_fc41d_ble.cmd_resp_final_buf[m_fc41d_ble.cmd_resp_final_len] = '\0';
			}
			else if(FC41D_AT_RESP_INTER_URC == is_cmd_resp_type)
			{
				m_fc41d_ble.cmd_resp_inter_urc_buf[m_fc41d_ble.cmd_resp_inter_urc_len] = '\0';
			}
			else if(FC41D_AT_RESP_RAW_DATA == is_cmd_resp_type)
			{
				m_fc41d_ble.cmd_resp_raw_data_buf[m_fc41d_ble.cmd_resp_raw_data_len] = '\0';
			}
			return;
		}
	}

	//printf("FC41D_Framesearch_NOT\r\n");
}

uint8_t EGTN_MW_FC41D_startup()
{
	uint8_t ret = 0;

	memset(m_fc41d_ble.cmd_task_queue,FC41D_AT_CMD_NON,FC41D_AT_CMD_TASK_QUEUE_MAX_LENGTH);
	m_fc41d_ble.cmd_task_queue_head = 0;
	m_fc41d_ble.cmd_task_queue_tail = 0;

	memset(m_fc41d_ble.cmd_gatt_data_buf,'\0',FC41D_AT_CMD_RAW_DATA_SIZE);
	memset(m_fc41d_ble.cmd_gatt_uuid,'\0',FC41D_AT_CMD_GATT_UUID_MAX_LENGTH);

#if(1 == (_TEST_GATT_CHARACTERISITC_UUID_MAP_))
	strcpy(&(m_fc41d_ble.gatt_uuid_map[0][0]), "fff2");
	strcpy(&(m_fc41d_ble.gatt_uuid_map[1][0]), "fff3");
	m_fc41d_ble.gatt_uuid_map_len = 2;
#endif

	EGTN_MW_FC41D_set_cen_low();
	EGTN_MW_FC41D_set_wakeup_in_low();

	EGTN_LIB_USERDELAY_set(&gDelay_fc41d_poweron, 50);
	EGTN_LIB_USERDELAY_set(&gDelay_fc41d_hardware_reset, 200);
	EGTN_LIB_USERDELAY_set(&gDelay_fc41d_wakeup, 3000);
	EGTN_LIB_USERDELAY_set(&gDelay_fc41d_software_reset, 3000);
	EGTN_LIB_USERDELAY_set(&gTimeout_fc41d_at_cmd, 3000);
	EGTN_LIB_USERDELAY_set(&gDelay_fc41d_cmd_delay, 2500);

	return ret;
}

uint8_t EGTN_MW_FC41D_ble_peripheral_init_demo()
{
	uint8_t ret = 0;
	static uint8_t step = 0;

	switch(step)
	{
		case 0 :	// wait power on
			EGTN_LIB_USERDELAY_start(&gDelay_fc41d_poweron, DELAY_RENEW_OFF);
			if(EGTN_LIB_USERDELAY_isfired(&gDelay_fc41d_poweron))
			{
				EGTN_LIB_USERDELAY_stop(&gDelay_fc41d_poweron);
				step = 1;
			}
		break;
		case 1 :	// hardware reset
			if(EGTN_LIB_USERDELAY_start(&gDelay_fc41d_hardware_reset, DELAY_RENEW_OFF))
			{
				EGTN_MW_FC41D_set_cen_high();
			}
			if(EGTN_LIB_USERDELAY_isfired(&gDelay_fc41d_hardware_reset))
			{
				EGTN_LIB_USERDELAY_stop(&gDelay_fc41d_hardware_reset);
				EGTN_MW_FC41D_set_cen_low();
				step = 2;
			}
		break;
		case 2 :	// wakeup (rising edge)
			if(EGTN_LIB_USERDELAY_start(&gDelay_fc41d_wakeup, DELAY_RENEW_OFF))
			{
				EGTN_MW_FC41D_set_wakeup_in_high();
			}
			if(EGTN_LIB_USERDELAY_isfired(&gDelay_fc41d_wakeup))
			{
				EGTN_LIB_USERDELAY_stop(&gDelay_fc41d_wakeup);
				step = 3;
			}
		break;
		case 3 :	// at cmd_TEST
			EGTN_MW_FC41D_push_cmd_task_queue(FC41D_AT_QRST);
			EGTN_MW_FC41D_push_cmd_task_queue(FC41D_CMD_DELAY);
			EGTN_MW_FC41D_push_cmd_task_queue(FC41D_AT_QVERSION);
			EGTN_MW_FC41D_push_cmd_task_queue(FC41D_AT_QURCCFG);
			EGTN_MW_FC41D_push_cmd_task_queue(FC41D_AT_QBLEINIT);
			EGTN_MW_FC41D_push_cmd_task_queue(FC41D_AT_QBLENAME);
			//EGTN_MW_FC41D_push_cmd_task_queue(FC41D_AT_QBLEADDR);
			EGTN_MW_FC41D_push_cmd_task_queue(FC41D_AT_QBLEGATTSSRV);
			EGTN_MW_FC41D_push_cmd_task_queue(FC41D_AT_QBLEGATTSCHAR);
			EGTN_MW_FC41D_push_cmd_task_queue(FC41D_AT_QBLEADVPARAM);
			EGTN_MW_FC41D_push_cmd_task_queue(FC41D_AT_QBLEADVSTART);
			step = 4;
		break;
		case 4 :

		break;
		default :

		break;
	}

	return ret;
}

void EGTN_MW_FC41D_ble_peripheral_loop()
{
	int i = 0;
	uint8_t is_cmd_ok = 0;
	static uint8_t blegattschar_step = 0;

	fc41d_rx_framesearch();

	if((0 != EGTN_MW_FC41D_cmd_task_queue_is_contain()) && (FC41D_AT_CMD_NON == m_fc41d_ble.cmd_in_progress))
	{
		m_fc41d_ble.cmd_in_progress = m_fc41d_ble.cmd_task_queue[m_fc41d_ble.cmd_task_queue_tail++];
		if(FC41D_AT_CMD_TASK_QUEUE_MAX_LENGTH <= m_fc41d_ble.cmd_task_queue_tail)	m_fc41d_ble.cmd_task_queue_tail = 0;
	}

	if(FC41D_AT_CMD_NON != m_fc41d_ble.cmd_in_progress)// is at cmd
	{
		if(EGTN_LIB_USERDELAY_start(&gTimeout_fc41d_at_cmd, DELAY_RENEW_OFF))
		{
			if(FC41D_AT_QBLEGATTSCHAR == m_fc41d_ble.cmd_in_progress)
			{
				if(1 == (m_fc41d_ble.cmd_task_list[m_fc41d_ble.cmd_in_progress].at_cmd_start_task)(&blegattschar_step))
				{
					blegattschar_step++;
				}
				else
				{
					//TODO : FC41D_AT_QBLEGATTSCHAR empty send data, uuid buf
				}

			}
			else
			{
				(m_fc41d_ble.cmd_task_list[m_fc41d_ble.cmd_in_progress].at_cmd_start_task)(NULL);
			}
		}

		if(EGTN_LIB_USERDELAY_isfired(&gTimeout_fc41d_at_cmd))
		{
			EGTN_LIB_USERDELAY_stop(&gTimeout_fc41d_at_cmd);
			//TODO : ERROR or repit...
		}
		else
		{
			if(1 == (m_fc41d_ble.cmd_task_list[m_fc41d_ble.cmd_in_progress].at_cmd_resp_task)(NULL))
			{
				EGTN_LIB_USERDELAY_stop(&gTimeout_fc41d_at_cmd);

				printf("fcloop:%dok\r\n",m_fc41d_ble.cmd_in_progress);

				if(FC41D_AT_QBLEGATTSCHAR == m_fc41d_ble.cmd_in_progress)
				{
					if(m_fc41d_ble.gatt_uuid_map_len <= blegattschar_step)
					{
						blegattschar_step = 0;
						is_cmd_ok = 1;
					}
				}
				else
				{
					is_cmd_ok = 1;
				}

				m_fc41d_ble.cmd_resp_inter_urc_len = 0;
				memset(m_fc41d_ble.cmd_resp_inter_urc_buf,0x00,FC41D_AT_CMD_INTER_URC_RESP_SIZE);
				m_fc41d_ble.cmd_resp_final_len = 0;
				memset(m_fc41d_ble.cmd_resp_final_buf,0x00,FC41D_AT_CMD_FINAL_RESP_SIZE);

				if(1 == is_cmd_ok)
				{
					m_fc41d_ble.cmd_in_progress = FC41D_CMD_OK;
				}
			}
		}

		if(FC41D_CMD_OK == m_fc41d_ble.cmd_in_progress)
		{
			m_fc41d_ble.cmd_in_progress = FC41D_AT_CMD_NON;	// Next cmd
		}
		else if(FC41D_CMD_ERROR == m_fc41d_ble.cmd_in_progress)
		{
			//TODO : casting FC41d CMD ERROR
		}
	}
#if 1
	if(0 < m_fc41d_ble.cmd_resp_inter_urc_len)//is URC
	{
		for(i=(FC41D_AT_LIST_END+1);i<FC41D_URC_LIST_END;i++)
		{
			if(1 == (m_fc41d_ble.cmd_task_list[i].at_cmd_resp_task)(NULL))
			{
				m_fc41d_ble.cmd_resp_inter_urc_len = 0;
				memset(m_fc41d_ble.cmd_resp_inter_urc_buf,0x00,FC41D_AT_CMD_INTER_URC_RESP_SIZE);
			}
		}
	}
#endif

	if(0 < m_fc41d_ble.cmd_resp_raw_data_len)//is Row Data
	{

		printf("FC41D_RawData:%s\r\n",m_fc41d_ble.cmd_resp_raw_data_buf);

		//TODO : FC41D --> BLE _ send GATT_parser
		if(0)
		{

		}
		//TODO : Send Gatt Data example!
		if(0)
		{

		}

#if((__TEST_CHARGING_DEMO__) == 1)
		if(0 == strcmp(m_fc41d_ble.cmd_resp_raw_data_buf,"#START\r\n"))
		{
			EGTN_APP_CHRG_set_start_charging();
		}
		if(0 == strcmp(m_fc41d_ble.cmd_resp_raw_data_buf,"#STOP\r\n"))
		{
			EGTN_APP_CHRG_set_finish_charging();
		}
		if(0 == strcmp(m_fc41d_ble.cmd_resp_raw_data_buf,"#PAUSE\r\n"))
		{
			EGTN_APP_CHRG_set_pause_charging();
		}

		strcpy(m_fc41d_ble.cmd_gatt_data_buf,m_fc41d_ble.cmd_resp_raw_data_buf);
		strcpy(m_fc41d_ble.cmd_gatt_uuid,"fff3");

		printf("cmd_gatt_uuid : %s\r\n",m_fc41d_ble.cmd_gatt_uuid);
		printf("cmd_gatt_data : %s\r\n",m_fc41d_ble.cmd_gatt_data_buf);

		EGTN_MW_FC41D_push_cmd_task_queue(FC41D_AT_QBLEGATTSNTFY);
#endif

		memset(m_fc41d_ble.cmd_resp_raw_data_buf,'\0',FC41D_AT_CMD_RAW_DATA_SIZE);
		m_fc41d_ble.cmd_resp_raw_data_len = 0;
	}
}
