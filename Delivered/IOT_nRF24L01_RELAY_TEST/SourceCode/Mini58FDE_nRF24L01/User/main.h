/*
 * main.h
 *
 *  Created on: Apr 21, 2022
 *      Author: quocl
 */

#ifndef MAIN_H_
#define MAIN_H_
#include <stdio.h>
#include "Mini58Series.h"
#include "string.h"


#define byte uint8_t
#define LOW false
#define HIGH true
#define delay(x) TIMER_Delay(TIMER1, x*1000) /* delay x ms */
#define delayMicroseconds(x) TIMER_Delay(TIMER1, x)
#define PROGMEM
#define _BV(x) (1<<(x))
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
extern uint32_t millis();
extern void ce(bool level);
extern void csn(bool level);
extern uint8_t spiWrite(uint8_t data);


#endif /* MAIN_H_ */
