#include<stdint.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stm32l0xx_hal.h>
#include "usart.h"
#include "container.h"

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
int32_t table_get_valid_element_count(void * pelement, uint8_t size)
{
    /*数据尺寸最大32字节*/
    if(size > 32)
    {
        /*参数错误*/
        return -1;
    }
    
    uint32_t cnti = 0;
    int32_t number = 0;
    uint8_t * pbuff = malloc(size);
    
    memcpy(pbuff, pelement, size);
    
    if(pbuff == NULL)
    {
        /*空间分配失败*/
        return -2;
    }
    
    for(; cnti < size*8; cnti++)
    {
        if(pbuff[cnti/8] & (0x01 << (cnti % 8)))
        {
            number++;
        }
    }
    
    free(pbuff);
    
    return number;
}

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
void print_iwdg_reg(void)
{
	struct container log_buff;
	uint8_t tmp[32] = {0};
	
	malloc_container(&log_buff, 48);

	sprintf((char *)tmp, "IWDG->PR=0x%08X.\n", IWDG->PR);
	fill_container(&log_buff, tmp, strlen((char *)tmp));

	memset(tmp, 0x00, sizeof(tmp));
	sprintf((char *)tmp, "IWDG->RLR=0x%08X.\n", IWDG->RLR);
	fill_container(&log_buff, tmp, strlen((char *)tmp));

	HAL_UART_Transmit(&huart1, log_buff.pbuff, log_buff.data_len, 100);

	free_container(&log_buff);
}

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
void print_sys_boot_reg(void)
{
	struct container log_buff;
	uint8_t tmp[32] = {0};

	malloc_container(&log_buff, 48);

	sprintf((char*)tmp, "RCC->CSR=0x%08X.\n", RCC->CSR);
	fill_container(&log_buff, tmp, strlen((char*)tmp));

	__HAL_RCC_PWR_CLK_ENABLE();
	memset(tmp, 0x00, sizeof(tmp));
	sprintf((char*)tmp, "PWR->CSR=0x%08X.\n", PWR->CSR);
	fill_container(&log_buff, tmp, strlen((char*)tmp));

	HAL_UART_Transmit(&huart1, log_buff.pbuff, log_buff.data_len, 100);

	free_container(&log_buff);
}

/*******************************************************************************
* Brief		:  
* Param    	: 
* Return	:      
*******************************************************************************/
void print_rtc_reg(void)
{
	struct container log_buff;
	uint8_t tmp[32] = {0};

	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();

	malloc_container(&log_buff, 32*4);

	sprintf((char*)tmp, "RTC->CR=0x%08X.\n", RTC->CR);
	fill_container(&log_buff, tmp, strlen((char*)tmp));

	memset(tmp, 0x00, sizeof(tmp));
	sprintf((char*)tmp, "RTC->ISR=0x%08X.\n", RTC->ISR);
	fill_container(&log_buff, tmp, strlen((char*)tmp));
    
    memset(tmp, 0x00, sizeof(tmp));
    sprintf((char*)tmp, "RTC->ALRMAR=0x%08X.\n", RTC->ALRMAR);
    fill_container(&log_buff, tmp, strlen((char*)tmp));
    
    memset(tmp, 0x00, sizeof(tmp));
    sprintf((char*)tmp, "RTC->TR=0x%08X.\n", RTC->TR);
    fill_container(&log_buff, tmp, strlen((char*)tmp));
    
	HAL_UART_Transmit(&huart1, log_buff.pbuff, log_buff.data_len, 100);

	free_container(&log_buff);
}








