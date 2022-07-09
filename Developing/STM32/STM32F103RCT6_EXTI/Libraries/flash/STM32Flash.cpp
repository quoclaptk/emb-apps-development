/*
 * STM32Flash.cpp
 *
 *  Created on: Apr 24, 2021
 *      Author: quoclaptk
 */

#include <STM32Flash.h>

STM32Flash::STM32Flash() {
	// TODO Auto-generated constructor stub

}

STM32Flash::~STM32Flash() {
	// TODO Auto-generated destructor stub
}

uint8_t lengthPage;

void STM32Flash::deleteBuffer(char* data)
{
	uint8_t len = strlen(data);
	for(uint8_t i = 0; i < len; i++)
	{
		data[i] = 0;
	}
}

void STM32Flash::flashLock()
{
	HAL_FLASH_Lock();
}

void STM32Flash::flashUnlock()
{
	HAL_FLASH_Unlock();
}

void STM32Flash::flashErase(uint32_t addr)
{
	flashUnlock();
	while((FLASH->SR&FLASH_SR_BSY));
	FLASH->CR |= FLASH_CR_PER; //Page Erase Set
	FLASH->AR = addr; //Page Address
	FLASH->CR |= FLASH_CR_STRT; //Start Page Erase
	while((FLASH->SR&FLASH_SR_BSY));
	FLASH->CR &= ~FLASH_SR_BSY;
	FLASH->CR &= ~FLASH_CR_PER; //Page Erase Clear
}

void STM32Flash::flashWriteInt(uint32_t addr, int data)
{
	flashUnlock();
	FLASH->CR |= FLASH_CR_PG;				/*!< Programming */
	while((FLASH->SR&FLASH_SR_BSY));
	*(__IO uint16_t*)addr = data;
	while((FLASH->SR&FLASH_SR_BSY));
	FLASH->CR &= ~FLASH_CR_PG;
	flashLock();
}

uint16_t STM32Flash::flashReadInt(uint32_t addr)
{
	uint16_t* val = (uint16_t *)addr;
	return *val;
}

void STM32Flash::flashWriteDword(uint32_t addr, uint32_t* data, uint8_t size)
{
	flashUnlock();
	FLASH->CR |= FLASH_CR_PG;
	for(int i=0; i<size; i+=1)
	{
		while((FLASH->SR&FLASH_SR_BSY) != FLASH_SR_BSY);
		*(uint32_t*)(addr + i*4) = (uint32_t)data[i];
	}
	while((FLASH->SR&FLASH_SR_BSY)){};
	FLASH->CR &= ~FLASH_CR_PG;
	FLASH->CR |= FLASH_CR_LOCK;
}

void STM32Flash::flashReadChar(char* dataOut, uint32_t addr1, uint32_t addr2)
{
	int check = 0;
	deleteBuffer(dataOut);
	if((unsigned char)flashReadInt(addr2+(uint32_t)2) == 255)
	{
		check = (unsigned char)flashReadInt(addr2)-48;
	}
	else
	{
		check = ((unsigned char)flashReadInt(addr2)-48)*10 + (unsigned char)flashReadInt(addr2+2)-48;
	}
	for(int i = 0; i < check; i++)
	{
		dataOut[i] = flashReadInt(addr1 + (uint32_t)(i*2));
	}
}

void STM32Flash::flashProgramPage(char* dataIn, uint32_t addr1, uint32_t addr2)
{
//	//FLASH_Unlock
//	Flash_Unlock();
//	//Flash_Erase Page
//	Flash_Erase(addr1);
//	//FLASH_Program HalfWord
//	Flash_Write_Char(addr1, dataIn);
//	HAL_Delay(100);
//	char tempbuf[5] = {0};
//	sprintf(tempbuf, "%d", lengthPage);
//	//FLASH_Unlock
//	Flash_Unlock();
//	//Flash_Erase Page
//	Flash_Erase(addr2);
//	//FLASH_Program HalfWord
//	Flash_Write_Char(addr2,tempbuf);
}
