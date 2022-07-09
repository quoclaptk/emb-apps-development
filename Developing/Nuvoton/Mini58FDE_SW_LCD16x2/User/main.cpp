/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * $Revision: 3 $
 * $Date: 15/02/13 2:19p $
 * @brief    A project template for Mini58 MCU.
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "main.h"
#include "swI2C.h"
#include "lcd16x2.h"


void SYS_Init(void)
{
	SYS_UnlockReg();
	CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV_HCLK(2));
	CLK->APBCLK = CLK_APBCLK_TMR1CKEN_Msk;
	SystemCoreClockUpdate();
	SYS_LockReg();
}

LCD lcd;

void masterTransmit(uint8_t address, uint8_t *data, uint32_t size)
{
	SW_I2C_start();
//	i2c.write(address<<1);
	SW_I2C_write(address<<1);
	for(uint8_t i=0; i<size; i++)
	{
//		i2c.write(*data);
		SW_I2C_write(*data);
		data++;
	}
	SW_I2C_stop();

}
/******************************************************************************/
void masterReceive(uint8_t address, uint8_t *data, uint32_t size)
{
	SW_I2C_start();
	SW_I2C_write((address<<1)|1);
	for(uint8_t i=0; i<size; i++)
	{
//		*data = i2c.read(I2C_NACK);
		*data = SW_I2C_read(I2C_NACK);
		data++;
	}
	SW_I2C_stop();
}



int main()
{
    SYS_Init();
    SW_I2C_init();
    lcd.init();
    lcd.setCursor(0, 1);
    lcd.putChars((char*)"slihsiohgioshgos");

    while(1)
    {

    }

}

/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/
