/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 14/12/08 11:51a $
 * @brief    Software Development Template.
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <swI2C.h>
#include "main.h"
#include "LiquidCrystal_I2C.h"
#include "DS1307RTC.h"

#define MOSI 	P05
#define MISO 	P06
#define SCK  	P07
#define CS  	P04

SWI2C i2c;

void SYS_Init(void)
{

}

void masterTransmit(uint8_t address, uint8_t *data, uint8_t size)
{
    i2c.start();
    i2c.write(address<<1);
    for(uint8_t i=0; i<size; i++)
    {
        i2c.write(*data);
        data++;
    }
    i2c.stop();
}

void masterReceive(uint8_t address, uint8_t *data, uint8_t size)
{
	i2c.start();
	i2c.write((address<<1)|1);
	for(uint8_t i=0; i<size; i++)
	{
		*data = i2c.read(I2C_NACK);
		data++;
	}
	i2c.stop();
}

void transmitData(uint8_t address, uint8_t data)
{
	i2c.start();
	i2c.write(address<<1);
	i2c.write(data);
	i2c.stop();
}


const char *daysOfWeek[7] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
DS1307_RTC rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);


int main()
{
    int8_t ch;
    /* Unlock protected registers */
    SYS_UnlockReg();
    SYS_Init();
//    I2C0_Init();
    /* Lock protected registers */
	lcd.init();
	lcd.backlight();
	lcd.setCursor(2,0);
	lcd.print("Arduinokit.vn");
	lcd.setCursor(0,1);
	lcd.print("Xin chao cac ban");

    do
    {
    	lcd.print("Hello World!");
//    	uint32_t data = GPIO_GET_IN_DATA(PA);
//    	data |= 1<<3;
//    	GPIO_SET_OUT_DATA(PA, data);
//    	delay(100);
//    	data &= ~(1<<3);
//		GPIO_SET_OUT_DATA(PA, data);
//		delay(100);
    }
    while(1);
}

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
