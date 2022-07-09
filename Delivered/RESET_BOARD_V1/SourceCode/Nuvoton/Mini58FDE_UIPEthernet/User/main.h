/*
 * main.h
 *
 *  Created on: Apr 15, 2022
 *      Author: quocl
 */

#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include "Mini58Series.h"
#include <stdbool.h>

extern uint32_t uwTick;

static __inline__ void millis_start(void) {
//    SysTick_Config(SystemCoreClock / 1000);
}

static __inline__ unsigned long millis(void) {
    return uwTick;
}

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))
extern void cs(bool level);
extern uint8_t spiWrite(uint8_t data);
#define delay(x) TIMER_Delay(TIMER1, x*1000); /* delay x ms */

#endif /* _MAIN_H_ */
