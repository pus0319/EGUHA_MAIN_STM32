/*
 * evon_lib_debouncecheck.c
 *
 *  Created on: 2022. 5. 16.
 *      Author: EVERON
 */



#include <egtn_lib_debouncecheck.h>

void EGTN_LIB_DEBOUNCECHECK_init(uint8_t* dbuf, uint16_t dbuflength)
{
	int i = 0;
	for(i=0 ; i<dbuflength ; i++)
	{
		dbuf[i] = 0;
	}
}

void EGTN_LIB_DEBOUNCECHECK_push(uint8_t* dbuf, int pdata)
{
	dbuf[0] = pdata;
}

void EGTN_LIB_DEBOUNCECHECK_shift(uint8_t* dbuf, uint16_t dbuflength)
{
	int i = 0;
	for(i=(dbuflength-2) ; i>0 ; i--)
	{
		dbuf[i] = dbuf[i - 1];
	}
}

uint8_t EGTN_LIB_DEBOUNCECHECK_compare(uint8_t* dbuf, uint16_t dbuflength, uint8_t value)
{
	int i = 0;
	for(i=(dbuflength-2) ; i>0 ; i--)
	{
		switch(value)
		{
			case 0 :
				if(dbuf[i] != dbuf[i - 1])
				{
					return 0;
				}
			break;
			default :
				if(dbuf[i] != value)
				{
					return 0;
				}
			break;
		}
	}

	dbuf[dbuflength-1] = dbuf[dbuflength-2];

	return 1;
}



