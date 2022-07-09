/*******************************************************************************
                       Copyright by Pham Van Lap KMT
********************************************************************************
** File Name        : I2C.C
** Version          : 1.0
** Author           : Pham Van Lap
** Create Date      : 10/12/2018
** Company          : FPT Software
** Email            : quoclaptk@gmail.com
** Phone Numbers    : 0886560383 or 0963836272
*******************************************************************************/

/*******************************************************************************
                             Revision History
********************************************************************************
**    Date              Author                           Detail
** ----------       --------------      ----------------------------------------
** 10/12/2018        Pham Van Lap                      Create new
*******************************************************************************/

/*******************************************************************************
                          Include Files
*******************************************************************************/
#include "I2C.h"
/*******************************************************************************
                      void Soft_I2C_Init()
*******************************************************************************/
void I2C_Init()
{
    SCL_OUTPUT_MODE;
    SDA_OUTPUT_MODE;
    SDA_PIN_LOW;
    SCL_PIN_LOW;
}
/*******************************************************************************
                      void Soft_I2C_Start(void)
*******************************************************************************/
void I2C_Start(void)
{
    SDA_PIN_HIGH;
    SCL_PIN_HIGH;
    delay_us(I2C_DELAY_TIMES);
    SDA_PIN_LOW;
    delay_us(I2C_DELAY_TIMES);
    SCL_PIN_LOW; 
}
/*******************************************************************************
                      void Soft_I2C_Stop(void)
*******************************************************************************/
void I2C_Stop(void)
{
    SDA_PIN_LOW;
    SCL_PIN_HIGH;
    delay_us(I2C_DELAY_TIMES);
    SDA_PIN_HIGH;
}
/*******************************************************************************
                      void Soft_I2C_WriteByte(uint8_t dat)
*******************************************************************************/
void I2C_WriteByte(uint8_t dat)
{
    uint8_t i;
    for(i=0;i<8;i++)
    { 
        SCL_PIN_LOW;  
        if((dat&0x80)&&1)SDA_PIN_HIGH; 
        else SDA_PIN_LOW; //tranfer  bit
        dat<<=1;    //shift left data
        delay_us(I2C_DELAY_TIMES);
        SCL_PIN_HIGH; 
        delay_us(I2C_DELAY_TIMES);
        SCL_PIN_LOW;             
    }
    delay_us(I2C_DELAY_TIMES);
    SCL_PIN_HIGH;
    delay_us(I2C_DELAY_TIMES);
    SCL_PIN_LOW;
    delay_us(I2C_DELAY_TIMES);
}
/*******************************************************************************
                      uint8_t Soft_I2C_ReadByte(void)
*******************************************************************************/
uint8_t I2C_ReadByte(void)
{
    SDA_INPUT_MODE;/* Set input mode for SDA pin */
    uint8_t dat;
    dat = 0x00;
    for(int i=0; i<8; i++) 
    { 
        delay_us(I2C_DELAY_TIMES);
        SCL_PIN_HIGH;
        delay_us(I2C_DELAY_TIMES);
        dat <<= 1;
        if(SDA_PIN_INPUT) dat++;
        SCL_PIN_LOW;
    }
    SDA_OUTPUT_MODE; /* Set output mode for SDA pin */
    SDA_PIN_HIGH; 
    SCL_PIN_HIGH;
    delay_us(I2C_DELAY_TIMES);
    SCL_PIN_LOW;
    delay_us(I2C_DELAY_TIMES);
    return dat;
}
/*******************************************************************************
******************************** END OF FILE ***********************************
*******************************************************************************/