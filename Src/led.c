#include "led.h"

/*******************************************************************************
* 1°¢∫Í∂®“Â
*******************************************************************************/
#define LED0_STROBE_CYCLE                               1000

/*******************************************************************************
* Function Name : 
* Description   :  
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
void Led_Open(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = LED0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED0_GPIO_Port, &GPIO_InitStruct);
    
    HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
    
    xTimerChangePeriod(LedTimerHandle, LED0_STROBE_CYCLE / 2, 100);    
}

/*******************************************************************************
* Function Name : 
* Description   :  
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
void Led_Close(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = LED0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED0_GPIO_Port, &GPIO_InitStruct);   
}

/*******************************************************************************
* Function Name : 
* Description   :  
* Input         :           
* Output        :         
* Return        :         
*******************************************************************************/
void Led_LedTimerCallback(void)
{
    HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
}











