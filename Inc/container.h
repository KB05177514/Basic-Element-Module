#ifndef __container_H
#define __container_H

#include<stdint.h>
#include<stdbool.h>

struct container
{
	uint8_t * pbuff;

	uint32_t data_len;

	uint32_t buff_size;
};

bool malloc_container(struct container * pcont, uint32_t len);
void free_container(struct container * pcont);
bool fill_container(struct container * pcont, uint8_t * psrc, uint32_t len);
void clear_container(struct container * pcont);


#endif






