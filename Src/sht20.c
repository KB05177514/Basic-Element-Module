/*******************************************************************************
* @version	: v1.0
* @author	: guankaibin
* @brief	: SHT20��������.    
*******************************************************************************/


#include<stdbool.h>
#include<stdint.h>

#include "i2c.h"

#include "power.h"

/*******************************************************************************
*1���ṹ�嶨��    
*******************************************************************************/
#define SHT20_SLAVE_ADDR                                0x80

#define SHT20_TEMPERATURE_MEASURE_CMD                   0xF3
#define SHT20_RELATIVE_HUMIDITY_MEASURE_CMD             0xF5

/*SHT20 14bit�¶�������ʱ��85ms*/
#define SHT20_TEMPERATURE_MEASURE_TIME_MS               85

/*SHT20 12bitʪ��������ʱ��29ms*/
#define SHT20_RELATIVE_HUMIDITY_MEASURE_TIME_MS         29


/*******************************************************************************
*2���ṹ�嶨��    
*******************************************************************************/
typedef struct
{
    volatile float temperature;
    
    volatile float relative_humidity;
}SHT20TypeDef;

/*******************************************************************************
*3����������    
*******************************************************************************/
static SHT20TypeDef SHT20;

/*******************************************************************************
* Brief     : ��SHT20
* Param     : 
* Return    :      
*******************************************************************************/
void SHT20_Open(void)
{
    if(Power_SensorPowerIsOpen() == true)
    {
        
    }
    else
    {
        Power_SensorOpen();
        vTaskDelay(15);
    }
}

/*******************************************************************************
* Brief     : �ر�SHT20
* Param     : 
* Return    :      
*******************************************************************************/
void SHT20_Close(void)
{
    Power_SensorClose();
}

/*******************************************************************************
* Brief     : д�¶Ȳ������� 
* Param     : 
* Return    :      
*******************************************************************************/
bool SHT20_WriteTMeasureCmd(void)
{
    uint8_t tx_cmd = SHT20_TEMPERATURE_MEASURE_CMD;  
       
    HAL_StatusTypeDef HAL_Status = 
    HAL_I2C_Master_Transmit(&hi2c1, SHT20_SLAVE_ADDR, &tx_cmd, sizeof(tx_cmd), 5);
    if(HAL_Status != HAL_OK)
    {
        return false;
    }
    else
    {
    	return true;
    }
}

/*******************************************************************************
* Brief     : ��ȡ�¶���ֵ 
* Param     : 
* Return    :      
*******************************************************************************/
bool SHT20_ReadTData(void)
{   
    uint8_t rx_data[3] = {0};
    HAL_StatusTypeDef HAL_Status = 
    HAL_I2C_Master_Receive(&hi2c1, SHT20_SLAVE_ADDR, rx_data, sizeof(rx_data), 5);
    if(HAL_Status != HAL_OK)
    {
        return false;
    }
    
    //У��
    
    uint16_t temperature = (rx_data[0] << 8) + (rx_data[1] & 0xFC);
    SHT20.temperature = ((temperature * 175.72) / 65535) - 46.85;
    
    return true;
}

/*******************************************************************************
* Brief     : дʪ�Ȳ�������
* Param     : 
* Return    :      
*******************************************************************************/
bool SHT20_WriteRHMeasureCmd(void)
{
    uint8_t tx_cmd = SHT20_RELATIVE_HUMIDITY_MEASURE_CMD;
    HAL_StatusTypeDef HAL_Status = 
    HAL_I2C_Master_Transmit(&hi2c1, SHT20_SLAVE_ADDR, &tx_cmd, sizeof(tx_cmd), 5);
    if(HAL_Status != HAL_OK)
    {
        return false;
    }
    else
    {
    	return true;
    }
}

/*******************************************************************************
* Brief     : ��ȡʪ����ֵ
* Param     : 
* Return    :      
*******************************************************************************/
bool SHT20_ReadRHData(void)
{    
    uint8_t rx_data[3] = {0};
    HAL_StatusTypeDef HAL_Status = 
    HAL_I2C_Master_Receive(&hi2c1, SHT20_SLAVE_ADDR, rx_data, sizeof(rx_data), 5);    
    if(HAL_Status != HAL_OK)
    {
        return false;
    }
    
    //У��
    
    uint16_t RH = (rx_data[0] << 8) + (rx_data[1] & 0xFC);
    SHT20.relative_humidity = ((RH * 125) / 65535) - 6;
    
    return true;
}

/*******************************************************************************
* Brief     : ��ѯSHT20�¶�
* Param     : 
* Return    :      
*******************************************************************************/
float SHT20_GetT(void)
{
    return SHT20.temperature;
}

/*******************************************************************************
* Brief     : ��ѯSHT20ʪ��
* Param     : 
* Return    :      
*******************************************************************************/
float SHT20_GetRH(void)
{
    return SHT20.relative_humidity;
}

/*******************************************************************************
* Brief     : SHT20�������
* Param     : 
* Return    :      
*******************************************************************************/
void SHT20_Handler(void)
{
    SHT20_WriteTMeasureCmd();

  	vTaskDelay(SHT20_TEMPERATURE_MEASURE_TIME_MS);

  	SHT20_ReadTData();

  	SHT20_WriteRHMeasureCmd();

  	vTaskDelay(SHT20_RELATIVE_HUMIDITY_MEASURE_TIME_MS);

  	SHT20_ReadRHData();
  
    vTaskDelay(885);
}























