/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * $Revision: 3 $
 * $Date: 15/02/13 2:19p $
 * @brief    A project template for Mini58 MCU.
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <UIPEthernet.h>

#define MOSI 	P05
#define MISO 	P06
#define SCK  	P07
#define CS  	P04

#define HCDATA 		P13
#define HCCLK		P14
#define HCLAT		P15

uint32_t uwTick = 0;
uint32_t ledTime = 0;
/******************************************************************************/
String buffer = "";
char c;
uint32_t count = 0;
/*** The configuration of the application ***/
// Change the configuration for your needs
const uint8_t mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEC };
const IPAddress myIP(192, 168, 137, 105);
/****** a little bit of security *****/
// max request size, arduino cannot handle big requests so set the max you really plan to process
const int maxSize = 512; // that is enough for 8 relays + a bigger header
// the get requests the application is listening to
const char REQ_ABOUT[] = "/about";
// Request parameters
const char GET[]  = "GET";
const char POST[] = "POST";
// http codes
const int RC_ERR = 500;
const int RC_OK  = 200;
// supported relay status
const int R_OFF = 1;
const int R_ON  = 0;
const int R_INV = 2;
/* ************ internal constants *************/
// new line
const char NL = '\n';
// carriage return
const char CR = '\r';
// response of relay status, json start
const char RS_START[] = "{Relay Status:[";
// response of relay status, json end
const char RS_END[] = "]}";
// response of relay status, json array separator;
const char RS_SEP = ',';
// response of the error JSON start
const char RS_ERR_START[] = "{\"e\":";
// response of the error JSON end
const char RS_ERR_END = '}';
const char HD_START[] = "HTTP/1.1 ";
const char HD_END[] = " \nContent-Type: text/html\nConnection: close\n\n";
const char VERSION[] = "{\"version\":\"0.2\"}";
// start the server on port 80
EthernetServer server = EthernetServer(80);
// Number of relays on board, max 9 are supported!
const uint8_t numRelays = 32;
uint32_t dataStatus = 0x00000000;
uint8_t relayDataStatus[numRelays]={R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON, R_ON};
/******************************************************************************/
String getPostData(EthernetClient &client);
bool updateRelayDataStatus(uint8_t relay, uint8_t onOffStat);
void analyzePostData(EthernetClient &client);
void printRelayStatus(EthernetClient &client);
void returnErr(EthernetClient &client, int rc);
void returnHeader(EthernetClient &client, int httpCode);
String getNextLine(EthernetClient &client);
/******************************************************************************/

void dataWrite(void)
{
	/* Update status data */
	for(uint8_t i=0; i<numRelays; i++)
	{
		if(relayDataStatus[i] == R_INV)
		{
			if(count>0)bitSet(dataStatus, i); /* Turn off relay and waiting by count variable is decreasing */
			else /* Turn on relay */
			{
				bitClear(dataStatus, i);
				relayDataStatus[i] = R_ON;
			}
		}
		else if(relayDataStatus[i] == R_ON)bitClear(dataStatus, i);
		else if(relayDataStatus[i] == R_OFF)bitSet(dataStatus, i);
	}
	/* Write to relays */
	for(uint8_t i=0; i<numRelays; i++)
	{
		if(((dataStatus>>i)&0x01)==0x01)HCDATA = 1;
		else HCDATA = 0;
		HCCLK = 1;
		HCCLK = 0;
	}
	HCLAT = 1;
	HCLAT = 0;
}
/******************************************************************************/
/******************************************************************************/

void SYS_Init(void)
{
	SYS_UnlockReg();
	CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV_HCLK(2));
	CLK->APBCLK = CLK_APBCLK_TMR1CKEN_Msk;
	SystemCoreClockUpdate();
	SYS_LockReg();
}

void cs(bool level)
{
	if(level == true)CS = 1;
	else CS = 0;
}
uint8_t spiWrite(uint8_t myByte)
{
	for(uint8_t i = 0; i<8; i++)
	{
		if(myByte & 0x80)MOSI = 1;
		else MOSI = 0;
		myByte <<= 1;
		SCK = 1; /* a slave latches input data bit */
		if(MISO != 0)myByte |= 0x01;
		SCK = 0; /* a slave shifts out next output data bit */
	}
	return(myByte);
}
/**
 * \brief SysTick_Handler.
 */
extern "C" void SysTick_Handler(void)
{
	ledTime++;
	if(ledTime>500)
	{
		ledTime = 0;
		P12 ^= 1;
	}
  /* Increment counter necessary in delay(). */
	uwTick++;
}

void GPIO_Init()
{
	GPIO_SetMode(P0, BIT4, GPIO_MODE_OUTPUT);/* CS */
	GPIO_SetMode(P0, BIT5, GPIO_MODE_OUTPUT); /* SI */
	GPIO_SetMode(P0, BIT6, GPIO_MODE_INPUT);/* SO */
	GPIO_SetMode(P0, BIT7, GPIO_MODE_OUTPUT);/* SCK */
	GPIO_SetMode(P1, BIT2, GPIO_MODE_OUTPUT); /* LED */
	GPIO_SetMode(P1, BIT3, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P1, BIT4, GPIO_MODE_OUTPUT);
	GPIO_SetMode(P1, BIT5, GPIO_MODE_OUTPUT);
}


int main()
{
    SYS_Init();
    GPIO_Init();
    SysTick_Config(SystemCoreClock/1000);/* 1ms increment for system timer */
    Ethernet.begin(mac);/* Configure IP address via DHCP */
//	Ethernet.begin(mac, myIP);/* Configure static IP address */
	Ethernet.localIP();
	server.begin();
    while(1)
    {
    	if(EthernetClient client = server.available())
		{
    		count=0x1FF;
			if (client)
			{
				size_t size;
				if((size = client.available()) > 0)
				{
					if(size > maxSize)// check the the data is not too big
					{
						returnHeader(client, RC_ERR);
						returnErr(client, 1);
					}
					// read all data
					while (client.connected() && client.available())
					{
						buffer = getNextLine(client);
						if (buffer.startsWith(GET))
						{
							returnHeader(client, RC_OK);
							String getData = buffer.substring(4, buffer.length() - 9);
							if (getData.equals(REQ_ABOUT))client.println(VERSION);
							else printRelayStatus(client);
							break;
						}
						else if (buffer.startsWith(POST))
						{
							//returnHeader(client, RC_OK);
							analyzePostData(client);
							break;
						}
						else /* only get and post are supported */
						{
							returnHeader(client, RC_ERR);
							returnErr(client, 2);
						}
					}
					client.stop();
				}
			}
		}
		dataWrite();
		if(count>0)count--;
    }

}
/**
 * It will get the data in case of a post request, by reading the last line.
 */
String getPostData(EthernetClient &client)
{
	char c;
	while (client.connected() && client.available())
	{
		c = client.read();
		// ignore all \r characters
		if ((c != CR) && (c == NL))
		{
			// is the next char a carriage return or a line break?
			c = client.read();
			// then ignore it and read the next character
			if (c == CR) c = client.read();
			// read the line with the post data
			if (c == NL) return getNextLine(client);
		} // end c != CR
	} // end while
	return "";
}

/**
 * Performs the change on the relay itself.
 */

bool updateRelayDataStatus(uint8_t relay, uint8_t onOffStat)
{
	if(onOffStat == R_OFF)
	{
		relayDataStatus[relay] = R_OFF;
		bitClear(dataStatus, relay);
	}
	else if(onOffStat == R_ON)
	{
		relayDataStatus[relay] = R_ON;
		bitSet(dataStatus, relay);
	}
	else if(onOffStat == R_INV)
	{
		relayDataStatus[relay] = R_INV;
		bitSet(dataStatus, relay);
	}
	else return false;
	return true;
}

/**
 * Performs the status change on the relays. The POST data must follow the
 * pattern: relay number = 0 or 1 or 2 => e.g. 0101010101010101010
 *   -> The relay number can only be an integer between 0 and the constant numRelays-1
 *   -> 0 turns the relay off
 *   -> 1 turns the relay on
 *   -> 2 changes the status of the relay. So a turned off relay would be switched on and the other way around.
 * The result of this method can be:
 * 	1. A HTTP 500 error if something went wrong processing the command.
 * 	2. A JSON String as you would get when sending a simple GET request.
 */

void analyzePostData(EthernetClient &client)
{
	String command = getPostData(client);
	uint8_t indexEnd = command.indexOf(']');
	uint8_t indexStart = command.indexOf('[');
	String param = command.substring(indexStart+1, indexEnd);
	for(uint8_t i=indexStart+1; i<indexEnd; i++)
	{
		uint8_t relayIndex = i - (indexStart+1);
		if((relayIndex<numRelays) && (relayIndex>=0))
		{
			uint8_t onOff = param.charAt(relayIndex) - '0';
			if((onOff >= 0)&&(onOff < 3))
			{
				bool ok = updateRelayDataStatus(relayIndex, onOff);
				if(!ok)
				{
					// stop processing, an error occurred!
					returnHeader(client, RC_ERR);
					returnErr(client, 5);
					return;
				}
			}
			else
			{
				/* Do not thing */
			}
		}
	}
	// return the final status of all relays
	returnHeader(client, RC_OK);
	printRelayStatus(client);
}


/**
 * Returns a JSON with the current values of the relays to the client. The
 * JSON will look like: {"r":[0,0,0,0,0,0,0,0]}
 * This one means all releays are turned off.
 */
void printRelayStatus(EthernetClient &client)
{
	client.print(RS_START);
	for (uint8_t i = 0; i < numRelays; i++)
	{
		client.print(bitRead(dataStatus, i));
	}
	client.println(RS_END);
}

/**
 * Returns a message to the client.
 */
void returnErr(EthernetClient &client, int rc)
{
	client.print(RS_ERR_START);
	client.print(rc);
	client.println(RS_ERR_END);
}

/**
 * Returns a header with the given http code to the client.
 */
void returnHeader(EthernetClient &client, int httpCode)
{
	client.print(HD_START);
	client.print(httpCode);
	client.print(HD_END);
}

String getNextLine(EthernetClient &client)
{
	char c;
	String buffer;
	while (client.connected() && client.available())
	{
		c = client.read();
		// ignore all \r characters
		if (c != CR)
		{
			// not read until you have a line break
			if (c == NL)
			{
				// every entry in in a certain line
				return buffer;
			}
			else
			{
				buffer += c;
			}
		} // end c != CR
	} // end while
	return buffer;
}
/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/
