/*
 * evon_lib_u8queue.c
 *
 *  Created on: Apr 13, 2022
 *      Author: EVERON
 */


#include <egtn_lib_u8queue.h>

void EGTN_LIB_U8QUEUE_comFlush(s_EGTN_LIB_QUEUE* s_queue)
{
	//s_queue->action_pointer = RING_BUFFER_MAX;
	s_queue->action_pointer = 0;
	s_queue->save_pointer = 0;
}

uint16_t EGTN_LIB_U8QUEUE_comLen(s_EGTN_LIB_QUEUE* s_queue)
{
	uint16_t i;
	if(s_queue->save_pointer >= (s_queue->action_pointer))
	{
		i = s_queue->save_pointer - s_queue->action_pointer;
	}
	else
	{
		i = s_queue->ring_buffer_size - s_queue->action_pointer + s_queue->save_pointer;
	}

	return i;
}

uint8_t read_ringbuffer(s_EGTN_LIB_QUEUE* s_queue)
{
	uint8_t ret_value = 0;
	//s_queue->action_pointer++;
	if(s_queue->action_pointer != s_queue->save_pointer)
	{
		ret_value = s_queue->ring_buffer[s_queue->action_pointer];
		s_queue->action_pointer++;

		if(s_queue->action_pointer >= s_queue->ring_buffer_size)
		{
			s_queue->action_pointer = 0;
		}
	}
	else
	{
		U8QUEUE_PRINTF("egtn_lib_u8queue__read__ERROR__action_pointer and save_pointer is same\r\n");
	}

	return ret_value;
}

uint8_t EGTN_LIB_U8QUEUE_contain(s_EGTN_LIB_QUEUE* s_queue, uint8_t *data)
{

}

uint8_t EGTN_LIB_U8QUEUE_get_byte(s_EGTN_LIB_QUEUE* s_queue)
{
	return read_ringbuffer(s_queue);
}

uint16_t EGTN_LIB_U8QUEUE_get_word(s_EGTN_LIB_QUEUE* s_queue)
{
	uint16_t wh = 0x0000;
	uint16_t wl = 0x0000;
	uint16_t temp = 0;

	wh = read_ringbuffer(s_queue);
	wl = read_ringbuffer(s_queue);

	temp = ((wh << 8) & 0xFF00) | (wl & 0x00FF);

	return temp;
}

void EGTN_LIB_U8QUEUE_inc_pointer(s_EGTN_LIB_QUEUE* s_queue)
{
	read_ringbuffer(s_queue);
}

void EGTN_LIB_U8QUEUE_push_ring(s_EGTN_LIB_QUEUE* s_queue, uint8_t comdt)
{
#if 0
	if(s_queue->blank_check > 50)	{
		EGTN_LIB_U8QUEUE_comFlush(s_queue);
	}
	s_queue->blank_check = 0;
#endif
#if 0
	if(s_queue->save_pointer != s_queue->action_pointer)
	{
		s_queue->ring_buffer[s_queue->save_pointer] = comdt;
		s_queue->save_pointer++;
		if(s_queue->save_pointer > s_queue->ring_buffer_size){
			s_queue->save_pointer = 0;
		}
	}
#endif

	if((s_queue->save_pointer - s_queue->action_pointer) == -1)
	{
		U8QUEUE_PRINTF("egtn_lib_u8queue__push__WARING__buf soon full\r\n");
	}

	s_queue->ring_buffer[s_queue->save_pointer] = comdt;
	s_queue->save_pointer++;
	if(s_queue->save_pointer >= s_queue->ring_buffer_size)
	{
		s_queue->save_pointer = 0;
	}
}




