/*
 * GPIO.c
 *
 *  Created on: Feb 20, 2022
 *      Author: ADMIN
 */

#include"stm32f1xx.h"





void GPIO_Set_Port(uint32_t PORT){
	RCC->APB2ENR |= (uint32_t)(1<<PORT);
}

void GPIO_Set_Pin(uint32_t PORT,uint32_t Pin){
	uint32_t CNFH = (Pin-8)*4;
	uint32_t CNFL = Pin*4;
	switch(PORT){
	// GPIOA
	case 2:
		if((Pin>7) && (Pin<15)){
		GPIOA->CRH &= ~(3<<CNFH); /* clear bit Mode */
		GPIOA->CRH |= (1<<CNFH); /*  max speed 10MHz */
		}
		if((Pin<7)){
		GPIOA->CRL &= ~(3<<CNFL); /* clear bit Mode */
		GPIOA->CRL |= (1<<CNFL); /* max speed 10 MHz */
		}
		break;
	// GPIOB
	case 3:
		if((Pin>7) && (Pin<15)){
		GPIOB->CRH &= ~(3<<CNFH); /* clear bit Mode */
		GPIOB->CRH |= (1<<CNFH); /*  max speed 10MHz */
		}
		if((Pin<7)){
		GPIOB->CRL &= ~(3<<CNFL); /* clear bit Mode */
		GPIOB->CRL |= (1<<CNFL); /* max speed 10 MHz */
		}
		break;
	// GPIOC
	case 4:
		if((Pin>7) && (Pin<15)){
		GPIOC->CRH &= ~(3<<CNFH); /* clear bit Mode */
		GPIOC->CRH |= (1<<CNFH); /*  max speed 10MHz */
		}
		if((Pin<7)){
		GPIOC->CRL &= ~(3<<CNFL); /* clear bit Mode */
		GPIOC->CRL |= (1<<CNFL); /* max speed 10 MHz */
		}
		break;
	case 5:
		if((Pin>7) && (Pin<15)){
		GPIOE->CRH &= ~(3<<CNFH); /* clear bit Mode */
		GPIOE->CRH |= (1<<CNFH); /*  max speed 10MHz */
		}
		if((Pin<7)){
		GPIOE->CRL &= ~(3<<CNFL); /* clear bit Mode */
		GPIOE->CRL |= (1<<CNFL); /* max speed 10 MHz */
		}
		break;
	}


}
void GPIO_Set_Mode(uint32_t GPIO_Mode,uint32_t PORT,uint32_t Pin){
	uint32_t  Mode_H = (Pin-8)*4;
	uint32_t Mode_L =  Pin*4;

	switch(PORT){

	case 2:
		if(GPIO_Mode==0){
			if((Pin>7) && (Pin<15)){

				GPIOA->CRH &= ~(3<<Mode_H); /* clear bit */
				GPIOA->CRH |= (2<<Mode_H); /* General purpose Open-drain */
			}
			else{
				GPIOA->CRL &= ~(3<<Mode_L); /* clear bit */
				GPIOA->CRL |= (2<<Mode_L); /* General purpose Open-drain */
			}

		}
		if(GPIO_Mode==1){

			if((Pin>7) && (Pin<15)){

				GPIOA->CRH &= ~(3<<Mode_H); /* clear bit  */
				GPIOA->CRH |= (1<<Mode_H); /* General purpose output Open-drain */
			}
			else{
				GPIOA->CRL &= ~(3<<Mode_L); /* clear bit  */
				GPIOA->CRL |= (1<<Mode_L); /* General purpose output Open-drain */
			}
		}

		break;
	case 3:
		if(GPIO_Mode==0){
			if((Pin>7) && (Pin<15)){

				GPIOB->CRH &= ~(3<<Mode_H); /* clear bit */
				GPIOB->CRH |= (2<<Mode_H); /* General purpose Open-drain */
			}
			else{
				GPIOB->CRL &= ~(3<<Mode_L); /* clear bit */
				GPIOB->CRL |= (2<<Mode_L); /* General purpose Open-drain */
			}

		}
		if(GPIO_Mode==1){

			if((Pin>7) && (Pin<15)){

				GPIOB->CRH &= ~(3<<Mode_H); /* clear bit  */
				GPIOB->CRH |= (1<<Mode_H); /* General purpose output Open-drain */
			}
			else{
				GPIOB->CRL &= ~(3<<Mode_L); /* clear bit  */
				GPIOB->CRL |= (1<<Mode_L); /* General purpose output Open-drain */
			}
		}

		break;
	case 4:
		if(GPIO_Mode==0){
			if((Pin>7) && (Pin<15)){

				GPIOC->CRH &= ~(3<<Mode_H); /* clear bit */
				GPIOC->CRH |= (2<<Mode_H); /* General purpose Open-drain */
			}
			else{
				GPIOC->CRL &= ~(3<<Mode_L); /* clear bit */
				GPIOC->CRL |= (2<<Mode_L); /* General purpose Open-drain */
			}

		}
		if(GPIO_Mode==1){

			if((Pin>7) && (Pin<15)){

				GPIOC->CRH &= ~(3<<Mode_H); /* clear bit  */
				GPIOC->CRH |= (1<<Mode_H); /* General purpose output Open-drain */
			}
			else{
				GPIOC->CRL &= ~(3<<Mode_L); /* clear bit  */
				GPIOC->CRL |= (1<<Mode_L); /* General purpose output Open-drain */
			}
		}

		break;
	case 5:
		if(GPIO_Mode==0){
			if((Pin>7) && (Pin<15)){

				GPIOD->CRH &= ~(3<<Mode_H); /* clear bit */
				GPIOD->CRH |= (2<<Mode_H); /* General purpose Open-drain */
			}
			else{
				GPIOD->CRL &= ~(3<<Mode_L); /* clear bit */
				GPIOD->CRL |= (2<<Mode_L); /* General purpose Open-drain */
			}

		}
		if(GPIO_Mode==1){

			if((Pin>7) && (Pin<15)){

				GPIOD->CRH &= ~(3<<Mode_H); /* clear bit  */
				GPIOD->CRH |= (1<<Mode_H); /* General purpose output Open-drain */
			}
			else{
				GPIOD->CRL &= ~(3<<Mode_L); /* clear bit  */
				GPIOD->CRL |= (1<<Mode_L); /* General purpose output Open-drain */
			}
		}

		break;
	case 6:
		if(GPIO_Mode==0){
			if((Pin>7) && (Pin<15)){

				GPIOE->CRH &= ~(3<<Mode_H); /* clear bit */
				GPIOE->CRH |= (2<<Mode_H); /* General purpose Open-drain */
			}
			else{
				GPIOE->CRL &= ~(3<<Mode_L); /* clear bit */
				GPIOE->CRL |= (2<<Mode_L); /* General purpose Open-drain */
			}

		}
		if(GPIO_Mode==1){

			if((Pin>7) && (Pin<15)){

				GPIOE->CRH &= ~(3<<Mode_H); /* clear bit  */
				GPIOE->CRH |= (1<<Mode_H); /* General purpose output Open-drain */
			}
			else{
				GPIOE->CRL &= ~(3<<Mode_L); /* clear bit  */
				GPIOE->CRL |= (1<<Mode_L); /* General purpose output Open-drain */
			}
		}

		break;

	}

}
void GPIO_SET(uint32_t PORT,uint32_t PIN){
	switch(PORT){
	case 2:
		GPIOA->ODR |=(1<<PIN);
		break;
	case 3:
		GPIOB->ODR |=(1<<PIN);
		break;
	case 4:
		GPIOC->ODR |=(1<<PIN);
		break;
	case 5:
		GPIOD->ODR |=(1<<PIN);
		break;
	case 6:
		GPIOE->ODR |=(1<<PIN);
		break;
	}

}
void GPIO_RESET(uint32_t PORT,uint32_t PIN){
	switch(PORT){
	case 2:
		GPIOA->ODR &= ~(1<<PIN);
		break;
	case 3:
		GPIOB->ODR &= ~(1<<PIN);
		break;
	case 4:
		GPIOC->ODR &= ~(1<<PIN);
		break;
	case 5:
		GPIOD->ODR &= ~(1<<PIN);
		break;
	case 6:
		GPIOE->ODR &= ~(1<<PIN);
		break;
	}

}
void GPIO_init(uint32_t GPIOx,uint32_t GPIO_Pin,uint32_t Mode){

//Set GPIO PORT ************************

	GPIO_Set_Port(GPIOx);
//Set PIN  ************************

	GPIO_Set_Pin(GPIOx,GPIO_Pin);

//Set Mode ************************
	GPIO_Set_Mode(Mode,GPIOx,GPIO_Pin);
}


