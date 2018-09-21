#include "led.h"

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
    
    GPIO_InitStruct.Pin = MCU2_LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(MCU2_LED_GPIO_Port, &GPIO_InitStruct);
    
    xTimerChangePeriod(LedTimerHandle, 500, 10);
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
    
    GPIO_InitStruct.Pin = MCU2_LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(MCU2_LED_GPIO_Port, &GPIO_InitStruct);
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
    HAL_GPIO_TogglePin(MCU2_LED_GPIO_Port, MCU2_LED_Pin);
}




