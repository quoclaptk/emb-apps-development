/*
 * myRTC.h
 *
 *  Created on: Oct 16, 2021
 *      Author: quocl
 */

#ifndef MYRTC_H_
#define MYRTC_H_

#include "main.h"
#include <string.h>

#define DS1307_ADDR 	    0x68
#define DS1307_REG_SECOND 	0x00
#define DS1307_REG_MINUTE 	0x01
#define DS1307_REG_HOUR  	0x02
#define DS1307_REG_DOW    	0x03
#define DS1307_REG_DATE   	0x04
#define DS1307_REG_MONTH  	0x05
#define DS1307_REG_YEAR   	0x06
#define DS1307_REG_CONTROL 	0x07
#define DS1307_REG_UTC_HR	0x08
#define DS1307_REG_UTC_MIN	0x09
#define DS1307_REG_CENT    	0x10
#define DS1307_REG_RAM   	0x11
#define DS1307_TIMEOUT		1000

typedef enum DS1307_Rate
{
	DS1307_1HZ, DS1307_4096HZ, DS1307_8192HZ, DS1307_32768HZ
} DS1307_Rate;

typedef enum DS1307_SquareWaveEnable
{
	DS1307_DISABLED, DS1307_ENABLED
} DS1307_SquareWaveEnable;

class myRTC {
public:
	myRTC();
	virtual ~myRTC();
	void init();
	void setClockHalt(uint8_t halt);
	uint8_t getClockHalt(void);
	void setRegByte(uint8_t regAddr, uint8_t val);
	uint8_t getRegByte(uint8_t regAddr);
	void setEnableSquareWave(DS1307_SquareWaveEnable mode);
	void setInterruptRate(DS1307_Rate rate);
	uint8_t getDayOfWeek(void);
	uint8_t getDate(void);
	uint8_t getMonth(void);
	uint16_t getYear(void);
	uint8_t getHour(void);
	uint8_t getMinute(void);
	uint8_t getSecond(void);
	int8_t getTimeZoneHour(void);
	uint8_t getTimeZoneMin(void);
	void setDayOfWeek(uint8_t dow);
	void setDate(uint8_t date);
	void setMonth(uint8_t month);
	void setYear(uint16_t year);
	void setHour(uint8_t hour_24mode);
	void setMinute(uint8_t minute);
	void setSecond(uint8_t second);
	void setTimeZone(int8_t hr, uint8_t min);
	uint8_t decodeBCD(uint8_t bin);
	uint8_t encodeBCD(uint8_t dec);
	void dsSramWrite(uint8_t addr, uint8_t *values, uint8_t nBytes);
};

#endif /* MYRTC_H_ */
