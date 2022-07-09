/*
 * Timer.c
 *
 *  Created on: Feb 20, 2022
 *      Author: ADMIN
 */

#include "stm32f1xx.h"

void Timer4_init(){

	RCC->APB1ENR |=( 1<<2); /* TIM4 timer clock enable */
	TIM4->CR1 |= (1<<7) |(1<<1); /* Counter enable,  Auto-reload preload enable */
	TIM4->PSC = 48-1;
	TIM4->ARR =100-1;
	TIM4->CR1 &= ~(1<<1);//Update register
	TIM4->EGR |=(1<<0);//Update generation
	TIM4->CR1 |= (1<<0);//enable  register 1
}
void Timer4_PWM(uint32_t Chanel,uint32_t PWM){
	/* PWM	 */
	TIM4->CCMR1 &= ~(7<<4);
	TIM4->CCMR1 |= (6<<4);
	TIM4->CCMR1 |= (1<<3);
	TIM4->CCER |= (1<<0);

//	switch(Chanel){
//	/*Chanel 1   */
//	case 1:
		TIM4->CCR1 = PWM;
		/* Enable clock for portB /PB6 */
		RCC->APB2ENR |= (1<<3);
		RCC->APB2ENR |= (1<<0);
		GPIOB->CRL &= ~(3<<24); /* clear bit 24, 25 */
		GPIOB->CRL|= (1<<24); /*SPEEED 10MHZ    */
		GPIOB->CRL &= ~(3<<26); /* clear bit 26, 27 */
		GPIOB->CRL |= (2<<26);/* Alternate function output Push-pul */
		AFIO->EVCR |= (1<<7);
		AFIO->MAPR &= ~(1<<12);/* TIMER 4 No remap */

//		break;
//		/*Chanel 2  */
//	case 2:
//		break;
//		/*Chanel 3   */
//	case 3:
//		break;
//		/*Chanel 4   */
//	case 4:
//		break;
//	 default:
//		 break;
//
//	}

}
