/*
 * nRF24L01_support.h
 *
 *  Created on: Mar 4, 2022
 *      Author: Admin
 */

#ifndef APPLICATION_USER_NRF24L01_SUPPORT_H_
#define APPLICATION_USER_NRF24L01_SUPPORT_H_

#include "main.h"

#ifdef USE_HAL_DRIVER

// Struct
typedef struct
{
	SPI_HandleTypeDef *SPI_UNIT;
	GPIO_TypeDef *CE_PORT;
	GPIO_TypeDef *CSN_PORT;
	uint16_t CE_PIN;
	uint16_t CSN_PIN;
	uint16_t IRQ_PIN;
	uint8_t DATA_SENT;
} nRF24_UNIT;

static inline void nRF24_CE_L(nRF24_UNIT *unit)
{
	HAL_GPIO_WritePin(unit->CE_PORT, unit->CE_PIN, GPIO_PIN_RESET);
}

static inline void nRF24_CE_H(nRF24_UNIT *unit)
{
    HAL_GPIO_WritePin(unit->CE_PORT, unit->CE_PIN, GPIO_PIN_SET);
}

static inline void nRF24_CSN_L(nRF24_UNIT *unit)
{
	HAL_GPIO_WritePin(unit->CSN_PORT, unit->CSN_PIN, GPIO_PIN_RESET);
}

static inline void nRF24_CSN_H(nRF24_UNIT *unit)
{
	HAL_GPIO_WritePin(unit->CSN_PORT, unit->CSN_PIN, GPIO_PIN_SET);
}

static inline void nRF24_Delay(uint32_t ms)
{
	HAL_Delay(ms);
}

static inline uint8_t nRF24_TransmitReceive(nRF24_UNIT *unit, uint8_t data)
{
    // Wait until TX buffer is empty
    uint8_t result;

    HAL_SPI_TransmitReceive(unit->SPI_UNIT, &data, &result, 1, 2000);

    return result;
}

static inline void nRF24_Register(nRF24_UNIT *unit, SPI_HandleTypeDef *hspi, GPIO_TypeDef *ce_port, GPIO_TypeDef *csn_port, uint16_t ce_pin, uint16_t csn_pin, uint16_t irq_pin)
{
	unit->SPI_UNIT = hspi;
	unit->CE_PORT = ce_port;
	unit->CSN_PORT = csn_port;
	unit->CE_PIN = ce_pin;
	unit->CSN_PIN = csn_pin;
	unit->IRQ_PIN = irq_pin;
	unit->DATA_SENT = 0;
}

static inline uint16_t nRF24_GetIRQPin(nRF24_UNIT *unit)
{
	return unit->IRQ_PIN;
}

#elif USE_FULL_LL_DRIVER

// Struct
typedef struct
{
	SPI_TypeDef *SPI_UNIT;
	GPIO_TypeDef *CE_PORT;
	GPIO_TypeDef *CSN_PORT;
	uint32_t CE_PIN;
	uint32_t CSN_PIN;
	uint32_t IRQ_PIN;
	uint8_t DATA_SENT;
} nRF24_UNIT;

static inline void nRF24_Register(nRF24_UNIT *unit, SPI_TypeDef *spi, GPIO_TypeDef *ce_port, GPIO_TypeDef *csn_port, uint32_t ce_pin, uint32_t csn_pin, uint32_t irq_pin)
{
	unit->SPI_UNIT = spi;
	unit->CE_PORT = ce_port;
	unit->CSN_PORT = csn_port;
	unit->CE_PIN = ce_pin;
	unit->CSN_PIN = csn_pin;
	unit->IRQ_PIN = irq_pin;
	unit->DATA_SENT = 0;
}

static inline uint32_t nRF24_GetIRQPin(nRF24_UNIT *unit)
{
	return unit->IRQ_PIN;
}

static inline uint8_t nRF24_TransmitReceive(nRF24_UNIT *unit, uint8_t data)
{
    LL_SPI_Enable(unit->SPI_UNIT);

    // Wait until TX buffer is empty
    while(LL_SPI_IsActiveFlag_BSY(unit->SPI_UNIT));
    while(!LL_SPI_IsActiveFlag_TXE(unit->SPI_UNIT));

    LL_SPI_TransmitData8(unit->SPI_UNIT, data);

    while(!LL_SPI_IsActiveFlag_RXNE(unit->SPI_UNIT));

    return LL_SPI_ReceiveData8(unit->SPI_UNIT);
}

static inline void nRF24_CE_L(nRF24_UNIT *unit)
{
    LL_GPIO_ResetOutputPin(unit->CE_PORT, unit->CE_PIN);
}

static inline void nRF24_CE_H(nRF24_UNIT *unit)
{
    LL_GPIO_SetOutputPin(unit->CE_PORT, unit->CE_PIN);
}

static inline void nRF24_CSN_L(nRF24_UNIT *unit)
{
    LL_GPIO_ResetOutputPin(unit->CSN_PORT, unit->CSN_PIN);
}

static inline void nRF24_CSN_H(nRF24_UNIT *unit)
{
    LL_GPIO_SetOutputPin(unit->CSN_PORT, unit->CSN_PIN);
}

static inline void nRF24_Delay(uint32_t ms)
{
	LL_mDelay(ms);
}

#else
/*
 * Write it yourself
 */
#endif

#endif /* APPLICATION_USER_NRF24L01_SUPPORT_H_ */
