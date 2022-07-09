/*
 * userConf.h
 *
 *  Created on: Mar 11, 2022
 *      Author: quocl
 */

#ifndef _USERCONF_H_
#define _USERCONF_H_
#include <stdio.h>
#include "Mini58Series.h"
#include <stdbool.h>

#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, BitStatus, BitAction;
#define delay(x) TIMER_Delay(TIMER1, x*1000); /* delay x ms */
#define delayMicroseconds(x) TIMER_Delay(TIMER1, x*10); /* delay x us */
#define delay_ms(x) delay(x)
#define delay_us(x) delayMicroseconds(x)
extern void masterTransmit(uint8_t addr, uint8_t *data, uint32_t size);
extern void masterReceive(uint8_t addr, uint8_t *data, uint32_t size);
extern void transmitData(uint8_t address, uint32_t data);

#endif /* USERCONF_H_ */
