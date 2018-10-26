#include<string.h>
#include "iwdg.h"
#include "usart.h"
#include "stm32l0xx_hal_pwr.h"
#include "container.h"


void test_process(void)
{	   
    HAL_UART_Transmit(&huart1, "enter into standby mode.\n", 25, 100);
    
//    HAL_Delay(1000);
  	
	HAL_PWR_EnterSTANDBYMode();
}


void test_init(void)
{
	char tmp[64] = {0};
	uint16_t len = 0;

	HAL_StatusTypeDef status;

	sprintf(tmp, "iwdg->pr=0x%08X.\n", hiwdg.Instance->PR);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);

	memset(tmp, 0x00, sizeof(tmp));
	sprintf(tmp, "iwdg->rlr=0x%08X.\n", hiwdg.Instance->RLR);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);

	memset(tmp, 0x00, sizeof(tmp));
	sprintf(tmp, "rcc->csr=0x%08X.\n", RCC->CSR);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);

	__HAL_RCC_PWR_CLK_ENABLE();
	memset(tmp, 0x00, sizeof(tmp));
	sprintf(tmp, "pwr->csr=0x%08X.\n", PWR->CSR);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);   
}

void test_backupdomain(void)
{
	__HAL_RCC_PWR_CLK_ENABLE();

	HAL_PWR_EnableBkUpAccess();

	char tmp[64] = {0};
	uint16_t len = 0;
	HAL_StatusTypeDef status;

	sprintf(tmp, "RTC->BKP0R=0x%08X.\n", RTC->BKP0R);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);

	memset(tmp, 0x00, sizeof(tmp));
	sprintf(tmp, "RTC->BKP1R=0x%08X.\n", RTC->BKP1R);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);


	memset(tmp, 0x00, sizeof(tmp));
	sprintf(tmp, "RTC->BKP2R=0x%08X.\n", RTC->BKP2R);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);

	memset(tmp, 0x00, sizeof(tmp));
	sprintf(tmp, "RTC->BKP3R=0x%08X.\n", RTC->BKP3R);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);

	memset(tmp, 0x00, sizeof(tmp));
	sprintf(tmp, "RTC->BKP4R=0x%08X.\n", RTC->BKP4R);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);

	RTC->BKP0R = 0x000000AA;
	RTC->BKP1R = 0x0000CC00;
	RTC->BKP2R = 0x00AA0000;
	RTC->BKP3R = 0xCC000000;
	RTC->BKP4R = 0xAACCAACC;
    
	sprintf(tmp, "RTC->BKP0R=0x%08X.\n", RTC->BKP0R);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);

	memset(tmp, 0x00, sizeof(tmp));
	sprintf(tmp, "RTC->BKP1R=0x%08X.\n", RTC->BKP1R);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);


	memset(tmp, 0x00, sizeof(tmp));
	sprintf(tmp, "RTC->BKP2R=0x%08X.\n", RTC->BKP2R);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);

	memset(tmp, 0x00, sizeof(tmp));
	sprintf(tmp, "RTC->BKP3R=0x%08X.\n", RTC->BKP3R);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);

	memset(tmp, 0x00, sizeof(tmp));
	sprintf(tmp, "RTC->BKP4R=0x%08X.\n", RTC->BKP4R);
	len = strlen(tmp);
	status = HAL_UART_Transmit(&huart1, (uint8_t*)tmp, len, 100);   
    
	RTC->BKP0R = 0x00000055;
	RTC->BKP1R = 0x00005500;
	RTC->BKP2R = 0x00550000;
	RTC->BKP3R = 0x55000000;
	RTC->BKP4R = 0xAA55AA55;    

	HAL_PWR_DisableBkUpAccess();
}
























