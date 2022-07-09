#ifndef __I2C_SOFTWARE_GPIO_H__
#define __I2C_SOFTWARE_GPIO_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

//#define SDA_DIR_OUT()   GPIO_SetMode(P2, BIT4, GPIO_MODE_OUTPUT);
//#define SDA_DIR_IN()    GPIO_SetMode(P2, BIT4, GPIO_MODE_INPUT);
//#define SCL_DIR_OUT()   GPIO_SetMode(P2, BIT5, GPIO_MODE_OUTPUT);
//#define SCL_DIR_IN()    GPIO_SetMode(P2, BIT5, GPIO_MODE_INPUT);
//#define SDA_HIGH()      do{P24=1;}while(0)
//#define SDA_LOW()       do{P24=1;}while(0)
//#define SCL_HIGH()      set_P04
//#define SCL_LOW()       clr_P04
//#define SDA_IN()        P03
#define I2C_ACK         0xFF
#define I2C_NACK        0x00
#define I2C_timeout     1000
void SW_I2C_init(void);
void SW_I2C_start(void);
void SW_I2C_stop(void);
unsigned char SW_I2C_read(unsigned char ack);
void SW_I2C_write(unsigned char value);
void SW_I2C_ACK_NACK(unsigned char mode);
unsigned char SW_I2C_wait_ACK(void);

#ifdef __cplusplus
}
#endif
#endif
