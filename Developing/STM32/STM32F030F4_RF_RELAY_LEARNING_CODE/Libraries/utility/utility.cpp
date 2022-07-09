/*
 * utility.cpp
 *
 *  Created on: Apr 15, 2021
 *      Author: quoclaptk
 */

#include <utility.h>

//extern SPI_HandleTypeDef hspi1;
extern uint32_t sysTickUptime;
Utility::Utility() {
	// TODO Auto-generated constructor stub

}

Utility::~Utility() {
	// TODO Auto-generated destructor stub
}

/*********************************************************************/
void Utility::delay_us(uint32_t us) // microseconds
{
//	uint32_t us_ticks =  us * (SystemCoreClock / 1000000U);
//	DWT->CYCCNT = 0U;
//	while(DWT->CYCCNT < us_ticks);
	uint32_t us_ticks =  us * (SystemCoreClock / 1000000U);
	SysTick->VAL = 0U;
	while(SysTick->VAL < us_ticks);
}
/*********************************************************************/
void Utility::delay_ms(uint32_t ms) // microseconds
{
//	uint32_t ms_ticks =  ms * (SystemCoreClock / 1000U);
//	DWT->CYCCNT = 0U;
//	while(DWT->CYCCNT < ms_ticks);

	uint32_t start_tick = sysTickUptime;
	while(sysTickUptime-start_tick < ms){}
}
/*********************************************************************/
uint32_t Utility::micros(void)
{
	return (sysTickUptime*1000 + (SysTick->VAL)/32);
}
/*********************************************************************/
uint32_t Utility::millis(void)
{
	return (sysTickUptime);
}
/*********************************************************************/
void Utility::digitalWrite(uint16_t pin, bool level)
{
	if(level)HAL_GPIO_WritePin(GPIOB, pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(GPIOB, pin, GPIO_PIN_RESET);
}
/*********************************************************************/
