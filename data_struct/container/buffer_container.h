#ifndef __buffer_container_H
#define __buffer_container_H

#include<stdint.h>
#include<stdbool.h>

/*buffer_container struct define*/
struct buffer_container
{
	uint8_t * pbuff;

	uint32_t data_len;

	uint32_t buff_size;
};

/*API declaration*/
bool buffer_container_malloc(struct buffer_container * pcont, uint32_t len);
void buffer_container_free(struct buffer_container * pcont);
bool buffer_container_fill(struct buffer_container * pcont, uint8_t * psrc, uint32_t len);
void buffer_container_clear(struct buffer_container * pcont);

#endif






