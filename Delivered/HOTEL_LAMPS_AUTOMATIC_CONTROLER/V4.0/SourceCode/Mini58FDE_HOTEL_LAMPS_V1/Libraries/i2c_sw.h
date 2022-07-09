#ifndef __I2C_SW_H
#define __I2C_SW_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes */
#include "main.h"
#include "stdio.h"

/* defines */
#define   SW_I2C1		1
#define   SW_I2C_SCL_PORT		P3
#define   SW_I2C_SDA_PORT		P3

#define   SW_I2C_SDA_PIN		P34
#define   SW_I2C_SCL_PIN		P35
#define   SW_I2C_SDA_BIT		BIT4
#define   SW_I2C_SCL_BIT		BIT5

//#define   SW_I2C_SCL_PORT		P2
//#define   SW_I2C_SDA_PORT		P2
//
//#define   SW_I2C_SDA_PIN		P25
//#define   SW_I2C_SCL_PIN		P24
//#define   SW_I2C_SDA_BIT		BIT5
//#define   SW_I2C_SCL_BIT		BIT4

#define  I2C_READ       0x01
#define  READ_CMD       1
#define  WRITE_CMD      0

/* functions */
void SW_I2C_initial(void);
void i2c_port_initial(uint8_t sel);		
uint8_t SW_I2C_ReadVal_SDA(uint8_t sel);
void SW_I2C_Write_Data(uint8_t sel, uint8_t data);
uint8_t SW_I2C_Read_Data(uint8_t sel);
uint8_t SW_I2C_WriteControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t data);
uint8_t SW_I2C_WriteControl_8Bit_OnlyRegAddr(uint8_t sel, uint8_t IICID, uint8_t regaddr);
uint8_t SW_I2C_WriteControl_16Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint16_t data);
uint8_t SW_I2C_ReadControl_8Bit_OnlyRegAddr(uint8_t sel, uint8_t IICID, uint8_t regaddr);
uint8_t SW_I2C_ReadControl_8Bit_OnlyData(uint8_t sel, uint8_t IICID);
uint16_t SW_I2C_ReadControl_16Bit_OnlyData(uint8_t sel, uint8_t IICID);
uint8_t SW_I2C_ReadControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr);
uint16_t SW_I2C_ReadControl_16Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr);
uint8_t SW_I2C_ReadnControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t rcnt, uint8_t (*pdata));
uint8_t SW_I2C_Multi_ReadnControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t rcnt, uint8_t (*pdata));
uint8_t SW_I2C_Check_SlaveAddr(uint8_t sel, uint8_t IICID);
uint8_t SW_I2C_UTIL_WRITE(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t data);
uint8_t SW_I2C_UTIL_Read(uint8_t sel, uint8_t IICID, uint8_t regaddr);
uint8_t SW_I2C_UTIL_Read_Multi(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t rcnt, uint8_t (*pdata));
uint8_t SW_I2C_UTIL_Write_Multi(uint8_t sel, uint8_t IICID, uint8_t *regaddr, uint8_t *pdata, uint8_t size);

#ifdef __cplusplus
}
#endif

#endif  /* __I2C_SW_H */
