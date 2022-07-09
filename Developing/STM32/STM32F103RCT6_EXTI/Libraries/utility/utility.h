/*
 * utility.h
 *
 *  Created on: Apr 15, 2021
 *      Author: quoclaptk
 */

#ifndef _UTILITY_H_
#define _UTILITY_H_
#include <stm32f1xx_hal.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <pgmspace.h>

#define OUTPUT	2
#define INPUT_PULLUP 1

#define USE_LCD_ARDUINO
//#define USE_NRF24L01
//#define ARDUINO 100
#define USE_RCSWITCH

typedef enum {
	LOW,
	HIGH,
	CHANGE,
	RISING,
	FALLING,
}EventMode;

#ifndef word
typedef unsigned int word;
#endif
#ifndef _BV
#define _BV(x) (1<<(x))
#endif
#define delayMicroseconds(us) delay_us(us)

class Utility {
public:
	Utility();
	virtual ~Utility();
	void delayInit(void);
	void delay(uint32_t ms);
	void delay_us(uint32_t us);
	void delay_ms(uint32_t ms);
	uint32_t micros(void);
	uint32_t millis(void);
	void pinMode(uint16_t pin, uint8_t mode);
	bool digitalRead(uint16_t pin);
	void digitalWrite(uint16_t pin, bool level);
	uint8_t SPItransfer(uint8_t var);
	void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode);
	void detachInterrupt(uint8_t interruptNum);
	/***************************************************************************/
};

#endif /* _UTILITY_H_ */
