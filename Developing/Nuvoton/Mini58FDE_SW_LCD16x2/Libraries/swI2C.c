/**************************************************************************//**
 * @file     i2c_software_gpio.c
 * @version  V0.10
 * $Revision: 2 $
 * $Date: 15/02/24 4:28p $
 * @brief    MINI58 series software I2C driver source file
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include <stdio.h>
#include "swI2C.h"

void SDA_DIR_OUT()
{
	GPIO_SetMode(P2, BIT5, GPIO_MODE_OUTPUT);
}
void SDA_DIR_IN()
{
	GPIO_SetMode(P2, BIT5, GPIO_MODE_INPUT);
}
void SCL_DIR_OUT()
{
	GPIO_SetMode(P2, BIT4, GPIO_MODE_OUTPUT);
}
void SCL_DIR_IN()
{
	GPIO_SetMode(P2, BIT4, GPIO_MODE_INPUT);
}
void SDA_HIGH()
{
	P25 = 1;
}
void SDA_LOW()
{
	P25 = 0;
}
void SCL_HIGH()
{
	P24 = 1;
}
void SCL_LOW()
{
	P24 = 0;
}
bool SDA_IN()
{
	return P24;
}

void SW_I2C_init(void)
{
    SDA_DIR_OUT();
    SCL_DIR_OUT();
    delayMicroseconds(100);
    SDA_HIGH();
    SCL_HIGH();
}
void SW_I2C_start(void)
{
    SDA_DIR_OUT();
    SDA_HIGH();
    SCL_HIGH();
    delayMicroseconds(40);
    SDA_LOW();
    delayMicroseconds(40);
    SCL_LOW();
}
void SW_I2C_stop(void)
{
    SDA_DIR_OUT();
    SDA_LOW();
    SCL_LOW();
    delayMicroseconds(40);
    SDA_HIGH();
    SCL_HIGH();
    delayMicroseconds(40);
}
unsigned char SW_I2C_read(unsigned char ack)
{
    unsigned char i = 8;
    unsigned char j = 0;
    SDA_DIR_IN();
    while(i > 0)
    {
        SCL_LOW();
        delayMicroseconds(20);
        SCL_HIGH();
        delayMicroseconds(20);
        j <<= 1;
        if(SDA_IN() != 0x00)
        {
            j++;
        }
        delayMicroseconds(10);
        i--;
    };
    switch(ack)
    {
        case I2C_ACK:
        {
            SW_I2C_ACK_NACK(I2C_ACK);;
            break;
        }
        default:
        {
            SW_I2C_ACK_NACK(I2C_NACK);;
            break;
        }
    }
    return j;
}
void SW_I2C_write(unsigned char value)
{
    unsigned char i = 8;
    SDA_DIR_OUT();
    SCL_LOW();
    while(i > 0)
    {
        if(((value & 0x80) >> 7) != 0x00)
        {
            SDA_HIGH();
        }
        else
        {
            SDA_LOW();
        }
        value <<= 1;
        delayMicroseconds(20);
        SCL_HIGH();
        delayMicroseconds(20);
        SCL_LOW();
        delayMicroseconds(20);
        i--;
    };
}
void SW_I2C_ACK_NACK(unsigned char mode)
{
    SCL_LOW();
    SDA_DIR_OUT();
    switch(mode)
    {
        case I2C_ACK:
        {
            SDA_LOW();
            break;
        }
        default:
        {
            SDA_HIGH();
            break;
        }
    }
    delayMicroseconds(20);
    SCL_HIGH();
    delayMicroseconds(20);
    SCL_LOW();
}
unsigned char SW_I2C_wait_ACK(void)
{
    signed int timeout = 0;
    SDA_DIR_IN();
    SDA_HIGH();
    delayMicroseconds(10);
    SCL_HIGH();
    delayMicroseconds(10);
    while(SDA_IN() != 0x00)
    {
        timeout++;
        if(timeout > I2C_timeout)
        {
            SW_I2C_stop();
            return 1;
        }
    };
    SCL_LOW();
    return 0;
}
