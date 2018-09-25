#include "power.h"

/*******************************************************************************
*1���궨�嶨��    
*******************************************************************************/

/*******************************************************************************
*2���ṹ�嶨��    
*******************************************************************************/
typedef struct
{
    bool stb_is_2_7v;  
  
    bool sensor_power_open; 
    
    bool vacc_power_open;
}PowerTypeDef;

/*******************************************************************************
*3����������    
*******************************************************************************/
static PowerTypeDef Power = 
{
    .stb_is_2_7v = false, 
  
    .sensor_power_open = false,
    
    .vacc_power_open = false,
};

/*******************************************************************************
* Brief     : �򿪴�������Դ
* Param     : 
* Return    :      
*******************************************************************************/
void Power_SensorOpen(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = SENSOR_POWER_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SENSOR_POWER_GPIO_Port, &GPIO_InitStruct);
    HAL_GPIO_WritePin(SENSOR_POWER_GPIO_Port, SENSOR_POWER_Pin, GPIO_PIN_RESET);
    
    Power.sensor_power_open = true;
}

/*******************************************************************************
* Brief     : �رմ�������Դ 
* Param     : 
* Return    :      
*******************************************************************************/
void Power_SensorClose(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = SENSOR_POWER_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SENSOR_POWER_GPIO_Port, &GPIO_InitStruct);

    Power.sensor_power_open = false;
}

/*******************************************************************************
* Brief     : ��������Դ״̬��ѯ 
* Param     : 
* Return    : true:��������Դ��;false:��������Դ�ر�     
*******************************************************************************/
bool Power_SensorPowerIsOpen(void)
{
    return Power.sensor_power_open;
}

/*******************************************************************************
* Brief     : V_STB��Դ��ѹѡ�� 
* Param     : input=true:ѡ��2.7V��ѹ; input=false:ѡ��2V��ѹ
* Return    :      
*******************************************************************************/
void Power_STBPowerSwitch2_7V(bool input)
{
    if(input == true)
    {
        GPIO_InitTypeDef GPIO_InitStruct;
        
        GPIO_InitStruct.Pin = VSET_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(VSET_GPIO_Port, &GPIO_InitStruct);
        HAL_GPIO_WritePin(VSET_GPIO_Port, VSET_Pin, GPIO_PIN_RESET);
        
        Power.stb_is_2_7v = true;
    }
    else
    {
        Power.stb_is_2_7v = false;
    }
}

/*******************************************************************************
* Brief     : V_STB��Դ״̬��ѯ  
* Param     : 
* Return    : true:V_STBΪ2.7V; false:V_STBΪ2V     
*******************************************************************************/
bool Power_STBPowerIs2_7V(void)
{
    return Power.stb_is_2_7v;
}

/*******************************************************************************
* Brief     : ��V_ACC��Դ 
* Param     : 
* Return    :      
*******************************************************************************/
void Power_VACCOpen(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = ACC_PWR_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ACC_PWR_GPIO_Port, &GPIO_InitStruct);
    HAL_GPIO_WritePin(ACC_PWR_GPIO_Port, ACC_PWR_Pin, GPIO_PIN_RESET);   
    
    Power.vacc_power_open = true;
}

/*******************************************************************************
* Brief     : �ر�V_ACC��Դ 
* Param     : 
* Return    :      
*******************************************************************************/
void Power_VACCClose(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = ACC_PWR_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ACC_PWR_GPIO_Port, &GPIO_InitStruct);  
    
    Power.vacc_power_open = false;
}

/*******************************************************************************
* Brief     : VACC��Դ״̬��ѯ 
* Param     : 
* Return    :      
*******************************************************************************/
bool Power_VACCIsOpen(void)
{
    return Power.vacc_power_open;
}




