/*
 * evon_lib_string.c
 *
 *  Created on: May 11, 2022
 *      Author: EVERON
 */

#include "egtn_lib_string.h"

char* egtn_lib_string_mystrcat(char* dest, const char* src)
{
	while (*dest) dest++;
	//while (*dest++ = *src++);
	while ((*dest++ = *src++) != '\0');
	return --dest;
}

