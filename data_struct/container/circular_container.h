#ifndef __circular_container_H
#define __circular_container_H

/*
* float�ͻ�״�����ṹ�嶨��
*/
struct float_circular_container
{
	float * pbuff;

	uint32_t len;	

	uint32_t count;

	uint32_t position;
};

/*
* API����
*/
bool float_circular_container_malloc(struct float_circular_container * pcrc_cont, uint32_t len);
void float_circular_container_free(struct float_circular_container * pcrc_cont);
void float_circular_container_fill(struct float_circular_container * pcrc_cont, float data);
void float_circular_container_clear(struct float_circular_container * pcrc_cont);


#endif
















