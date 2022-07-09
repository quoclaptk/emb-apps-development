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
#include "main.h"
#include "LiquidCrystal_I2C.h"
#include "DS1307RTC.h"
/** Tick Counter united by ms */
static volatile uint32_t _dwTickCount = 0;

void SYS_Init(void)
{
    /* Enable IP clock */
    CLK->APBCLK = CLK_APBCLK_UART0_EN_Msk;

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and cyclesPerUs automatically. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFP &= ~(SYS_GPB_MFP_PB0_Msk | SYS_GPB_MFP_PB1_Msk);
    SYS->GPB_MFP |= (SYS_GPB_MFP_PB0_UART0_RXD | SYS_GPB_MFP_PB1_UART0_TXD);

    if (SysTick_Config(SystemCoreClock / 1000))
     { // Set Systick to 1ms interval
       while (true)
         ; // Capture error
     }
}

/**
 * \brief SysTick_Handler.
 */
void SysTick_Handler(void)
{
  /* Increment counter necessary in delay(). */
  _dwTickCount++;
}

/**
 *  \brief Get current Tick Count, in ms.
 */
uint32_t GetTickCount(void)
{
  return _dwTickCount;
}


void transmitData(uint8_t address, uint8_t data)
{
//    i2c.start();
//    i2c.write(address<<1);
//    for(uint8_t i=0; i<size; i++)
//    {
//        i2c.write(*data);
//        data++;
//    }
//    i2c.stop();
}

void masterTransmit(uint8_t address, uint8_t *data, uint8_t size)
{
//    i2c.start();
//    i2c.write(address<<1);
//    for(uint8_t i=0; i<size; i++)
//    {
//        i2c.write(*data);
//        data++;
//    }
//    i2c.stop();
}

void masterReceive(uint8_t address, uint8_t *data, uint8_t size)
{
//    i2c.start();
//    i2c.write(address<<1);
//    for(uint8_t i=0; i<size; i++)
//    {
//        i2c.write(*data);
//        data++;
//    }
//    i2c.stop();
}

uint8_t spiWrite(uint8_t data)
{

}

void _cs(bool level)
{

}

uint32_t micros(void)
{

    uint32_t ticks, ticks2;
    uint32_t pend, pend2;
    uint32_t count, count2;

    ticks2 = SysTick->VAL;
    pend2 = !!(SCB->ICSR & SCB_ICSR_PENDSTSET_Msk);
    count2 = GetTickCount();

    do
    {
        ticks = ticks2;
        pend = pend2;
        count = count2;
        ticks2 = SysTick->VAL;
        pend2 = !!(SCB->ICSR & SCB_ICSR_PENDSTSET_Msk);
        count2 = GetTickCount();
    } while ((pend != pend2) || (count != count2) || (ticks < ticks2));

    return ((count + pend) * 1000) + (((SysTick->LOAD - ticks) * (1048576 / (SystemCoreClock / 1000000))) >> 20);
    // this is an optimization to turn a runtime division into two compile-time divisions and
    // a runtime multiplication and shift, saving a few cycles
}




//char *daysOfWeek[7] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
DS1307_RTC rtc();
LiquidCrystal_I2C lcd(0x27, 16, 2);


int main()
{
    int8_t ch;

    uint32_t times = 0;

    /* Unlock protected registers */
    SYS_UnlockReg();

    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

    printf("Simple Demo Code\n\n");

    printf("Please Input Any Key\n\n");

    GPIO_SetMode(PA, BIT3, GPIO_PMD_OUTPUT);

    do
    {
    	times = micros();
    	GPIO_SET_OUT_DATA(PA, 1<<3);
    	delay(100);
		GPIO_SET_OUT_DATA(PA, 0<<3);
		delay(100);
    }
    while(1);
}

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
