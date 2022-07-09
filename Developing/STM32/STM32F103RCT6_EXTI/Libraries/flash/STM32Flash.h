/*
 * STM32Flash.h
 *
 *  Created on: Apr 24, 2021
 *      Author: quoclaptk
 */

#ifndef _STM32FLASH_H_
#define _STM32FLASH_H_

#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "string.h"

class STM32Flash {
public:
	STM32Flash();
	virtual ~STM32Flash();
	void deleteBuffer(char* data);
	void flashLock(void);
	void flashUnlock(void);
	void flashErase(uint32_t addr);
	void flashWriteInt(uint32_t addr, int data);
	uint16_t flashReadInt(uint32_t addr);
	void flashWriteDword(uint32_t addr, uint32_t* data, uint8_t size);
	void flashReadChar(char* dataOut, uint32_t addr1, uint32_t addr2);
	void flashProgramPage(char* dataIn, uint32_t addr1, uint32_t addr2);
};

#endif /* _STM32FLASH_H_ */
