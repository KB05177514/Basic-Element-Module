#include "power.h"

/*******************************************************************************
*1、宏定义定义    
*******************************************************************************/

/*******************************************************************************
*2、结构体定义    
*******************************************************************************/
typedef struct
{
    bool stb_is_2_7v;  
  
    bool sensor_power_open; 
    
    bool vacc_power_open;
}PowerTypeDef;

/*******************************************************************************
*3、变量定义    
*******************************************************************************/
static PowerTypeDef Power = 
{
    .stb_is_2_7v = false, 
  
    .sensor_power_open = false,
    
    .vacc_power_open = false,
};

/*******************************************************************************
* Brief     : 打开传感器电源
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
* Brief     : 关闭传感器电源 
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
* Brief     : 传感器电源状态查询 
* Param     : 
* Return    : true:传感器电源打开;false:传感器电源关闭     
*******************************************************************************/
bool Power_SensorPowerIsOpen(void)
{
    return Power.sensor_power_open;
}

/*******************************************************************************
* Brief     : V_STB电源电压选择 
* Param     : input=true:选择2.7V电压; input=false:选择2V电压
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
* Brief     : V_STB电源状态查询  
* Param     : 
* Return    : true:V_STB为2.7V; false:V_STB为2V     
*******************************************************************************/
bool Power_STBPowerIs2_7V(void)
{
    return Power.stb_is_2_7v;
}

/*******************************************************************************
* Brief     : 打开V_ACC电源 
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
* Brief     : 关闭V_ACC电源 
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
* Brief     : VACC电源状态查询 
* Param     : 
* Return    :      
*******************************************************************************/
bool Power_VACCIsOpen(void)
{
    return Power.vacc_power_open;
}




