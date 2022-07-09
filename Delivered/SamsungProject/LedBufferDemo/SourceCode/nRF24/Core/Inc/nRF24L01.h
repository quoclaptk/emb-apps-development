/*
 * nRF24L01.h
 *
 *  Created on: Mar 4, 2022
 *      Author: Admin
 */

#ifndef APPLICATION_USER_NRF24L01_H_
#define APPLICATION_USER_NRF24L01_H_

#include "nRF24L01_support.h"

// nRF24L0 instruction definitions
#define nRF24_CMD_R_REGISTER       		0b00000000 // Register read
#define nRF24_CMD_W_REGISTER       		0b00100000 // Register write
#define nRF24_CMD_R_RX_PAYLOAD     		0b01100001 // Read RX payload
#define nRF24_CMD_W_TX_PAYLOAD     		0b10100000 // Write TX payload
#define nRF24_CMD_FLUSH_TX         		0b11100001 // Flush TX FIFO
#define nRF24_CMD_FLUSH_RX         		0b11100010 // Flush RX FIFO
#define nRF24_CMD_REUSE_TX_PL      		0b11100011 // Reuse TX payload
#define nRF24_CMD_R_RX_PL_WID	   		0b01100000 // Read RX-payload width for the top R_RX_PAYLOAD in the RX FIFO.
#define nRF24_CMD_W_ACK_PAYLOAD    		0b10101000 // Write ACK payload
#define nRF24_CMD_W_TX_PAYLOAD_NOACK 	0b10110000 //Write TX payload and disable AUTOACK
#define nRF24_CMD_NOP              		0b11111111 // No operation (used for reading status register)
#define nRF24_CMD_FEATURE         		0b01010000 // (De)Activates R_RX_PL_WID, W_ACK_PAYLOAD, W_TX_PAYLOAD_NOACK features

// nRF24L0 register definitions
#define nRF24_REG_CONFIG           		0x00 // Configuration register
#define nRF24_REG_EN_AA            		0x01 // Enable "Auto acknowledgment"
#define nRF24_REG_EN_RXADDR        		0x02 // Enable RX addresses
#define nRF24_REG_SETUP_AW         		0x03 // Setup of address widths
#define nRF24_REG_SETUP_RETR       		0x04 // Setup of automatic retransmit
#define nRF24_REG_RF_CH            		0x05 // RF channel
#define nRF24_REG_RF_SETUP         		0x06 // RF setup register
#define nRF24_REG_STATUS           		0x07 // Status register
#define nRF24_REG_OBSERVE_TX       		0x08 // Transmit observe register
#define nRF24_REG_RPD              		0x09 // Received power detector
#define nRF24_REG_RX_ADDR_P0       		0x0A // Receive address data pipe 0
#define nRF24_REG_RX_ADDR_P1       		0x0B // Receive address data pipe 1
#define nRF24_REG_RX_ADDR_P2       		0x0C // Receive address data pipe 2
#define nRF24_REG_RX_ADDR_P3       		0x0D // Receive address data pipe 3
#define nRF24_REG_RX_ADDR_P4       		0x0E // Receive address data pipe 4
#define nRF24_REG_RX_ADDR_P5       		0x0F // Receive address data pipe 5
#define nRF24_REG_TX_ADDR          		0x10 // Transmit address
#define nRF24_REG_RX_PW_P0         		0x11 // Number of bytes in RX payload in data pipe 0
#define nRF24_REG_RX_PW_P1         		0x12 // Number of bytes in RX payload in data pipe 1
#define nRF24_REG_RX_PW_P2         		0x13 // Number of bytes in RX payload in data pipe 2
#define nRF24_REG_RX_PW_P3         		0x14 // Number of bytes in RX payload in data pipe 3
#define nRF24_REG_RX_PW_P4         		0x15 // Number of bytes in RX payload in data pipe 4
#define nRF24_REG_RX_PW_P5         		0x16 // Number of bytes in RX payload in data pipe 5
#define nRF24_REG_FIFO_STATUS      		0x17 // FIFO status register
#define nRF24_REG_DYNPD            		0x1C // Enable dynamic payload length
#define nRF24_REG_FEATURE          		0x1D // Feature register

// Size (Bytes)
#define nRF24_RX_ADDR_P0_SIZE 			5
#define nRF24_RX_ADDR_P1_SIZE 			5
#define nRF24_RX_ADDR_P2_SIZE 			1
#define nRF24_RX_ADDR_P3_SIZE 			1
#define nRF24_RX_ADDR_P4_SIZE 			1
#define nRF24_RX_ADDR_P5_SIZE 			1

#define nRF24_TX_ADDR_SIZE				5

// Register bits definitions
#define nRF24_STATUS_TX_FULL			(1<<0)
#define nRF24_STATUS_RX_P_NO_0			(1<<1)
#define nRF24_STATUS_RX_P_NO_1			(1<<2)
#define nRF24_STATUS_RX_P_NO_2			(1<<3)
#define nRF24_STATUS_MAX_RT				(1<<4)
#define nRF24_STATUS_TX_DS				(1<<5)
#define nRF24_STATUS_RX_DR				(1<<6)

#define nRF24_RF_CH_NUM_0				(1<<0)
#define nRF24_RF_CH_NUM_1				(1<<1)
#define nRF24_RF_CH_NUM_2				(1<<2)
#define nRF24_RF_CH_NUM_3				(1<<3)
#define nRF24_RF_CH_NUM_4				(1<<4)
#define nRF24_RF_CH_NUM_5				(1<<5)
#define nRF24_RF_CH_NUM_6				(1<<6)

#define nRF24_RF_SETUP_RF_PWR_0			(1<<1)
#define nRF24_RF_SETUP_RF_PWR_1			(1<<2)
#define nRF24_RF_SETUP_RF_DR_HIGH		(1<<3)
#define nRF24_RF_SETUP_PLL_LOCK			(1<<4)
#define nRF24_RF_SETUP_RF_DR_LOW		(1<<5)
#define nRF24_RF_SETUP_CONT_WAVE		(1<<7)

#define nRF24_CONFIG_PRIM_RX       		(1<<0)
#define nRF24_CONFIG_PWR_UP        		(1<<1)
#define nRF24_CONFIG_CRCO				(1<<2)
#define nRF24_CONFIG_EN_CRC				(1<<3)
#define nRF24_CONFIG_MASK_MAX_RT		(1<<4)
#define nRF24_CONFIG_MASK_TX_DS			(1<<5)
#define nRF24_CONFIG_MASK_RX_DR			(1<<6)

#define nRF24_SETUP_AW_AW_0				(1<<0)
#define nRF24_SETUP_AW_AW_1				(1<<1)

// Fake address to test transceiver presence (5 bytes long)
#define nRF24_TEST_ADDR            		{0xEE, 0xDD, 0xCC, 0xBB, 0xAA}

// Other
#define nRF24_AA_ON						1
#define nRF24_AA_OFF					0
#define nRF24_MODE_RX					1
#define nRF24_MODE_TX					0
#define nRF24_PWR_UP					1
#define nRF24_PWR_DOWN					0

#define nRF24_PIPE_0					0
#define nRF24_PIPE_1					1
#define nRF24_PIPE_2					2
#define nRF24_PIPE_3					3
#define nRF24_PIPE_4					4
#define nRF24_PIPE_5					5
#define nRF24_PIPE_TX					6

#define	nRF24_DR_1Mbps					0
#define	nRF24_DR_2Mbps					nRF24_RF_SETUP_RF_DR_HIGH
#define	nRF24_DR_250kbps				nRF24_RF_SETUP_RF_DR_LOW

#define nRF24_CRC_OFF					0
#define nRF24_CRC_1BYTE					nRF24_CONFIG_EN_CRC
#define nRF24_CRC_2BYTES				nRF24_CONFIG_EN_CRC | nRF24_CONFIG_CRCO

#define nRF24_AW_3BYTES					nRF24_SETUP_AW_AW_0
#define nRF24_AW_4BYTES					nRF24_SETUP_AW_AW_1
#define nRF24_AW_5BYTES					nRF24_SETUP_AW_AW_1 | nRF24_SETUP_AW_AW_0

#define nRF24_RFPWR_18dBm				0
#define	nRF24_RFPWR_12dBm				nRF24_RF_SETUP_RF_PWR_0
#define	nRF24_RFPWR_6dBm				nRF24_RF_SETUP_RF_PWR_1
#define	nRF24_RFPWR_0dBm				nRF24_RF_SETUP_RF_PWR_0 | nRF24_RF_SETUP_RF_PWR_1

#define nRF24_IRQ_OFF					0
#define nRF24_IRQ_MAX_RT				nRF24_CONFIG_MASK_MAX_RT
#define nRF24_IRQ_TX_DS					nRF24_CONFIG_MASK_TX_DS
#define nRF24_IRQ_RX_DR					nRF24_CONFIG_MASK_RX_DR

static const uint8_t nRF24_ADDR_REGS[7] =
{
		nRF24_REG_RX_ADDR_P0,
		nRF24_REG_RX_ADDR_P1,
		nRF24_REG_RX_ADDR_P2,
		nRF24_REG_RX_ADDR_P3,
		nRF24_REG_RX_ADDR_P4,
		nRF24_REG_RX_ADDR_P5,
		nRF24_REG_TX_ADDR
};

// Mask
#define nRF24_MASK_REG_MAP				0b00011111
#define nRF24_MASK_DR             		0b11010111
#define nRF24_MASK_CRC					0b11110011
#define nRF24_MASK_RF_PWR				0b11111001
#define nRF24_MASK_CONFIG_IRQ			0b01110000

// Functions
void nRF24_WriteReg(nRF24_UNIT *unit, uint8_t reg, uint8_t data);
void nRF24_WriteMBReg(nRF24_UNIT *unit, uint8_t reg, uint8_t *data, uint8_t size);

uint8_t nRF24_ReadReg(nRF24_UNIT *unit, uint8_t reg);
void nRF24_ReadMBReg(nRF24_UNIT *unit, uint8_t reg, uint8_t *data, uint8_t size);

void nRF24_Init(nRF24_UNIT *unit);
uint8_t nRF24_Check(nRF24_UNIT *unit);

void nRF24_FlushTX(nRF24_UNIT *unit);
void nRF24_FlushRX(nRF24_UNIT *unit);
void nRF24_ClearIRQFlags(nRF24_UNIT *unit);

void nRF24_SetAA(nRF24_UNIT *unit, uint8_t pipe, uint8_t on);
void nRF24_SetAddr(nRF24_UNIT *unit, uint8_t pipe, const uint8_t *addr);
void nRF24_SetRFChannel(nRF24_UNIT *unit, uint8_t channel);
void nRF24_SetDataRate(nRF24_UNIT *unit, uint8_t data_rate);
void nRF24_SetCRCScheme(nRF24_UNIT *unit, uint8_t scheme);
void nRF24_SetAddrWidth(nRF24_UNIT *unit, uint8_t addr_width);
void nRF24_SetRFPower(nRF24_UNIT *unit, uint8_t power);
void nRF24_SetMode(nRF24_UNIT *unit, uint8_t mode);
void nRF24_SetPower(nRF24_UNIT *unit, uint8_t on);
void nRF24_SetIRQ(nRF24_UNIT *unit, uint8_t mask_irq);

#endif /* APPLICATION_USER_NRF24L01_H_ */
