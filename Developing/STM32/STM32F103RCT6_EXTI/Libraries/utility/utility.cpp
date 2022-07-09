/*
 * utility.cpp
 *
 *  Created on: Apr 15, 2021
 *      Author: quoclaptk
 */

#include <utility.h>

//extern SPI_HandleTypeDef hspi1;
extern uint32_t sysTickUptime;
extern uint32_t Tim1TickUptime;
Utility::Utility() {
	// TODO Auto-generated constructor stub

}

Utility::~Utility() {
	// TODO Auto-generated destructor stub
}

void Utility::delayInit(void)
{
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}
/*********************************************************************/
void Utility::delay_us(uint32_t us) // microseconds
{
	uint32_t us_ticks =  us * (SystemCoreClock / 1000000U);
	DWT->CYCCNT = 0U;
	while(DWT->CYCCNT < us_ticks);
}
/*********************************************************************/
void Utility::delay_ms(uint32_t ms) // microseconds
{
	uint32_t ms_ticks =  ms * (SystemCoreClock / 1000U);
	DWT->CYCCNT = 0U;
	while(DWT->CYCCNT < ms_ticks);
}
/*********************************************************************/
uint32_t Utility::micros(void)
{
	return  DWT->CYCCNT / (SystemCoreClock / 1000000U);
	//return (Tim1TickUptime*200 + TIM1->CNT);
}
/*********************************************************************/
uint32_t Utility::millis(void)
{
	return  DWT->CYCCNT / (SystemCoreClock / 1000U);
}
/*********************************************************************/
void Utility::digitalWrite(uint16_t pin, bool level)
{
	if(level)HAL_GPIO_WritePin(GPIOB, pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(GPIOB, pin, GPIO_PIN_RESET);
}
/*********************************************************************/
