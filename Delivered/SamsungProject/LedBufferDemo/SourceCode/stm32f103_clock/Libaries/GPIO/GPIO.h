/*
 * GPIO.h
 *
 *  Created on: Feb 20, 2022
 *      Author: ADMIN
 */

#ifndef _GPIO_H_
#define _GPIO_H_
#define GPIO_OUT 1
#define GPIO_IN 0

#define GPIO_A 2
#define GPIO_B 3
#define GPIO_C 4
#define GPIO_D 5
#define GPIO_E 6


#define PIN1  1
#define PIN2  2
#define PIN3  3
#define PIN4  4
#define PIN5  5
#define PIN6  6
#define PIN7  7
#define PIN8  8
#define PIN9  9
#define PIN10  10
#define PIN11  11
#define PIN12  12
#define PIN13  13
#define PIN14  14
#define PIN15  15


void GPIO_init(uint32_t GPIOx,uint32_t GPIO_Pin,uint32_t Mode);
void GPIO_SET(uint32_t PORT,uint32_t PIN);
void GPIO_RESET(uint32_t PORT,uint32_t PIN);

#endif /* GPIO_GPIO_H_ */
