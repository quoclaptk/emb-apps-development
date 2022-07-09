#include "stm32f1xx.h"
#include "Clock.h"
#include "GPIO.h"
#include "Timer.h"

void time(uint32_t t)
{
	while(t--);
}

int main()
{

	*(uint32_t*)(0x40021000 + 0x4) = 3<<2; //RCC->CFGR
	//HSE_PLL_Clock_init(6);
	HSE_72MHz_Init();
//	rcc_HSE_Configuration();
	SystemCoreClockUpdate();

	GPIO_init(GPIO_A,PIN1,GPIO_OUT);

	Timer4_init();
	Timer4_PWM(1, 20);
	while(1){
		GPIO_SET(GPIO_A,PIN1);
		time(0XFF);
		GPIO_RESET(GPIO_A,PIN1);
		time(0XFF);
		//GPIO_TypeDef *IOA = GPIOA;

	}
}
