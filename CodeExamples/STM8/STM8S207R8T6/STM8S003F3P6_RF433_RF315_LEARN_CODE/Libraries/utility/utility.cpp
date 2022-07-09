/*
 * utility.cpp
 *
 *  Created on: Apr 15, 2021
 *      Author: quoclaptk
 */

#include <utility.h>

//extern SPI_HandleTypeDef hspi1;
uint32_t Tim1TickUptime = 0;
Utility::Utility() {
	// TODO Auto-generated constructor stub

}

Utility::~Utility() {
	// TODO Auto-generated destructor stub
}

void Utility::delayInit(void)
{
	
}
/*********************************************************************/
void Utility::delay_us(uint32_t us) // microseconds
{
	
}
/*********************************************************************/
void Utility::delay_ms(uint32_t ms) // microseconds
{
	
}
/*********************************************************************/
uint32_t Utility::micros(void)
{
    return (Tim1TickUptime*35);
}
/*********************************************************************/
uint32_t Utility::millis(void)
{
	//return  DWT->CYCCNT / (SystemCoreClock / 1000U);
   return 0;
}
/*********************************************************************/
void Utility::digitalWrite(uint16_t pin, bool level)
{
	
}
/*********************************************************************/
