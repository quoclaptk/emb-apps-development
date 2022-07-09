/*
 * nRF24L01.c
 *
 *  Created on: Mar 4, 2022
 *      Author: Admin
 */

#include "nrf24l01.h"

void nRF24_WriteReg(nRF24_UNIT *unit, uint8_t reg, uint8_t data)
{
	nRF24_CSN_L(unit);

	if(reg < nRF24_CMD_W_REGISTER)
	{
		// Just write command and status registers
		nRF24_TransmitReceive(unit, nRF24_CMD_W_REGISTER | (reg & nRF24_MASK_REG_MAP));
		nRF24_TransmitReceive(unit, data);
	}
	else
	{
		nRF24_TransmitReceive(unit, reg);

		// This is a single byte command, don't need data
		if(reg == nRF24_CMD_FLUSH_TX || reg == nRF24_CMD_FLUSH_RX)
			return;

		if(reg == nRF24_CMD_REUSE_TX_PL || reg == nRF24_CMD_NOP)
			return;

		nRF24_TransmitReceive(unit, data);
	}

	nRF24_CSN_H(unit);
}

uint8_t nRF24_ReadReg(nRF24_UNIT *unit, uint8_t reg)
{
	uint8_t value;

	nRF24_CSN_L(unit);

	nRF24_TransmitReceive(unit, reg & nRF24_MASK_REG_MAP);
	value = nRF24_TransmitReceive(unit, nRF24_CMD_NOP);

	nRF24_CSN_H(unit);

	return value;
}

void nRF24_WriteMBReg(nRF24_UNIT *unit, uint8_t reg, uint8_t *data, uint8_t size)
{
	nRF24_CSN_L(unit);

	nRF24_TransmitReceive(unit, reg);

	while(size--)
	{
		nRF24_TransmitReceive(unit, *data++);
	}

	nRF24_CSN_H(unit);
}

void nRF24_ReadMBReg(nRF24_UNIT *unit, uint8_t reg, uint8_t *data, uint8_t size)
{
	nRF24_CSN_L(unit);

	nRF24_TransmitReceive(unit, reg);

	while(size--)
	{
		*data++ = nRF24_TransmitReceive(unit, nRF24_CMD_NOP);
	}

	nRF24_CSN_H(unit);
}

void nRF24_FlushTX(nRF24_UNIT *unit)
{
	nRF24_WriteReg(unit, nRF24_CMD_FLUSH_TX, 0);
}

void nRF24_FlushRX(nRF24_UNIT *unit)
{
	nRF24_WriteReg(unit, nRF24_CMD_FLUSH_RX, 0);
}

void nRF24_ClearIRQFlags(nRF24_UNIT *unit)
{
	uint8_t value; value = nRF24_ReadReg(unit, nRF24_REG_STATUS);

	// Clear RX_DR, TX_DS and MAX_RT bits of the STATUS register
	value |= (nRF24_STATUS_MAX_RT | nRF24_STATUS_TX_DS | nRF24_STATUS_RX_DR);

	nRF24_WriteReg(unit, nRF24_REG_STATUS, value);
}

void nRF24_Init(nRF24_UNIT *unit)
{
	// Write to registers their initial values
	nRF24_WriteReg(unit, nRF24_REG_CONFIG, 0b00001000);
	nRF24_WriteReg(unit, nRF24_REG_EN_AA, 0b00111111);
	nRF24_WriteReg(unit, nRF24_REG_EN_RXADDR, 0b00000011);
	nRF24_WriteReg(unit, nRF24_REG_SETUP_AW, 0b00000011);
	nRF24_WriteReg(unit, nRF24_REG_SETUP_RETR, 0b00000011);
	nRF24_WriteReg(unit, nRF24_REG_RF_CH, 0b00000010);
	nRF24_WriteReg(unit, nRF24_REG_RF_SETUP, 0b00001110);
	nRF24_WriteReg(unit, nRF24_REG_STATUS, 0b00000000);

	uint8_t RX_Address_Pipe0[nRF24_RX_ADDR_P0_SIZE] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	nRF24_WriteMBReg(unit, nRF24_REG_RX_ADDR_P0, RX_Address_Pipe0, nRF24_RX_ADDR_P0_SIZE);

	uint8_t RX_Address_Pipe1[nRF24_RX_ADDR_P1_SIZE] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
	nRF24_WriteMBReg(unit, nRF24_REG_RX_ADDR_P1, RX_Address_Pipe1, nRF24_RX_ADDR_P1_SIZE);

	nRF24_WriteReg(unit, nRF24_REG_RX_ADDR_P2, 0xC3);
	nRF24_WriteReg(unit, nRF24_REG_RX_ADDR_P3, 0xC4);
	nRF24_WriteReg(unit, nRF24_REG_RX_ADDR_P4, 0xC5);
	nRF24_WriteReg(unit, nRF24_REG_RX_ADDR_P5, 0xC6);

	uint8_t TX_Address[nRF24_TX_ADDR_SIZE] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	nRF24_WriteMBReg(unit, nRF24_REG_TX_ADDR, TX_Address, nRF24_TX_ADDR_SIZE);

	nRF24_WriteReg(unit, nRF24_REG_RX_PW_P0, 0b00000000);
	nRF24_WriteReg(unit, nRF24_REG_RX_PW_P1, 0b00000000);
	nRF24_WriteReg(unit, nRF24_REG_RX_PW_P2, 0b00000000);
	nRF24_WriteReg(unit, nRF24_REG_RX_PW_P3, 0b00000000);
	nRF24_WriteReg(unit, nRF24_REG_RX_PW_P4, 0b00000000);
	nRF24_WriteReg(unit, nRF24_REG_RX_PW_P5, 0b00000000);

	nRF24_WriteReg(unit, nRF24_REG_FIFO_STATUS, 0b00000000);
	nRF24_WriteReg(unit, nRF24_REG_DYNPD, 0b00000000);
	nRF24_WriteReg(unit, nRF24_REG_FEATURE, 0b00000000);

	nRF24_FlushRX(unit);
	nRF24_FlushTX(unit);
	nRF24_ClearIRQFlags(unit);

	nRF24_CSN_H(unit);
}

uint8_t nRF24_Check(nRF24_UNIT *unit)
{
	uint8_t TxData[nRF24_TX_ADDR_SIZE] = nRF24_TEST_ADDR;
	uint8_t RxData[nRF24_TX_ADDR_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00};

	// Write test TX address and read TX_ADDR register
	nRF24_WriteMBReg(unit, nRF24_CMD_W_REGISTER | nRF24_REG_TX_ADDR, TxData, nRF24_TX_ADDR_SIZE);
	nRF24_ReadMBReg(unit, nRF24_CMD_R_REGISTER | nRF24_REG_TX_ADDR, RxData, nRF24_TX_ADDR_SIZE);

	// Compare buffers, return error on first mismatch
	for(uint8_t i = 0; i < nRF24_TX_ADDR_SIZE; i++)
	{
		if(RxData[i] != TxData[i])
			return 0;
	}

	return 1;
}

void nRF24_SetAA(nRF24_UNIT *unit, uint8_t pipe, uint8_t on)
{
	if(pipe > 5)
	{
		// Enable / Disable Auto-ACK for ALL pipes
		nRF24_WriteReg(unit, nRF24_REG_EN_AA, on ? 0b00111111 : 0b00000000);
	}
	else
	{
		uint8_t value; value = nRF24_ReadReg(unit, nRF24_REG_EN_AA);

		if(on)
		{
			value |= (1 << pipe);
		}
		else
		{
			value &= ~(1 << pipe);
		}

		nRF24_WriteReg(unit, nRF24_REG_EN_AA, value);
	}
}

void nRF24_SetAddr(nRF24_UNIT *unit, uint8_t pipe, const uint8_t *addr)
{
	switch(pipe)
	{
		case nRF24_PIPE_TX:
		case nRF24_REG_RX_PW_P0...nRF24_REG_RX_PW_P1:
		{
			// Get address width
			uint8_t addr_width; addr_width = nRF24_ReadReg(unit, nRF24_REG_SETUP_AW) + 2;

			// Write address in reverse order (LSByte first)
			addr += addr_width - 1;

			nRF24_CSN_L(unit);

			nRF24_TransmitReceive(unit, nRF24_CMD_W_REGISTER | nRF24_ADDR_REGS[pipe]);

			while(addr_width--)
			{
				nRF24_TransmitReceive(unit, *addr--);
			}

			nRF24_CSN_H(unit);

			break;
		}
		case nRF24_REG_RX_PW_P2...nRF24_REG_RX_PW_P5:
		{
			// Write address LSBbyte (only first byte from the addr buffer)
			nRF24_WriteReg(unit, nRF24_ADDR_REGS[pipe], *addr);

			break;
		}
		default:
		{
			// Incorrect pipe number -> do nothing
			break;
		}
	}
}

void nRF24_SetRFChannel(nRF24_UNIT *unit, uint8_t channel)
{
	if(channel > 127)
	{
		channel = 127;
	}

	nRF24_WriteReg(unit, nRF24_REG_RF_CH, channel);
}

void nRF24_SetMode(nRF24_UNIT *unit, uint8_t mode)
{
	uint8_t value; value = nRF24_ReadReg(unit, nRF24_REG_CONFIG);

	// Configure PRIM_RX bit of the CONFIG register
	if(mode)
	{
		value |= nRF24_CONFIG_PRIM_RX;
	}
	else
	{
		value &= ~nRF24_CONFIG_PRIM_RX;
	}

	nRF24_WriteReg(unit, nRF24_REG_CONFIG, value);
}

void nRF24_SetPower(nRF24_UNIT *unit, uint8_t level)
{
	uint8_t value; value = nRF24_ReadReg(unit, nRF24_REG_CONFIG);

	if(level)
	{
		// It goes into Stanby-I mode with consumption about 26uA
		value |= nRF24_CONFIG_PWR_UP;
	}
	else
	{
		// Put the transceiver into power down mode with consumption about 900nA
		value &= ~nRF24_CONFIG_PWR_UP;
	}

	nRF24_WriteReg(unit, nRF24_REG_CONFIG, value);
}

void nRF24_SetCRCScheme(nRF24_UNIT *unit, uint8_t scheme)
{
	uint8_t value; value = nRF24_ReadReg(unit, nRF24_REG_CONFIG);

	// Configure EN_CRC[3] and CRCO[2] bits of the CONFIG register
	scheme &= ~nRF24_MASK_CRC; // Safety
	value &= nRF24_MASK_CRC;
	value |= scheme;

	nRF24_WriteReg(unit, nRF24_REG_CONFIG, value);
}

void nRF24_SetIRQ(nRF24_UNIT *unit, uint8_t mask_irq)
{
	uint8_t value; value = nRF24_ReadReg(unit, nRF24_REG_CONFIG);

	// Configure Mask[4:6] bits of the CONFIG register
	mask_irq &= ~nRF24_MASK_CONFIG_IRQ; // Safety
	value &= nRF24_MASK_CONFIG_IRQ;
	value |= mask_irq;

	nRF24_WriteReg(unit, nRF24_REG_CONFIG, value);
}

void nRF24_SetAddrWidth(nRF24_UNIT *unit, uint8_t addr_width)
{
	if(addr_width < 1)
	{
		addr_width = 1;
	}

	if(addr_width > 3)
	{
		addr_width = 3;
	}

	nRF24_WriteReg(unit, nRF24_REG_SETUP_AW, addr_width);
}

void nRF24_SetDataRate(nRF24_UNIT *unit, uint8_t data_rate)
{
	uint8_t value; value = nRF24_ReadReg(unit, nRF24_REG_RF_SETUP);

	// Configure RF_DR_LOW[5] and RF_DR_HIGH[3] bits of the RF_SETUP register
	data_rate &= ~nRF24_MASK_DR;
	value &= nRF24_MASK_DR;
	value |= data_rate;

	nRF24_WriteReg(unit, nRF24_REG_RF_SETUP, value);
}

void nRF24_SetRFPower(nRF24_UNIT *unit, uint8_t power)
{
	uint8_t value; value = nRF24_ReadReg(unit, nRF24_REG_RF_SETUP);

	// Configure RF_PWR[2:1] bits of the RF_SETUP register
	power &= ~nRF24_MASK_RF_PWR;
	value &= nRF24_MASK_RF_PWR;
	value |= power;

	nRF24_WriteReg(unit, nRF24_REG_RF_SETUP, value);
}




