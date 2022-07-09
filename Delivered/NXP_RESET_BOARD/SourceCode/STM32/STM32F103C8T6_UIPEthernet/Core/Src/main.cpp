/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.cpp
  * @brief          : Main program body
  * Link			: https://www.arduino.cc/reference/en/libraries/uipethernet/
  * Version			: 2.0.11
  * Example			: https://codebender.cc/sketch:210387#ENC28J60%20relay%20control.ino
  * POST			: curl -X POST http://192.168.0.100 -d "{data:[1111111111111111]}"
  * GET				:
  ******************************************************************************
 **/
#include <UIPEthernet.h>
/******************************************************************************/
SPI_HandleTypeDef hspi1;
/******************************************************************************/
String buffer = "";
char c;
uint32_t count = 0;
/*** The configuration of the application ***/
// Change the configuration for your needs
const uint8_t mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
const IPAddress myIP(192, 168, 0, 105);
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
const int R_OFF = 0;
const int R_ON  = 1;
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
uint8_t relayDataStatus[numRelays]={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
/******************************************************************************/
String getPostData(EthernetClient &client);
bool updateRelayDataStatus(uint8_t relay, uint8_t onOffStat);
void analyzePostData(EthernetClient &client);
void printRelayStatus(EthernetClient &client);
void returnErr(EthernetClient &client, int rc);
void returnHeader(EthernetClient &client, int httpCode);
String getNextLine(EthernetClient &client);
/******************************************************************************/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/******************************************************************************/
void _cs(bool level)
{
	if(level)HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
}

uint8_t spiWrite(uint8_t data)
{
	uint8_t rxData = 0;
	HAL_SPI_TransmitReceive(&hspi1, &data, &rxData, 1, 100);
	return rxData;
}
void dataWrite(void)
{
	/* Update status data */
	for(uint8_t i=0; i<numRelays; i++)
	{
		if(relayDataStatus[i] == R_INV)
		{
			if(count>0)bitClear(dataStatus, i); /* Turn off relay and waiting by count variable is decreasing */
			else /* Turn on relay */
			{
				bitSet(dataStatus, i);
				relayDataStatus[i] = R_ON;
			}
		}
		else if(relayDataStatus[i] == R_ON)bitSet(dataStatus, i);
		else if(relayDataStatus[i] == R_OFF)bitClear(dataStatus, i);
	}
	/* Write to relays */
	for(uint8_t i=0; i<numRelays; i++)
	{
		if(((dataStatus>>i)&0x01)==0x01)HAL_GPIO_WritePin(HC_DATA_GPIO_Port, HC_DATA_Pin, GPIO_PIN_SET);
		else HAL_GPIO_WritePin(HC_DATA_GPIO_Port, HC_DATA_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HC_CLK_GPIO_Port, HC_CLK_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HC_CLK_GPIO_Port, HC_CLK_Pin, GPIO_PIN_RESET);
	}
	HAL_GPIO_WritePin(HC_LAT_GPIO_Port, HC_LAT_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(HC_LAT_GPIO_Port, HC_LAT_Pin, GPIO_PIN_RESET);
}
/******************************************************************************/
int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_SPI1_Init();
	Ethernet.begin(mac);/* Configure IP address via DHCP */
	//Ethernet.begin(mac, myIP);/* Configure static IP address */
	Ethernet.localIP();
	server.begin();
	while (1)
	{
		if(EthernetClient client = server.available())
		{ 	count=0x1FF;
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
					//HAL_Delay(1);
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
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CS_Pin|LED_Pin|HC_DATA_Pin|HC_CLK_Pin
                          |HC_LAT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CS_Pin LED_Pin HC_DATA_Pin HC_CLK_Pin
                           HC_LAT_Pin */
  GPIO_InitStruct.Pin = CS_Pin|LED_Pin|HC_DATA_Pin|HC_CLK_Pin
                          |HC_LAT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

