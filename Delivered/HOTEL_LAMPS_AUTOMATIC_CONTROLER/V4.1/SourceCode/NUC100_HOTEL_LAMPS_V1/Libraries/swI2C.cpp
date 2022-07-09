/*
 * SWI2C.cpp
 *
 *  Created on: Oct 17, 2021
 *      Author: quocl
 */
/******************************************************************************/
#include <swI2C.h>
/******************************************************************************/
SWI2C::SWI2C() {
	// TODO Auto-generated constructor stub

}

SWI2C::~SWI2C() {
	// TODO Auto-generated destructor stub
}
/******************************************************************************/
void SWI2C::sw_i2c_out()
{
    do
    {
    	SDA_DIR_OUT();
    	SCL_DIR_OUT();
    }while(0);
}
/******************************************************************************/
void SWI2C::sw_i2c_in()
{
    do
    {
    	SDA_DIR_IN();
    	SCL_DIR_OUT();
    }while(0);
}
/******************************************************************************/
void SWI2C::sda_high()
{
	SDA_HIGH();
}
/******************************************************************************/
void SWI2C::sda_low()
{
	SDA_LOW();
}
/******************************************************************************/
void SWI2C::scl_high()
{
	SCL_HIGH();
}
/******************************************************************************/
void SWI2C::scl_low()
{
	SCL_LOW();
}
/******************************************************************************/
BitStatus SWI2C::sda_in()
{
	if(SDA_IN())return SET;
	else return RESET;
}
/******************************************************************************/
void SWI2C::init(void)
{
    sw_i2c_out();
    delay_ms(10);
    sda_high();
    scl_high();
}
/******************************************************************************/
void SWI2C::start(void)
{
    sw_i2c_out();
    sda_high();
    scl_high();
    delay_us(40);
    sda_low();
    delay_us(40);
    scl_low();
}
/******************************************************************************/
void SWI2C::stop(void)
{
    sw_i2c_out();
    sda_low();
    scl_low();
    delay_us(40);
    sda_high();
    scl_high();
    delay_us(40);
}
/******************************************************************************/
unsigned char SWI2C::read(unsigned char ack)
{
    unsigned char i = 0x08;
    unsigned char j = 0x00;
    sw_i2c_in();
    while(i > 0x00)
    {
        scl_low();
        delay_us(20);
        scl_high();
        delay_us(20);
        j <<= 1;
        if(sda_in() != 0x00)
        {
            j++;
        }
        delay_us(10);
        i--;
    };

    switch(ack)
    {
        case I2C_ACK:
        {
            ack_nack(I2C_ACK);;
            break;
        }
        default:
        {
            ack_nack(I2C_NACK);;
            break;
        }
    }

    return j;
}
/******************************************************************************/
void SWI2C::write(unsigned char value)
{
    unsigned char i = 0x08;
    sw_i2c_out();
    scl_low();
    while(i > 0x00)
    {
        if(((value & 0x80) >> 0x07) != 0x00)sda_high();
        else sda_low();
        value <<= 1;
        delay_us(20);
        scl_high();
        delay_us(20);
        scl_low();
        delay_us(20);
        i--;
    }
}
/******************************************************************************/
void SWI2C::ack_nack(unsigned char mode)
{
    scl_low();
    sw_i2c_out();
    switch(mode)
    {
        case I2C_ACK:
        {
            sda_low();
            break;
        }
        default:
        {
            sda_high();
            break;
        }
    }
    delay_us(20);
    scl_high();
    delay_us(20);
    scl_low();
}
/******************************************************************************/
unsigned char SWI2C::wait_ack(void)
{
    signed int timeout = 0x0000;
    sw_i2c_in();
    sda_high();
    delay_us(10);
    scl_high();
    delay_us(10);
    while(sda_in() != 0x00)
    {
        timeout++;

        if(timeout > I2C_TIMEOUT)
        {
            SWI2C::stop();
            return 1;
        }
    };
    scl_low();
    return 0x00;
}
/******************************************************************************/
