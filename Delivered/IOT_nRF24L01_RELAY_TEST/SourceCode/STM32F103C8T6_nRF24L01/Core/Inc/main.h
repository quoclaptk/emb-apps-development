/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <string.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
static __inline__ void delayMicroseconds(uint32_t u32Usec)
{
	uint32_t startTick = SysTick->VAL;
	uint32_t delayTicks = u32Usec*(SystemCoreClock/1000000);
	while (SysTick->VAL - startTick < delayTicks);
}
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CE_Pin GPIO_PIN_0
#define CE_GPIO_Port GPIOB
#define CSN_Pin GPIO_PIN_2
#define CSN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define byte uint8_t
#define LOW false
#define HIGH true
#define delay(x) HAL_Delay(x) /* delay x ms */
#define PROGMEM
#define _BV(x) (1<<(x))
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
extern uint32_t millis();
extern void ce(bool level);
extern void csn(bool level);
extern uint8_t spiWrite(uint8_t data);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
