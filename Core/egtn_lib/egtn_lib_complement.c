/*
 * evon_lib_complement.c
 *
 *  Created on: 2023. 2. 13.
 *      Author: MSI
 */


#include <egtn_lib_complement.h>

uint8_t EGTN_LIB_COMPLEMENT_TWO_STM32_32bit(int32_t input, int32_t* output)
{
	uint8_t ret_value = 0;
	uint32_t temp = input;

	if((temp & (0x80000000)) == 0x80000000)
	{
		temp = ~temp;
		temp = temp + 1;

		*output = temp;

		ret_value = 1;
	}

	return ret_value;
}

uint8_t EGTN_LIB_BYTE_TO_HEXASCII(uint8_t input, uint8_t* output)
{
	uint8_t ret_value = 1;
	uint8_t temp = input;
	uint8_t hex_msb;
	uint8_t hex_lsb;

	hex_msb = ((temp >> 4) & 0x0F);
	hex_lsb = (temp & 0x0F);

	if((hex_msb >= 0) && (hex_msb < 10))
	{
		hex_msb = hex_msb + 0x30;
	}
	else if((hex_msb >= 10) && (hex_msb < 16))
	{
		hex_msb = hex_msb - 10;
		hex_msb = hex_msb + 0x41;
	}
	else
	{
		hex_msb = 0x30;
		ret_value = 0;
	}

	if((hex_lsb >= 0) && (hex_lsb < 10))
	{
		hex_lsb = hex_lsb + 0x30;
	}
	else if((hex_lsb >= 10) && (hex_lsb < 16))
	{
		hex_lsb = hex_lsb - 10;
		hex_lsb = hex_lsb + 0x41;
	}
	else
	{
		hex_lsb = 0x30;
		ret_value = 0;
	}

	output[0] = hex_msb;
	output[1] = hex_lsb;

	return ret_value;
}

uint8_t EGTN_LIB_HEXASCII_TO_BYTE(char* input, uint8_t* output)
{
	uint8_t ret_value = 1;
	char ascii_msb = input[0];
	char ascii_lsb = input[1];
	uint8_t hex_msb = 0x00;
	uint8_t hex_lsb = 0x00;
	uint8_t hex_output = 0x00;


	if((ascii_msb >= 0x30) && (ascii_msb <= 0x39))
	{
		hex_msb = ascii_msb - 0x30;
	}
	else if((ascii_msb >= 0x41) && (ascii_msb <= 0x46))
	{
		hex_msb = ascii_msb - 0x41 + 10;
	}
	else
	{
		hex_msb = 0x00;
		ret_value = 0;
	}

	if((ascii_lsb >= 0x30) && (ascii_lsb <= 0x39))
	{
		hex_lsb = ascii_lsb - 0x30;
	}
	else if((ascii_lsb >= 0x41) && (ascii_lsb <= 0x46))
	{
		hex_lsb = ascii_lsb - 0x41 + 10;
	}
	else
	{
		hex_lsb = 0x00;
		ret_value = 0;
	}

	hex_output = (((hex_msb << 4) & 0xF0) | (hex_lsb & 0x0F));
	*output = hex_output;

	return ret_value;
}
