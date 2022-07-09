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
#include <RF24.h>
#include <WString.h>

#define MOSI 	P05
#define MISO 	P06
#define SCK  	P07
#define CSN  	P04
#define CE		P24

uint32_t uwTick = 0;
uint32_t ledTime = 0;

void SYS_Init(void)
{
	SYS_UnlockReg();
	CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV_HCLK(2));
	CLK->APBCLK = CLK_APBCLK_TMR1CKEN_Msk;
	SystemCoreClockUpdate();
	SYS_LockReg();
}

void ce(bool level)
{

}
void csn(bool level)
{
	if(level == true)CSN = 1;
	else CSN = 0;
}
uint8_t spiWrite(uint8_t myByte)
{
	for(uint8_t i = 0; i<8; i++)
	{
		if(myByte & 0x80)MOSI = 1;
		else MOSI = 0;
		myByte <<= 1;
		SCK = 1; /* a slave latches input data bit */
		if(MISO != 0)myByte |= 0x01;
		SCK = 0; /* a slave shifts out next output data bit */
	}
	return(myByte);
}

extern "C" void SysTick_Handler(void)
{
	ledTime++;
	if(ledTime>500)
	{
		P12 ^= 1;
		ledTime = 0;
	}
  /* Increment counter necessary in delay(). */
	uwTick++;
}

uint32_t millis()
{
	return uwTick;
}

void GPIO_Init()
{
	GPIO_SetMode(P2, BIT4, GPIO_MODE_OUTPUT);/* CE */
	GPIO_SetMode(P0, BIT4, GPIO_MODE_OUTPUT);/* CS */

	GPIO_SetMode(P0, BIT5, GPIO_MODE_OUTPUT); /* SI */
	GPIO_SetMode(P0, BIT6, GPIO_MODE_INPUT);/* SO */
	GPIO_SetMode(P0, BIT7, GPIO_MODE_OUTPUT);/* SCK */


	GPIO_SetMode(P1, BIT2, GPIO_MODE_OUTPUT); /* LED */

	GPIO_SetMode(P3, BIT4, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P3, BIT5, GPIO_MODE_OUTPUT);
//	GPIO_SetMode(P1, BIT5, GPIO_MODE_OUTPUT);
}

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

String convertToString(char* a, int size)
{
    int i;
    String s = "";
    for (i = 0; i < size; i++) {
    	if(a[i] != '\0')s = s + a[i];
    	else return s;
    }
    return s;
}

int main()
{
	byte text[32]= "";
	String strON = "RELAYON", strOFF = "RELAYOFF";
	String mydata;
	SYS_Init();
	GPIO_Init();
	SysTick_Config(SystemCoreClock/1000);/* 1ms increment for system timer */
	radio.begin();
	radio.openReadingPipe(0, address);
	radio.setPALevel(RF24_PA_MIN);
	radio.startListening();
    while(1)
    {
		if(radio.available())
		{
			radio.read(&text, sizeof(text));
			mydata = (String)(char*)text;
			if(mydata == strON)
			{
				P34 = P35 = 1;
			}
			else if(mydata == strOFF)
			{
				P34 = P35 = 0;
			}
		}
    }

}

/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/
