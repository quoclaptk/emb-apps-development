/*
 * swI2C.h
 *
 *  Created on: Oct 17, 2021
 *      Author: quocl
 */

#ifndef _SWI2C_H_
#define _SWI2C_H_

#include "main.h"

#define SDA_DIR_OUT()   GPIO_SetMode(PA, BIT9, GPIO_PMD_OUTPUT)
#define SDA_DIR_IN()    GPIO_SetMode(PA, BIT9, GPIO_PMD_INPUT)
#define SCL_DIR_OUT()   GPIO_SetMode(PA, BIT8, GPIO_PMD_OUTPUT)
#define SCL_DIR_IN()    GPIO_SetMode(PA, BIT8, GPIO_PMD_INPUT)
#define SDA_HIGH()      GPIO_SET_OUT_DATA(PA, 1<<0)
#define SDA_LOW()       GPIO_SET_OUT_DATA(PA, 0<<9)
#define SCL_HIGH()      GPIO_SET_OUT_DATA(PA, 1<<8)
#define SCL_LOW()       GPIO_SET_OUT_DATA(PA, 0<<8)
#define SDA_IN()        (GPIO_GET_IN_DATA(PA)&BIT9)>>9
#define I2C_ACK         0xFF
#define I2C_NACK        0x00
#define I2C_TIMEOUT     1000

class SWI2C {
public:
    SWI2C();
    virtual ~SWI2C();
    void init(void);
    void start(void);
    void stop(void);
    unsigned char read(unsigned char ack);
    void write(unsigned char value);
    void ack_nack(unsigned char mode);
    unsigned char wait_ack(void);
private:
    void sw_i2c_out(void);
    void sw_i2c_in(void);
    void sda_high(void);
    void sda_low(void);
    void scl_high(void);
    void scl_low(void);
    BitStatus sda_in(void);
};
#endif /* SWI2C_H_ */
