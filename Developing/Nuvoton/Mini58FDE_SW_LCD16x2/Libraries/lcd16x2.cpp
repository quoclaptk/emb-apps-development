/*******************************************************************************
** File Name   : lcd_driver.c
** Description : Source file for LCD Display
** Author      : Pham Van Lap
** Create Date : 23/03/2018
*******************************************************************************/
#include "lcd16x2.h"
/******************************************************************************/
//static void (*masterTransmit)(uint8_t address, uint8_t *data, uint8_t size);
//static void (*delay)(uint32_t us);
/******************************************************************************/
LCD::LCD()
{
//    memcpy(&masterTransmit, &transmit, sizeof(transmit));
//    memcpy(&delay, &delayUs, sizeof(delayUs));
}

LCD::~LCD(){}
/******************************************************************************/
void LCD::write4bits(uint8_t value)
{
    expanderWrite(value);
    pulseEnable(value);
}
/******************************************************************************/
void LCD::expanderWrite(uint8_t _data)
{
    uint8_t temp = (int)(_data);
    masterTransmit(LCD_ADDR, &temp, 1);
}
/******************************************************************************/
void LCD::pulseEnable(uint8_t _data)
{
    expanderWrite(_data | En);	// En high
    delay(1);		// enable pulse must be >450ns
    
    expanderWrite(_data & ~En);	// En low
    delay(50);		// commands need > 37us to settle
} 
/******************************************************************************/
void LCD::putCmd(unsigned char cmd)
{
    write4bits(cmd>>4);/* Gui 4 bit cao */
    write4bits(cmd); /* Gui 4 bit thap*/
}
/******************************************************************************/
void LCD::init()
{
    write4bits(0x00);
    delay(1000);
    write4bits(0x03);
    delay(2000);
    delay(800);
    write4bits(0x02);
    putCmd(0x28); // giao thuc 4 bit, hien thi 2 hang, ki tu 5x8
    putCmd(0x0c); // cho phep hien thi man hinh
    putCmd(0x06); // tang ID, khong dich khung hinh
    putCmd(0x01); // xoa toan bo khung hinh
}
/******************************************************************************/
void LCD::setCursor(unsigned char x, unsigned char y)
{
   unsigned char address;
   if(!y)address = (0x80+x);
   else address = (0xc0+x);
   delay(8);
   putCmd(address);
   delay(400);
}
/******************************************************************************/
void LCD::putChar(char data)
{
    putCmd(data);
}
/******************************************************************************/
void LCD::putChars(char *s)
{
    while(*s!='\0')
    {
        putChar(*s);
        s++;
    }
}
/******************************************************************************
********************************* END OF FILE *********************************
******************************************************************************/
