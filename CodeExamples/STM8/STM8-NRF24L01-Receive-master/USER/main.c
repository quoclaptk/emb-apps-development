/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� ***************
 * �ļ���  ��main.c
 * ����    ������ͨ�ų���     
 * ʵ��ƽ̨�����STM8������
 * ��汾  ��V2.1.0
 * ����    ��ling_guansheng QQ:779814207
 * ����    ��
 * �Ա�    ��http://shop71177993.taobao.com/
 * �޸�ʱ�� ��2012-12-22
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "sysclock.h"
#include "uart1.h"
#include "nRF24L01.h"


/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

int main(void)
{
  
	u8 RxBuf[32];
	
	/*�����ⲿ����24MΪ��ʱ��*/ 
	SystemClock_Init(HSE_Clock);
	
	Uart1_Init();
	
	
	nRF24L01_Pin_Conf();
	
	__enable_interrupt();	/* �������ж� */
	
	while(1)
	{ 
		
		nRF24L01_Set_RxMode();
		if (!(nRF24L01_RevData(RxBuf))) {
			UART1_SendString(RxBuf, 32);
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

/*************** (C) COPYRIGHT ���iCreateǶ��ʽ���������� *****END OF FILE****/