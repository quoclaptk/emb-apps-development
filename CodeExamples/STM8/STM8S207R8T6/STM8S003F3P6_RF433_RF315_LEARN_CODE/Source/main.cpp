/**
  ******************************************************************************
  * @file    main.cpp
  * @author  PHAM VAN LAP
  * @version V1.0.0
  * @date    05-May-2021
  * @brief   
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
#include <RCSwitch.h>

/**
  * @addtogroup CLK_MaxSpeed
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define DATA_START_ADDRESS 0x4100 /* EEPROM base address */
/* Private variables ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void GPIO_Config(void);
static void CLK_Config(void);
static void TIM1_Config(void);
static void EXTI_Config(void);
void UpdateRemoteCode();
uint8_t GetPosition(uint32_t data);
void delay_ms(uint32_t ms);
/* Private functions ---------------------------------------------------------*/
RCSwitch mySwitch = RCSwitch();
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    disableInterrupts();
    CLK_Config();
    GPIO_Config();
    TIM1_Config(); 
    EXTI_Config();
    enableInterrupts();
    mySwitch.enableReceive(0);
    if(GPIO_ReadInputPin(UPDATE_PORT, UPDATE_PIN) == RESET)
    {
        GPIO_WriteHigh(LED_PORT, LED_PIN);
        UpdateRemoteCode();
        GPIO_WriteLow(LED_PORT, LED_PIN);
    }
    while (1)
    {
        if (mySwitch.available())
        {
            switch (GetPosition((uint32_t)mySwitch.getReceivedValue()))
            {
                case 0:
                    GPIO_WriteHigh(RELAY1_PORT, RELAY1_PIN);
                    delay_ms(DELAY_TIME);
                    break;
                case 1:
                    GPIO_WriteLow(RELAY1_PORT, RELAY1_PIN);
                    delay_ms(DELAY_TIME);
                    break;
                case 2:
                    GPIO_WriteHigh(RELAY2_PORT, RELAY2_PIN);
                    delay_ms(DELAY_TIME);
                    break;
                case 3:
                    GPIO_WriteLow(RELAY2_PORT, RELAY2_PIN);
                    delay_ms(DELAY_TIME);
                    break;
            }
            mySwitch.resetAvailable();
        }
    }
}
/******************************************************************************/
/**
  * @brief  UpdateRemoteCode
  * @param  None
  * @retval None
  */
/******************************************************************************/
void UpdateRemoteCode(void)
{
    uint8_t count = 4;
    uint32_t buff[4] = {0UL, 0UL, 0UL, 0UL}, varNew = 0;
    while((count>0)&&(GPIO_ReadInputPin(UPDATE_PORT, UPDATE_PIN) == RESET))
    {
        if(mySwitch.available())
        {
            varNew = (uint32_t)mySwitch.getReceivedValue();
            if(count==4) {buff[count-1] = varNew; count--;}
            else
            {
                if(buff[count] != varNew) 
                {
                    buff[count-1] = varNew;
                    count--;
                }
            }
            mySwitch.resetAvailable();
        }
    }
    /* Write new code to EEPROM */
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    for(uint8_t i=0; i<4; i++)
    {
        FLASH_ProgramWord(DATA_START_ADDRESS + i*4, buff[i]);
    }
    FLASH_Lock(FLASH_MEMTYPE_DATA);
}
/******************************************************************************/
/**
  * @brief  Get button position
  * @param  data need to check
  * @retval None
  */
/******************************************************************************/
uint8_t GetPosition(uint32_t data)
{
    for(uint8_t i=0; i<4; i++)
    {
        if( (*(uint32_t*)(DATA_START_ADDRESS + i*4)) == data)
        {
            return i;
        }
    }
    return 4;
}
/******************************************************************************/
/**
  * @brief  Configure GPIO for button available on the evaluation board
  * @param  None
  * @retval None
  */
/******************************************************************************/
static void GPIO_Config(void)
{
    GPIO_Init(RELAY1_PORT, RELAY1_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(RELAY2_PORT, RELAY2_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
    
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
    
    GPIO_Init(UPDATE_PORT, UPDATE_PIN, GPIO_MODE_IN_PU_NO_IT);
    
    GPIO_WriteLow(LED_PORT, LED_PIN);
}

void delay_ms(uint32_t ms)
{
    while(ms--);
}
/******************************************************************************/
/**
  * @brief  Configure system clock to run at Maximum clock speed and output the 
  *         system clock on CCO pin
  * @param  None
  * @retval None
  */
/******************************************************************************/
static void CLK_Config(void)
{
    //ErrorStatus status = ERROR;
    CLK_DeInit();
    /* Configure the Fcpu to DIV1*/
    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
    /* Configure the HSI prescaler to the optimal value */
    CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
    /* Output Fcpu on CLK_CCO pin */
    CLK_CCOConfig(CLK_OUTPUT_CPU);
    /* Configure the system clock to use HSE clock source and to run at 24Mhz */
    //status = CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
    
    //while (ButtonPressed == FALSE)
    //{
    //}
    /* Configure the system clock to use HSI clock source and to run at 16Mhz */
    //status = CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
    CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}
/******************************************************************************/
/**
  * @brief  Configure the TIM1 to delay function
  * @param  None
  * @retval None
  */
/******************************************************************************/
static void TIM1_Config(void)
{
    TIM1_DeInit();						// reset all resgister timer1
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, ENABLE);	// provide clock for timer1
    //TIM1_TimeBaseInit(15999,TIM1_COUNTERMODE_UP, 1000,0);     // config frequency interrupt PSC= 15999+1 =16000, ARR = 1000 -> F_interrupt = 16*10^6 / 16000/1000 = 1Hz = 1s
    TIM1_TimeBaseInit(159, TIM1_COUNTERMODE_UP, 1, 0);
    TIM1_ARRPreloadConfig(ENABLE);				// enable register auto reload active -  over counter -> reset counter
    TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);		        // ennable over inerrupt 
    TIM1_ClearFlag(TIM1_FLAG_UPDATE);	                        // clear flag over counter for firttime run
    TIM1_Cmd(ENABLE);						// enable timer active
}
/******************************************************************************/
/**
  * @brief  Configure the EXTI
  * @param  None
  * @retval None
  */
/******************************************************************************/
static void EXTI_Config(void)
{
    /* De-initialized external interrupt */
    EXTI_DeInit();
    GPIO_Init(RF_PORT, RF_PIN, GPIO_MODE_IN_PU_IT);
    /* External interrupt port D block, falling edge */
    EXTI_SetExtIntSensitivity(EXTI_PORT, EXTI_SENSITIVITY_RISE_FALL);
}
/******************************************************************************/
#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
