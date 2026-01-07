/*
 * evon_lib_u8queue.c
 *
 *  Created on: Apr 13, 2022
 *      Author: EVERON
 */

#ifndef EGTN_LIB_INC_EGTN_LIB_U8QUEUE_H_
#define EGTN_LIB_INC_EGTN_LIB_U8QUEUE_H_


#include "main.h"

//#define RING_BUFFER_MAX 1024
#define RETURN_INTERVAL 0// 250602 TODO most to test 1 --> 0

#define U8QUEUE_USE_PRINTF
#ifdef U8QUEUE_USE_PRINTF
#include <stdio.h>
#define U8QUEUE_PRINTF	printf
#else
#define U8QUEUE_PRINTF(...)
#endif

typedef struct s_evon_lib_queue{
	//uint8_t ring_buffer[RING_BUFFER_MAX + 1];
	uint8_t *ring_buffer;
	uint16_t ring_buffer_size;
	uint16_t save_pointer;
	uint16_t action_pointer;
	uint16_t blank_check;
}s_EGTN_LIB_QUEUE;


void EGTN_LIB_U8QUEUE_push_ring(s_EGTN_LIB_QUEUE* s_queue, uint8_t comdt);
uint16_t EGTN_LIB_U8QUEUE_get_word(s_EGTN_LIB_QUEUE* s_queue);
uint8_t EGTN_LIB_U8QUEUE_get_byte(s_EGTN_LIB_QUEUE* s_queue);
uint16_t EGTN_LIB_U8QUEUE_comLen(s_EGTN_LIB_QUEUE* s_queue);
void EGTN_LIB_U8QUEUE_comFlush(s_EGTN_LIB_QUEUE* s_queue);
void EGTN_LIB_U8QUEUE_inc_pointer(s_EGTN_LIB_QUEUE* s_queue);


#endif /* EGTN_LIB_INC_EGTN_LIB_U8QUEUE_H_ */
