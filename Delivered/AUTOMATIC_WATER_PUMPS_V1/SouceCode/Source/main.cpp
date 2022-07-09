/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.3.0
  * @date    16-June-2017
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#define ELEC_VALVE_1 0x01
#define ELEC_VALVE_2 0x02
#define ELEC_VALVE_3 0x04
#define ELEC_VALVE_4 0x08
#define ELEC_MOTOR 	 0x10

#define levelLowPort            GPIOB
#define levelLowPin             GPIO_PIN_4

#define levelHighPort           GPIOB
#define levelHighPin            GPIO_PIN_5

#define statusPort              GPIOC
#define statusPin               GPIO_PIN_3

#define PumpsControlPort        GPIOC
#define PumpsControlPin         GPIO_PIN_4

#define sosPort                 GPIOC
#define sosPin                  GPIO_PIN_5

#define runStatusPort           GPIOC
#define runStatusPin            GPIO_PIN_6

#define errStatusPort           GPIOC
#define errStatusPin            GPIO_PIN_7

static void InternalClockInit(void)
{
    CLK_DeInit();
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
    while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY)!=SET);
}

void GPIO_Init(void)
{
    GPIO_Init(levelLowPort, levelLowPin, GPIO_MODE_IN_PU_NO_IT); /* level Low status */
    GPIO_Init(levelHighPort, levelHighPin, GPIO_MODE_IN_PU_NO_IT); /* level High status */
    GPIO_Init(sosPort, sosPin, GPIO_MODE_IN_PU_NO_IT); /* sos request */
    GPIO_Init(statusPort, statusPin, GPIO_MODE_IN_PU_NO_IT);/* Pumps status */
    
    GPIO_Init(PumpsControlPort, PumpsControlPin, GPIO_MODE_OUT_PP_HIGH_FAST); /* Pumps control */
    GPIO_Init(runStatusPort, runStatusPin, GPIO_MODE_OUT_PP_HIGH_FAST); /* Led status for runing system */
    GPIO_Init(errStatusPort, errStatusPin, GPIO_MODE_OUT_PP_HIGH_FAST); /* Led status for error system */
    
    GPIO_WriteLow(errStatusPort, errStatusPin); /* Set default  */
}

void delay(uint32_t time)
{
    while(time--);
}

uint8_t ControlWaterPumps(BitStatus s1, BitStatus s2)
{
    if((s1 == RESET) && (s2 == RESET))
    {
            return 1; /* Enable water */
    }
    if((s1 != RESET) && (s2 != RESET))
    {
            return 0; /* Disable water */
    }
    return 2;
}

void GetSensorStatus(void)
{
    if(ControlWaterPumps(GPIO_ReadInputPin(levelLowPort, levelLowPin), GPIO_ReadInputPin(levelHighPort, levelHighPin)) != RESET)
    {
         /* Enable water pumps */
        GPIO_WriteHigh(PumpsControlPort, PumpsControlPin);
    }
    else if(ControlWaterPumps(GPIO_ReadInputPin(levelLowPort, levelLowPin), GPIO_ReadInputPin(levelHighPort, levelHighPin)) == RESET) /* Full */
    {
        /* Disable all */
        GPIO_WriteLow(PumpsControlPort, PumpsControlPin);
    }
}

void main(void)
{
    InternalClockInit();
    GPIO_Init();
    /* Infinite loop */
    while (1)
    {
        
        if(GPIO_ReadInputPin(sosPort, sosPin) != RESET) /* truong hop khan cap can bom */
        {
            GPIO_WriteHigh(PumpsControlPort, PumpsControlPin); /* Bom nuoc ko can dieu khien */
        }
        else  
        {
            GetSensorStatus();
        }
    }
  
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
