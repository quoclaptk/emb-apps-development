/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 14/12/08 11:51a $
 * @brief    Software Development Template.
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <i2c_sw.h>
#include "main.h"
#include "LiquidCrystal_I2C.h"
#include "RTC.h"
//#include "RTClib.h"
#include "i2c_sw.h"

uint32_t uwTick = 0;
uint32_t ledTime = 0;
uint32_t myCount = 0;

/******************************************************************************/
typedef struct
{
   signed char s;
   signed char m;
   signed char h;
   signed char dy;
   signed char dt;
   signed char mt;
   uint16_t yr;
}myTime_t;

typedef struct _time_control
{
   signed char hr;
   signed char min;
}myTimeControl_t;

bool set = false, set_control = false, manualStatus = false;
unsigned char menu = 0, range = 0;
myTime_t time;
myTimeControl_t timeControl;
uint32_t controlDataOld = 0;

void writeControlLapms(uint32_t data);
static void display_time(void);
static void setup_time(void);
static void get_time(void);
static void set_time(void);
static void show_value(uint8_t x_pos, uint8_t y_pos, uint16_t value);
static uint16_t adjust(const uint8_t x_pos, const uint8_t y_pos, const uint16_t value_max, const uint16_t value_min, uint16_t value);
void setup_time_control(void);
void adjust_time_control(unsigned char x_pos, unsigned char y_pos, unsigned char ramAddr);
inline void set_ram(unsigned char ramAddr, unsigned char hr);
inline uint8_t read_ram(unsigned char ramAddr);
void runProgram(void);
//void change_lamps_status(uint32_t _controlData);

void SYS_Init(void)
{
	SYS_UnlockReg();
	CLK->APBCLK = CLK_APBCLK_TMR1CKEN_Msk;
	SystemCoreClockUpdate();
	SYS_LockReg();
}

void GPIO_Init()
{
	/* Set mode output for HC595 out data */
	GPIO_SetMode(P0, BIT4, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P0, BIT5, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P0, BIT7, GPIO_MODE_OUTPUT);
	/* Set mode output for LED Status */
	GPIO_SetMode(P2, BIT5, GPIO_MODE_OUTPUT);
	/* Set mode input for button */
	GPIO_SetMode(P1, BIT2, GPIO_MODE_INPUT);
	GPIO_SetMode(P1, BIT3, GPIO_MODE_INPUT);
	GPIO_SetMode(P1, BIT4, GPIO_MODE_INPUT);
	GPIO_SetMode(P1, BIT5, GPIO_MODE_INPUT);
	GPIO_SetMode(P2, BIT4, GPIO_MODE_INPUT);
}

extern "C" void SysTick_Handler(void)
{
	ledTime++;
	if(ledTime>500)
	{
		ledTime = 0;
		P25 ^= 1;
	}
	uwTick++;
}

const char *daysOfWeek[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
myRTC rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void writeControlLapms(uint32_t data)
{
    for(uint8_t i=0; i<32; i++)
    {
        if(((data>>i)&0x00000001)==0x00000001)HCDATA = 1;
        else HCDATA = 0;
        HCCLK = 1;
        HCCLK = 0;
    }
    HCLAT = 1;
    HCLAT = 0;
}

int main()
{
	time.s = 0;
	time.m = 16;
	time.h = 9;
	time.dy = 6;
	time.dt = 10;
	time.mt = 9;
	time.yr = 2022;
	SYS_UnlockReg();
	SYS_Init();
	GPIO_Init();
	SysTick_Config(SystemCoreClock/1000);/* 1ms increment for system timer */
	SW_I2C_initial();
	i2c_port_initial(SW_I2C1);
	rtc.init();
	lcd.init();
//	set_time();
	lcd.backlight();
	/* Set default lamps control */
//	set_ram(ADDR_TIME_ON_RANGE_01, 18);
//	set_ram(ADDR_TIME_OFF_RANGE_01, 6);
//
//	set_ram(ADDR_TIME_ON_RANGE_02, 0);
//	set_ram(ADDR_TIME_OFF_RANGE_02, 5);
//
//	set_ram(ADDR_TIME_ON_RANGE_03, 18);
//	set_ram(ADDR_TIME_OFF_RANGE_03, 12);

//	set_ram(ADDR_TIME_ON_RANGE_04, 3);
//	set_ram(ADDR_TIME_OFF_RANGE_04, 5);

//	set_ram(ADDR_TIME_ON_RANGE_05, 5);
//	set_ram(ADDR_TIME_OFF_RANGE_05, 6);
	while(1)
	{
		if((BUTTON_PIN1 == 0)&&(BUTTON_PIN2 == 0)&&(set == false)&&(set_control == false))
		{
			delay_ms(100);
			while(BUTTON_PIN1 == 0);
			menu = 0;
			set = true;
		}

		if((BUTTON_PIN1 == 0)&&(BUTTON_PIN3 == 0)&&(set == false)&&(set_control == false))
		{
			delay_ms(100);
			while(BUTTON_PIN3 == 0);
			range = 0;
			lcd.clear();
			set_control = true;
		}

		if((BUTTON_PIN4 == 0)&&(BUTTON_PIN5 == 0)&&(set == false)&&(set_control == false))
		{
			while(BUTTON_PIN4 == 0);
			delay_ms(100);
			manualStatus ^= 1;
			lcd.clear();
			lcd.setCursor(0, 0);
			if(manualStatus==1)lcd.print("ALL LAMPS IS ON");
		}

		if(set)setup_time();
		else if(set_control)setup_time_control();
		else
		{
			runProgram();
		}
	}
}
/******************************************************************************/
void display_time(void)
{
    char lcdBuff[16];
    lcd.setCursor(1, 0);
    if(time.dy>0)lcd.print(daysOfWeek[time.dy-1]);
    else lcd.print("---");
    sprintf(lcdBuff, " %02d/%02d/%04d", time.dt, time.mt, time.yr);
    lcd.print(lcdBuff);
    lcd.setCursor(3, 1);
    sprintf(lcdBuff, " %02d:%02d:%02d ", time.h, time.m, time.s);
    lcd.print(lcdBuff);
}
/******************************************************************************/
void setup_time(void)
{
    switch(menu)
    {
        case 0:{time.h = adjust(4, 1, 23, 0, time.h);}break;
        case 1:{time.m = adjust(7, 1, 59, 0, time.m);}break;
        case 2:{time.s = adjust(10, 1, 59, 0, time.s);}break;
        case 3:{time.dy = adjust(1, 0, 7, 1, time.dy);}break;
        case 4:{time.dt = adjust(5, 0, 31, 1, time.dt);}break;
        case 5:{time.mt = adjust(8, 0, 12, 1, time.mt);}break;
        case 6:{time.yr = adjust(11, 0, 2099, 2022, time.yr);}break;
    }
}
/******************************************************************************/
void setup_time_control(void)
{
    lcd.setCursor(3, 0);
    switch(range)
    {
        case 0x00:{lcd.print("RANGE_01_ON ");adjust_time_control(4, 1, ADDR_TIME_ON_RANGE_01);}break;
        case 0x01:{lcd.print("RANGE_01_OFF");adjust_time_control(4, 1, ADDR_TIME_OFF_RANGE_01);}break;
        case 0x02:{lcd.print("RANGE_02_ON ");adjust_time_control(4, 1, ADDR_TIME_ON_RANGE_02);}break;
        case 0x03:{lcd.print("RANGE_02_OFF");adjust_time_control(4, 1, ADDR_TIME_OFF_RANGE_02);}break;
        case 0x04:{lcd.print("RANGE_03_ON ");adjust_time_control(4, 1, ADDR_TIME_ON_RANGE_03);}break;
        case 0x05:{lcd.print("RANGE_03_OFF");adjust_time_control(4, 1, ADDR_TIME_OFF_RANGE_03);}break;
        case 0x06:{lcd.print("RANGE_04_ON ");adjust_time_control(4, 1, ADDR_TIME_ON_RANGE_04);}break;
        case 0x07:{lcd.print("RANGE_04_OFF");adjust_time_control(4, 1, ADDR_TIME_OFF_RANGE_04);}break;
        case 0x08:{lcd.print("RANGE_05_ON ");adjust_time_control(4, 1, ADDR_TIME_ON_RANGE_05);}break;
        case 0x09:{lcd.print("RANGE_05_OFF");adjust_time_control(4, 1, ADDR_TIME_OFF_RANGE_05);}break;
    }
}
/******************************************************************************/
uint16_t adjust(const uint8_t x_pos, const uint8_t y_pos, const uint16_t value_max, const uint16_t value_min, uint16_t value)
{
    if(menu<3)
    {
        lcd.setCursor(3, 1);
        lcd.print('<');
        lcd.setCursor(12, 1);
        lcd.print('>');
    }
    lcd.setCursor(x_pos, y_pos);
    if(menu==3)lcd.print("   "); // space for day of week name
    else if(menu==6)lcd.print("    "); // space for year
    else lcd.print("  "); // basic time
    delay_ms(200);
    if(menu == 3)
    {
        lcd.setCursor(x_pos, y_pos);
        lcd.print(daysOfWeek[time.dy-1]);
    }
    else show_value(x_pos, y_pos, value);
    delay_ms(200);

    if((BUTTON_PIN2 == 0)&&(set==true))
    {
        while(BUTTON_PIN2 == 0);
        menu++;
        if(menu > 6)
        {
            lcd.clear();
            set_time();
            set = false;
        }
    }
    if((BUTTON_PIN3 == 0)&&(set == true))
    {
        lcd.clear();
        set_time();
        set = false;
    }
    if((BUTTON_PIN4 == 0)&&(set == true))
	{
		if(value > value_min)value--;
		else value = value_max;
		delay_ms(100);
	}
    if((BUTTON_PIN5 == 0)&&(set == true))
    {
        value++;
        delay_ms(100);
        if(value > value_max)value = value_min;
    }

    return value;
}
/******************************************************************************/
void adjust_time_control(unsigned char x_pos, unsigned char y_pos, unsigned char ramAddr)
{
    if((BUTTON_PIN2 == 0) && (set_control==true))
    {
        delay_ms(100);
        while(BUTTON_PIN2 == 0);
        range++;if(range > 0x09){lcd.clear(); set_control = false;}
    }
    if((BUTTON_PIN3 == 0)&&(set_control == true))
    {
        lcd.clear(); set_control = false;
    }
    timeControl.hr = read_ram(ramAddr);
    if((BUTTON_PIN4 == 0)&&(set_control==true))/* down */
	{
		if(timeControl.hr>0)timeControl.hr--;
		else timeControl.hr=23;
		delay_ms(100);
		set_ram(ramAddr, timeControl.hr);
	}
    if((BUTTON_PIN5 == 0)&&(set_control==true))/* up */
    {
        timeControl.hr++;
        if(timeControl.hr>23)timeControl.hr = 0;
        delay_ms(100);
        set_ram(ramAddr, timeControl.hr);
    }
    char lcdBuff[16] = {0};
    sprintf(lcdBuff, ">>%02d:%02d<<", timeControl.hr, timeControl.min);
    lcd.setCursor(x_pos, x_pos);
    lcd.print(lcdBuff);
}
/******************************************************************************/
void set_time(void)
{
    rtc.setSecond(time.s);
    rtc.setMinute(time.m);
    rtc.setHour(time.h);
    rtc.setDayOfWeek(time.dy);
    rtc.setDate(time.dt);
    rtc.setMonth(time.mt);
    rtc.setYear(time.yr);
}
/******************************************************************************/
uint8_t read_ram(uint8_t ramAddr)
{
    return rtc.getRegByte(ramAddr);
}
/******************************************************************************/
void set_ram(uint8_t ramAddr, uint8_t data)
{
    rtc.setRegByte(ramAddr, data); /* save hour */
}
/******************************************************************************/
void show_value(uint8_t x_pos, uint8_t y_pos, uint16_t value)
{
    char valBuff[2];
    lcd.setCursor(x_pos, y_pos);
    if(value<100)sprintf(valBuff, "%02d", value);
    else if((value>=100) && (value<=255))sprintf(valBuff, "%03d", value);
    else sprintf(valBuff, "%04d", value);
    lcd.print(valBuff);
}
/******************************************************************************/
void get_time(void)
{
    time.s = rtc.getSecond();
    time.m = rtc.getMinute();
    time.h = rtc.getHour();
    time.dy = rtc.getDayOfWeek();
    time.dt = rtc.getDate();
    time.mt = rtc.getMonth();
    time.yr = rtc.getYear();
}
/******************************************************************************/
uint16_t convert_time_to_minute(uint8_t hour, uint8_t minute)
{
	return (hour*60 + minute);
}
/******************************************************************************/
void runProgram(void)
{
    uint32_t controlData = 0;
    uint8_t temp = 0;
    if(manualStatus==false)
    {
    	get_time(); display_time();
    	uint16_t curentTime = convert_time_to_minute(time.h, time.m);
    	if((time.h>=18) && (time.h<=23)) // Buoi toi
    	{
			if((curentTime >= convert_time_to_minute(18, 15))&&(curentTime <= convert_time_to_minute(23, 59)))
			{
				lampSet(controlData, 21); // den tang 1
				lampSet(controlData, 22); // den tang 2
			}
    	}
    	else if((time.h>=0) && (time.h<=6)) // dau sang
    	{
    		if((curentTime >= convert_time_to_minute(0, 0))&&(curentTime <= convert_time_to_minute(5, 30)))
			{
				lampSet(controlData, 21); // den tang 1
				lampSet(controlData, 23); // den cay
			}
    	}
    	else
		{
			controlData = 0x00000000;
		}
    }
    else /* check user manual before write */
    {
        controlData=0xFFFFFFFF;
    }
    /* Write to output */
    writeControlLapms(~controlData); /* write data to output */
}
/******************************************************************************/
/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
