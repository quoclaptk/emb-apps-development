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

#define HCDATA 	P05
#define HCCLK 	P07
#define HCLAT 	P04

#define BUTTON_PIN1     P12
#define BUTTON_PIN2     P13
#define BUTTON_PIN3     P14
#define BUTTON_PIN4     P15
#define BUTTON_PIN5     P24

/* The define for time on/off */
#define ADDR_TIME_ON_RANGE_01         0x12
#define ADDR_TIME_OFF_RANGE_01        0x14
#define ADDR_TIME_ON_RANGE_02         0x16
#define ADDR_TIME_OFF_RANGE_02        0x18
#define ADDR_TIME_ON_RANGE_03         0x1A
#define ADDR_TIME_OFF_RANGE_03        0x1C
#define ADDR_TIME_ON_RANGE_04         0x1E
#define ADDR_TIME_OFF_RANGE_04        0x20
#define ADDR_TIME_ON_RANGE_05         0x22
#define ADDR_TIME_OFF_RANGE_05        0x24
#define ADDR_TIME_ON_RANGE_06         0x26
#define ADDR_TIME_OFF_RANGE_06        0x28
#define ADDR_TIME_ON_RANGE_07         0x2A
#define ADDR_TIME_OFF_RANGE_07        0x2C
#define ADDR_TIME_ON_RANGE_08         0x2E
#define ADDR_TIME_OFF_RANGE_08        0x30
#define ADDR_TIME_ON_RANGE_09         0x32
#define ADDR_TIME_OFF_RANGE_09        0x34
#define ADDR_TIME_ON_RANGE_10         0x36
#define ADDR_TIME_OFF_RANGE_10        0x38

typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define lampSet(value, bit) bitSet(value, bit+6)
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, BitStatus, BitAction;
#define delay(x) TIMER_Delay(TIMER1, x*1000); /* delay x ms */
#define delayMicroseconds(x) TIMER_Delay(TIMER1, x); /* delay x us */
#define delay_ms(x) delay(x)
#define delay_us(x) delayMicroseconds(x)
extern void masterTransmit(uint8_t addr, uint8_t *data, uint8_t size);
extern void masterReceive(uint8_t addr, uint8_t *data, uint8_t size);
extern void transmitData(uint8_t addr, uint8_t data);

#endif /* USERCONF_H_ */
