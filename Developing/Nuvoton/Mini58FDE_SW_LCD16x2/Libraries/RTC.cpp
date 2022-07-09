/*
 * myRTC.cpp
 *
 *  Created on: Oct 16, 2021
 *      Author: quocl
 */

#include <RTC.h>

//static void (*masterTransmit)(uint8_t , uint8_t*, uint8_t );
//static void (*masterReceive)(uint8_t , uint8_t*, uint8_t );

myRTC::myRTC()
{
    // TODO Auto-generated constructor stub
//    memcpy(&masterTransmit, &transmit, sizeof(transmit));
//    memcpy(&masterReceive, &receive, sizeof(receive));
}

myRTC::~myRTC() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief Initializes the DS1307 module. Sets clock halt bit to 0 to start timing.
 * @param hi2c User I2C handle pointer.
 */
void myRTC::init()
{
    setClockHalt(0);
    setEnableSquareWave(DS1307_ENABLED);
    setInterruptRate(DS1307_1HZ);
}

/**
 * @brief Sets clock halt bit.
 * @param halt Clock halt bit to set, 0 or 1. 0 to start timing, 0 to stop.
 */
void myRTC::setClockHalt(uint8_t halt)
{
    uint8_t ch = (halt ? 1 << 7 : 0);
    setRegByte(DS1307_REG_SECOND, ch | (getRegByte(DS1307_REG_SECOND) & 0x7f));
}

/**
 * @brief Gets clock halt bit.
 * @return Clock halt bit, 0 or 1.
 */
uint8_t myRTC::getClockHalt(void)
{
    return (getRegByte(DS1307_REG_SECOND) & 0x80) >> 7;
}

/**
 * @brief Sets the byte in the designated DS1307 register to value.
 * @param regAddr Register address to write.
 * @param val Value to set, 0 to 255.
 */
void myRTC::setRegByte(uint8_t regAddr, uint8_t val)
{
    uint8_t bytes[2] = { regAddr, val };
    masterTransmit(DS1307_ADDR, bytes, 2);
}

/**
 * @brief Gets the byte in the designated DS1307 register.
 * @param regAddr Register address to read.
 * @return Value stored in the register, 0 to 255.
 */
uint8_t myRTC::getRegByte(uint8_t regAddr)
{
    uint8_t val;
    masterTransmit(DS1307_ADDR, &regAddr, 1);
    masterReceive(DS1307_ADDR, &val, 1);
    return val;
}

/**
 * @brief Toggle square wave output on pin 7.
 * @param mode DS1307_ENABLED (1) or DS1307_DISABLED (0);
 */
void myRTC::setEnableSquareWave(DS1307_SquareWaveEnable mode)
{
    uint8_t controlReg = getRegByte(DS1307_REG_CONTROL);
    uint8_t newControlReg = (controlReg & ~(1 << 4)) | ((mode & 1) << 4);
    setRegByte(DS1307_REG_CONTROL, newControlReg);
}

/**
 * @brief Set square wave output frequency.
 * @param rate DS1307_1HZ (0b00), DS1307_4096HZ (0b01), DS1307_8192HZ (0b10) or DS1307_32768HZ (0b11).
 */
void myRTC::setInterruptRate(DS1307_Rate rate)
{
    uint8_t controlReg = getRegByte(DS1307_REG_CONTROL);
    uint8_t newControlReg = (controlReg & ~0x03) | rate;
    setRegByte(DS1307_REG_CONTROL, newControlReg);
}

/**
 * @brief Gets the current day of week.
 * @return Days from last Sunday, 0 to 6.
 */
uint8_t myRTC::getDayOfWeek(void)
{
    return decodeBCD(getRegByte(DS1307_REG_DOW));
}

/**
 * @brief Gets the current day of month.
 * @return Day of month, 1 to 31.
 */
uint8_t myRTC::getDate(void)
{
    return decodeBCD(getRegByte(DS1307_REG_DATE));
}

/**
 * @brief Gets the current month.
 * @return Month, 1 to 12.
 */
uint8_t myRTC::getMonth(void)
{
    return decodeBCD(getRegByte(DS1307_REG_MONTH));
}

/**
 * @brief Gets the current year.
 * @return Year, 2000 to 2099.
 */
uint16_t myRTC::getYear(void)
{
    uint16_t cen = getRegByte(DS1307_REG_CENT) * 100;
    return decodeBCD(getRegByte(DS1307_REG_YEAR)) + cen;
}

/**
 * @brief Gets the current hour in 24h format.
 * @return Hour in 24h format, 0 to 23.
 */
uint8_t myRTC::getHour(void)
{
    return decodeBCD(getRegByte(DS1307_REG_HOUR) & 0x3f);
}

/**
 * @brief Gets the current minute.
 * @return Minute, 0 to 59.
 */
uint8_t myRTC::getMinute(void)
{
    return decodeBCD(getRegByte(DS1307_REG_MINUTE));
}

/**
 * @brief Gets the current second. Clock halt bit not included.
 * @return Second, 0 to 59.
 */
uint8_t myRTC::getSecond(void)
{
    return decodeBCD(getRegByte(DS1307_REG_SECOND) & 0x7f);
}

/**
 * @brief Gets the stored UTC hour offset.
 * @note  UTC offset is not updated automatically.
 * @return UTC hour offset, -12 to 12.
 */
int8_t myRTC::getTimeZoneHour(void)
{
    return getRegByte(DS1307_REG_UTC_HR);
}

/**
 * @brief Gets the stored UTC minute offset.
 * @note  UTC offset is not updated automatically.
 * @return UTC time zone, 0 to 59.
 */
uint8_t myRTC::getTimeZoneMin(void)
{
    return getRegByte(DS1307_REG_UTC_MIN);
}

/**
 * @brief Sets the current day of week.
 * @param dayOfWeek Days since last Sunday, 0 to 6.
 */
void myRTC::setDayOfWeek(uint8_t dayOfWeek)
{
    setRegByte(DS1307_REG_DOW, encodeBCD(dayOfWeek));
}

/**
 * @brief Sets the current day of month.
 * @param date Day of month, 1 to 31.
 */
void myRTC::setDate(uint8_t date)
{
    setRegByte(DS1307_REG_DATE, encodeBCD(date));
}

/**
 * @brief Sets the current month.
 * @param month Month, 1 to 12.
 */
void myRTC::setMonth(uint8_t month)
{
    setRegByte(DS1307_REG_MONTH, encodeBCD(month));
}

/**
 * @brief Sets the current year.
 * @param year Year, 2000 to 2099.
 */
void myRTC::setYear(uint16_t year)
{
    setRegByte(DS1307_REG_CENT, year / 100);
    setRegByte(DS1307_REG_YEAR, encodeBCD(year % 100));
}

/**
 * @brief Sets the current hour, in 24h format.
 * @param hour_24mode Hour in 24h format, 0 to 23.
 */
void myRTC::setHour(uint8_t hour_24mode)
{
    setRegByte(DS1307_REG_HOUR, encodeBCD(hour_24mode & 0x3f));
}

/**
 * @brief Sets the current minute.
 * @param minute Minute, 0 to 59.
 */
void myRTC::setMinute(uint8_t minute)
{
    setRegByte(DS1307_REG_MINUTE, encodeBCD(minute));
}

/**
 * @brief Sets the current second.
 * @param second Second, 0 to 59.
 */
void myRTC::setSecond(uint8_t second)
{
    uint8_t ch = getClockHalt();
    setRegByte(DS1307_REG_SECOND, encodeBCD(second | ch));
}

/**
 * @brief Sets UTC offset.
 * @note  UTC offset is not updated automatically.
 * @param hr UTC hour offset, -12 to 12.
 * @param min UTC minute offset, 0 to 59.
 */
void myRTC::setTimeZone(int8_t hr, uint8_t min)
{
    setRegByte(DS1307_REG_UTC_HR, hr);
    setRegByte(DS1307_REG_UTC_MIN, min);
}

/**
 * @brief Decodes the raw binary value stored in registers to decimal format.
 * @param bin Binary-coded decimal value retrieved from register, 0 to 255.
 * @return Decoded decimal value.
 */
uint8_t myRTC::decodeBCD(uint8_t bin)
{
    return (((bin & 0xf0) >> 4) * 10) + (bin & 0x0f);
}

/**
 * @brief Encodes a decimal number to binaty-coded decimal for storage in registers.
 * @param dec Decimal number to encode.
 * @return Encoded binary-coded decimal value.
 */
uint8_t myRTC::encodeBCD(uint8_t dec)
{
    return (dec % 10 + ((dec / 10) << 4));
}
