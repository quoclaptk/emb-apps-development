/*
 * Clock.c
 *
 *  Created on: Feb 20, 2022
 *      Author: ADMIN
 */
#include "stm32f1xx.h"
#include"string.h"

#define O "123"
void HSE_PLL_Clock_init(uint32_t PLL_multiplication)
{
    /* enable HSE clock */

	RCC->CR |= 1<<16;
	RCC->CFGR |= 4<<8;
	while((RCC->CR & (uint32_t)(1<<17)) == 0);/* HSE is stable */

	RCC->CFGR    &= ~(1<<17); /* HSE clock not divided */
	RCC->CFGR    |= (uint32_t)(1<<16); /* HSE oscillator clock selected as PLL input clock */
	/* nhan clock HSE voi 8(thach anh); VD: -> 8*6 = 48 MHZ */
//	RCC->CFGR    |= (uint32_t)((PLL_multiplication-2)<<18);
	RCC->CFGR |= 7<<18; /* PLL input clock x 9 */

	//RCC->CFGR    |= (uint32_t)(7<<24);
	/* enable PLL */
	RCC->CR |= (1<<24);
	/* doi PLL on dinh */
	while((RCC->CR & (uint32_t)(1<<25)) == 0);
	/*chon PLL la nguon vao cua clock   */
	RCC->CFGR    |= (2<<0);
	while((RCC->CFGR & (uint32_t)(2<<2)) == 0); /*  */
}


void HSE_72MHz_Init(void)
{

	RCC->CFGR &= ~(0xF<<18);  /* Clear PLL */


	//RCC->CFGR |= 4<<18;  /* clock source x6  = 6x8 = 48MHz */
//	RCC->CFGR |= 5<<18;  /* clock source x6  = 7x8 = 56MHz */
	RCC->CFGR |= 7<<18;  /* clock source x6  = 9x8 =72MHz */


	RCC->CFGR |= 4<<8; /* select clock for APB1 */

	RCC->CR &= ~(1<<24); /* Disable PLL */
	RCC->CFGR &= ~(1<<17);/* Select HSE for PLL */
	RCC->CFGR |= 1<<16; /* HSE is clock source for PLL */
	RCC->CFGR |= 2<<0; /* Select PLL clock source */
	RCC->CR |= (1<<24); /* enable PLL */

	FLASH->ACR |= 2<<0;

	RCC->CR |= (1<<16); /* HSE disable enable */
	while((RCC->CR & (uint32_t)(1<<17)) == 0);/* HSE is stable */
	RCC->CFGR &= ~(1<< 0);

}


void rcc_HSE_Configuration(void)
    {
      /*
       * Configuration parameter --> Clock tree for STM32F103
       * Input frequency of HSE = 8 MHz
       * PLL_MUX = 9
       * USB Pre-scaler = 1
       * AHB Pre-Scaler = 1
       * Cortex Pre-scaler = 1
       * --> 72MHz system clock configuration
       *
       * Configuration parameter for peripheral
       * APB1 Pre-scaler = 2 --> 36MHz and 72MHz
       * APB2 Pre-scaler = 1 --> 72MHz and 72MHz
       * ADC Pre-scaler = 6 --> ADC 12MHz
       *
       */

      /*
       * Clock_Mux configuration
       */

      //PLL_Mux configuration
      RCC->CFGR &= ~(RCC_CFGR_PLLMULL); //Clear PLL Mux fields
      RCC->CFGR |= RCC_CFGR_PLLMULL9; //PLL 8MHz *9 = 72MHz
      //USB Pre-scaler
      RCC->CFGR |= RCC_CFGR_USBPRE; //PLL clock is not divided


      /*
       * HSE configuration
       */
      //Enable HSE oscillator
      RCC->CR |= RCC_CR_HSEON;
      //Wait for it to stabilize
      while((RCC->CR & RCC_CR_HSERDY) == 0);
      //Select HSE as PLL source
      RCC->CFGR |= RCC_CFGR_PLLSRC;
      //Enable PLL
      RCC->CR |= RCC_CR_PLLON;
      //Wait for PLL ready
      while((RCC->CR & RCC_CR_PLLRDY) == 0 );

      /*
       * Set-up latency
       *Flash Pre-fetch and wait state configuration
       *Flash 2 wait state = 72MHz
       */

      //Configuration LATENCY field is Two wait state (72MHz)
      FLASH->ACR &= ~(FLASH_ACR_LATENCY_Msk);
      FLASH->ACR |= FLASH_ACR_LATENCY_1;
      //Enable Pre-fetch buffer
      FLASH->ACR |= FLASH_ACR_PRFTBE;


      /*
       * Select system clock
       */

      //Select HSE as system clock
      RCC->CFGR &= ~(RCC_CFGR_SW);
      RCC->CFGR |= RCC_CFGR_SW_1;

      //Wait for PLL to be the active CLK source
      while((RCC->CFGR & RCC_CFGR_SW_1) == 0);

      /*
       * Configuration for peripheral
       */

      //APB1 configuration
      RCC->CFGR &= ~(RCC_CFGR_PPRE1);
      RCC->CFGR |= RCC_CFGR_PPRE1_2;
      //APB2 configuration
      RCC->CFGR &= ~(RCC_CFGR_PPRE2);
      //ADC Pre-scaler configuration
      RCC->CFGR &= ~(RCC_CFGR_ADCPRE);
      RCC->CFGR |= RCC_CFGR_ADCPRE_1;

    }



