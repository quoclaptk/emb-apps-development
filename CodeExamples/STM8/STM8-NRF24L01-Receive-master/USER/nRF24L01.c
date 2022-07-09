/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� **************
 * �ļ���  ��nRF24L01.c
 * ����    ��nRF24L01����ģ��ʵ��   
 * ʵ��ƽ̨�����STM8������
 * ��汾  ��V2.1.0
 * ����    �����  QQ��779814207
 * ����    ��
 * �Ա�    ��http://shop71177993.taobao.com/
 * �޸�ʱ�� ��2012-12-23

  ���STM8������Ӳ������
    |----------------------------|
	|  CE  - PI0             	 |
	|  SPI_CLK - PC5(SPI+SCK)	 |
    |  SPI_MOSI - PC6(SPI_MOSI)  |
    |  SPI_MISO - PC7(SPI_MISO)  |
	|  CSN - PC1             	 |
	|  IRQ - PC2             	 |
    |----------------------------|

*******************************************************************************/

/* ����ϵͳͷ�ļ� */

/* �����Զ���ͷ�ļ� */
#include "stm8s.h"
#include "uart1.h"
#include "nRF24L01.h"

/* �Զ��������� */

/* �Զ���� */

/* ȫ�ֱ������� */

u8  TxAddr[]={0x34,0x43,0x10,0x10,0x01};//���͵�ַ

/* һ���򵥵���ʱ���� */
void Delay(u32 cnt)
{
	u32 i;
	
	for (; cnt > 0; cnt--) {
		for (i = 0; i < 3000; i++)
			;
	}
}

/*******************************************************************************
 * ����: NRF24L01_Pin_Conf
 * ����: nRF24L01�������ų�ʼ����SPIģ���ʼ��
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void nRF24L01_Pin_Conf()
{
	/* ��ʼ��SPI--��λ��ǰ��6M, ��ģʽ��SCK����Ϊ�͵�ƽ����һ�����زɼ����� */
	SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_4, SPI_MODE_MASTER,\
				SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE, \
				SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x07);
	
	SPI_Cmd(ENABLE);	/* ʹ��SPI */
	
	GPIO_Init(GPIOC, CSN, GPIO_MODE_OUT_PP_HIGH_FAST);	/* CSN���ų�ʼ��Ϊ��� */
	GPIO_Init(GPIOI, CE, GPIO_MODE_OUT_PP_HIGH_FAST);	/* CE���ų�ʼ��Ϊ��� */
}


/*******************************************************************************
 * ����: nRF24L01_SPI_RW
 * ����: nRF24L01 SPIģʽ�¶�д��������
 * �β�: data -> ҪдnRF24L01������
 * ����: nRF24L01���ص�����
 * ˵��: �� 
 ******************************************************************************/
static u8 nRF24L01_SPI_RW(u8 date)
{
	/* �ȴ�DR�Ĵ����ǿ� */
	while (SPI_GetFlagStatus( SPI_FLAG_TXE) == RESET);
	
	/* ͨ��SPI����һ���ֽ� */
	SPI_SendData(date);
	
	/* �ȴ�����һ���ֽ� */
	while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
	
	/* ����SPI�����ϵ��ֽ� */
	return SPI_ReceiveData();  
}

/*******************************************************************************
 * ����: nRF24L01_Read_Reg
 * ����: ��ȡnRF24L01�Ĵ�������
 * �β�: RegAddr -> nRF24L01�Ĵ�����ַ
 * ����: nRF24L01���ص�����
 * ˵��: �� 
 ******************************************************************************/
static u8 nRF24L01_Read_Reg(u8 RegAddr)
{
   u8 BackData;
   
   ClrCSN;							/* ����ʱ�� */
   nRF24L01_SPI_RW(RegAddr);		/* д�Ĵ�����ַ */
   BackData = nRF24L01_SPI_RW(0x00);	/* д����Ĵ���ָ�� */ 
   SetCSN;
   
   return(BackData); 				/* ����״ֵ̬ */
}

/*******************************************************************************
 * ����: nRF24L01_Write_Reg
 * ����: ��nRF24L01�Ĵ���д���ݺ���
 * �β�: RegAddr -> nRF24L01�Ĵ�����ַ
 *		 data -> д��Ĵ���������
 * ����: nRF24L01���ص�����
 * ˵��: �� 
 ******************************************************************************/
static u8 nRF24L01_Write_Reg(u8 RegAddr,u8 data)
{
   u8 BackData;
   
   ClrCSN;						/* ����ʱ�� */
   BackData = nRF24L01_SPI_RW(RegAddr);	/* д���ַ */
   nRF24L01_SPI_RW(data);				/* д��ֵ */
   SetCSN;
   
   return(BackData);
}

/*******************************************************************************
 * ����: nRF24L01_Write_Reg
 * ����: ��ȡnRF24L01RX FIFO�����ݺ���
 * �β�: RegAddr -> nRF24L01�Ĵ�����ַ
 *		 Rxdata -> ָ������������ָ��
 * 	     DataLen -> ���ݳ���
 * ����: nRF24L01���ص�����
 * ˵��: ����ģʽ��ʹ��
 ******************************************************************************/
static u8 nRF24L01_Read_RxData(u8 RegAddr, u8 *RxData, u8 DataLen)
{ 
	u8 BackData,i;
	
	ClrCSN;									/* ����ʱ�� */
	BackData = nRF24L01_SPI_RW(RegAddr);	/* д��Ҫ��ȡ�ļĴ�����ַ */
	for(i = 0; i < DataLen; i++) 			/* ��ȡ���� */
	{
		RxData[i] = nRF24L01_SPI_RW(0);
	} 
	
	SetCSN;
	
	return(BackData); 
}

/*******************************************************************************
 * ����: nRF24L01_Write_TxData
 * ����: д��nRF24L01TX FIFO�����ݺ���
 * �β�: RegAddr -> nRF24L01�Ĵ�����ַ
 *		 Rxdata -> ָ��Ҫд�����ݵ�ָ��
 * 	     DataLen -> ���ݳ���
 * ����: nRF24L01���ص�����
 * ˵��: ����ģʽ��ʹ��
 ******************************************************************************/
static u8 nRF24L01_Write_TxData(u8 RegAddr,u8 *TxData,u8 DataLen)
{ 
	u8 BackData,i;
	
	ClrCSN;
	BackData = nRF24L01_SPI_RW(RegAddr);	/* д��Ҫд��Ĵ����ĵ�ַ */
	for(i = 0; i < DataLen; i++)			/* д������ */
	{
		nRF24L01_SPI_RW(*TxData++);
	}   
	
	SetCSN;
	return(BackData);
}

/*******************************************************************************
 * ����: nRF24L01_Set_RxMode
 * ����: ��nRF24L01TX FIFO����Ϊ����ģʽ
 * �β�: ��
 * ����: ��
 * ˵��: 
 ******************************************************************************/
void nRF24L01_Set_RxMode()
{
	ClrCE; 
	/* �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ */
  	nRF24L01_Write_TxData(W_REGISTER+RX_ADDR_P0, TxAddr, TX_ADDR_WITDH);  
	
	/******�����йؼĴ�������**************/
  	nRF24L01_Write_Reg(W_REGISTER+EN_AA,0x01);       /* ʹ�ܽ���ͨ��0�Զ�Ӧ�� */
  	nRF24L01_Write_Reg(W_REGISTER+EN_RXADDR,0x01);   /* ʹ�ܽ���ͨ��0 */
  	nRF24L01_Write_Reg(W_REGISTER+RF_CH,0x40);       /* ѡ����Ƶͨ��0x40 */
	nRF24L01_Write_Reg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);  /* ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ�� */
  	nRF24L01_Write_Reg(W_REGISTER+RF_SETUP,0x07);    /* ���ݴ�����1Mbps�����书��0dBm���������Ŵ������� */
	nRF24L01_Write_Reg(W_REGISTER+CONFIG,0x0f);      /* CRCʹ�ܣ�16λCRCУ�飬�ϵ� */ 
	SetCE;
	Delay(5);	/* ����оƬ�ֲ�Ҫ�� ����10us������ */
  
}

/*******************************************************************************
 * ����: nRF24L01_RevData
 * ����: �������ݺ���
 * �β�: RevData -> ָ�������ݻ�����
 * ����: 1--��������ʧ�ܣ�0--�������ݳɹ�
 * ˵��: 
 ******************************************************************************/
u8 nRF24L01_RevData(u8 *RevData)
{
	u8 RevFlags = 1;
	u8 sta;
	
	sta = nRF24L01_Read_Reg(R_REGISTER+STATUS);	/* ��ȡ״̬�Ĵ�����ֵ */
	if(sta & 0x40)				/* �ж��Ƿ���յ����� */
	{
		ClrCE; 			
		nRF24L01_Read_RxData(R_RX_PAYLOAD,RevData,RX_DATA_WITDH);	/* ��RXFIFO��ȡ4λ���� */
		
		/* ���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־ */
		nRF24L01_Write_Reg(W_REGISTER+STATUS,0xff); 
		
		ClrCSN;
	   	nRF24L01_SPI_RW(FLUSH_RX);	/* �������FIFO */
	   	SetCSN;	
		
		RevFlags = 0;	   
	}
	
	return(RevFlags);
}

/*************************��������*********************************************/
void GetDate(u8 *data)				 
{
  u8 sta;
    sta=nRF24L01_Read_Reg(R_REGISTER+STATUS);//�������ݺ��ȡ״̬�Ĵ���
    if(sta&0x40)				// �ж��Ƿ���յ�����
     {
	   ClrCE;//CE=0;//����
	   nRF24L01_Read_RxData(R_RX_PAYLOAD,data,RX_DATA_WITDH);// ��RXFIFO��ȡ���� ����4λ���ɣ���һλλ����λ
	   
	  
	   nRF24L01_Write_Reg(W_REGISTER+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�
	   ClrCSN;//CSN=0;
	   nRF24L01_SPI_RW(FLUSH_RX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס���� 
	   SetCSN;//CSN=1;		
	   UART1_SendString(data, 4);
	   
     }
    //NRFWriteReg(W_REGISTER+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�	  
}