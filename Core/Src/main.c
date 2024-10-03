/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdarg.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DEBUG_UART1 huart2
#define RGB_UART1 huart8
#define NIR_UART1 huart6
#define OBC_UART1 huart4
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart8;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_uart4_tx;
DMA_HandleTypeDef hdma_uart4_rx;
DMA_HandleTypeDef hdma_uart8_tx;
DMA_HandleTypeDef hdma_uart8_rx;
DMA_HandleTypeDef hdma_usart6_tx;
DMA_HandleTypeDef hdma_usart6_rx;

/* USER CODE BEGIN PV */
uint8_t rgb_img1 = 0;
uint8_t *data_rec1;
uint32_t ptr1;
uint8_t Whole_Img_RGB[18000] = { '\0' };
uint8_t OBC_CMD_RX1[7];
uint8_t obc_ok =0;
uint8_t OBC_RX_FLAG1 = 0;
uint8_t OBC_TX_FLAG1 = 0;
uint8_t obc_data1, rx_data1[7], i1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_UART8_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_UART4_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */
int buffersize(char *buff);
void myprintf(const char *fmt, ...);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart == &RGB_UART1) {

//		if (HAL_UART_Receive(&huart8, rgb_img_size, sizeof(rgb_img_size), 3000)
//				== HAL_OK) {
//			HAL_UART_Transmit(&huart2, "RGB IMAGE SIZE:",
//					sizeof("RGB IMAGE SIZE:"), 1000);
//			HAL_UART_Transmit(&huart2, rgb_img_size, sizeof(rgb_img_size),
//					1000);
//			ptr = atoi((char*) rgb_img_size);
			rgb_img1 = 1;

			HAL_UART_Receive_DMA(&huart8, Whole_Img_RGB, ptr1);
			int loop = 0;

			char log1[20];
			uint16_t data_size = 4000;
			uint8_t temp[data_size];
			loop = ptr1 / data_size;
			HAL_UART_Transmit(&huart2, "\n\n********Reading Image data****\n",
					sizeof("\n\n********Reading Image data****\n") - 1, 1000);

			if (Whole_Img_RGB[ptr1 - 2] == 0xFF
					&& Whole_Img_RGB[ptr1 - 1] == 0xD9) {
				myprintf(
						"End marker (0xFF, 0xD9) detected, Image received successfully.\n");
								obc_ok = 0;
			} else {
				myprintf(
						"Warning: End marker (0xFF, 0xD9) not found. Data might be incomplete.\n");
			}
			rgb_img1 = 0;
			myprintf("Ready to receive next image size.\n");


}
void OBC_HANDSHAKE1() {
	while (OBC_RX_FLAG1 != 1) {
		if (HAL_UART_Receive(&huart4, &obc_data1, 1, 1000) == HAL_OK) {
			HAL_UART_Transmit(&DEBUG_UART1, &obc_data1, 1, 100);
			rx_data1[i1++] = obc_data1;
			i1 = i1 % 8;
			if (i1 == 7)
				OBC_RX_FLAG1 = 1;
		}

	}
	if (OBC_RX_FLAG1 == 1) {
		HAL_UART_Transmit(&huart4, rx_data1, sizeof(rx_data1), 1000);
		HAL_UART_Transmit(&DEBUG_UART1, &rx_data1, 1, 100);
	}
}

uint32_t IMAGE_CAPTURE1() {
	uint8_t CAM_tx[] = { 'C', 'A', 'M', 'O', 'N' };

	uint32_t size1 = 0;
	uint8_t rgb_img_size[6];
	data_rec1 = Whole_Img_RGB;
	char log1[30];
	UART_Flush(&huart2);
	UART_Flush(&huart8);
	UART_Flush_DMA(&huart8);
	HAL_UART_Transmit(&RGB_UART1, CAM_tx, sizeof(CAM_tx), 1000);
//	HAL_UART_Transmit(&NIR_UART1, CAM_tx, sizeof(CAM_tx), 1000);

    if (HAL_UART_Receive(&huart8, rgb_img_size, sizeof(rgb_img_size), 5000) == HAL_OK) {
    	HAL_UART_Transmit(&huart2, "RGB IMAGE SIZE:", sizeof("RGB IMAGE SIZE:"), 1000);
    	HAL_UART_Transmit(&huart2, rgb_img_size, sizeof(rgb_img_size), 1000);
        ptr1 = atoi((char*) rgb_img_size);
//        Whole_Img_RGB = (uint8_t*) malloc(ptr1);
        HAL_UART_Receive_DMA(&huart8, Whole_Img_RGB, ptr1);

	if (rgb_img1 == 1){
				int len = snprintf(log1, sizeof(log1), " %lu bytes\n", ptr1);
				HAL_UART_Transmit(&huart4, (uint8_t*) "Image size is: ",
						sizeof("Image size is: "), 1000);
				HAL_UART_Transmit(&huart4, (uint8_t*) log1, len, 1000);

	}

	}

//		HAL_UART_Receive_DMA(&RGB_UART1, rrr, ptr1);
//		if(HAL_UART_Receive(&RGB_UART1, rrr, ptr1, 10000) == HAL_OK){
////					HAL_UART_Transmit(&RGB_UART, data_rec, ptr,1000);
//			sprintf(log1 , "data size : %d received\n", ptr1);
//				HAL_UART_Transmit(&DEBUG_UART1,log1, sizeof(log1), 1000);
//				}

//		do{
//			if(HAL_UART_Receive(&RGB_UART1, temp, sizeof(temp),1000) == HAL_OK){
//
////				rrr[loop++]=  temp;
//				loop--;
////				  sprintf(log1 , "%d \0", loop);
//				HAL_UART_Transmit(&DEBUG_UART1, temp, sizeof(temp), 1000);
//			}
//		}while(loop>0);
////		loop =ptr1%10;
//		do{
//
//			if(HAL_UART_Receive(&RGB_UART1, temp, sizeof(temp),1000) == HAL_OK){
//
//			//				rrr[loop++]=  temp;
////							loop--;
//			//				  sprintf(log1 , "%d \0", loop);
//							HAL_UART_Transmit(&DEBUG_UART1, temp, sizeof(temp), 1000);
//
//							if(temp == 0xd9) break;
//						}
//		}while(1);
//		if (HAL_OK == HAL_UART_Receive_DMA(&huart8, rrr, ptr1-2)) {
//

//			sprintf(log1 , "************************\n\n BUffer data size : %d received\n", ptr1);
//		HAL_UART_Transmit(&DEBUG_UART1,log1, sizeof(log1), 1000);

//		HAL_UART_Transmit(&DEBUG_UART1, rrr, ptr1-1, 1000);
//		}
//		RGB_CAM = 1;
		//HAL_Delay(20000);

	}
}
void OCP_EN1() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_Delay(100);
}
void OCP_DISABLE() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_Delay(100);
}

void UART_Flush(UART_HandleTypeDef *huart) {
	__HAL_UART_FLUSH_DRREGISTER(huart);
}
void UART_Flush_DMA(UART_HandleTypeDef *huart) {
	// Disable UART DMA request
	__HAL_UART_DISABLE_IT(huart, UART_IT_RXNE);

	// Abort any ongoing UART reception via DMA
	HAL_UART_AbortReceive(huart);

	// Reset the UART receive state
	huart->RxState = HAL_UART_STATE_READY;
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_UART8_Init();
  MX_USART2_UART_Init();
  MX_USART6_UART_Init();
  MX_UART4_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Transmit(&huart2, (uint8_t*) "Camera is starting",
			sizeof("Camera is starting"), 1000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {

//
//		OBC_HANDSHAKE1();
//		OBC_RX_FLAG1 = 0;
//
//		do {
//			if (HAL_UART_Receive(&OBC_UART1, OBC_CMD_RX1, 7, 1000) == HAL_OK) {
//				UART_Flush(&huart4);
//
//				if (OBC_CMD_RX1[0] == 0x53 && OBC_CMD_RX1[1] == 0x0C
//						&& OBC_CMD_RX1[2] == 0x0A && OBC_CMD_RX1[3] == 0X0e
//						&& OBC_CMD_RX1[4] == 0X01 && OBC_CMD_RX1[5] == 0X7e) {
//					HAL_UART_Transmit(&OBC_UART1, OBC_CMD_RX1,
//							sizeof(OBC_CMD_RX1), 1000);
////									OCP_EN1();
//					OBC_RX_FLAG1 = 1;
//					break;
//				}
//			}
//		} while (1);
//		myprintf("Data received from OBC\r\n");
//		HAL_Delay(2000);
		//		while (!OBC_RX_FLAG) {
//		//			myprintf("waiting for command from OBC.\r\n");
//		//			HAL_Delay(1000);
//		//		}
		OCP_EN1();
		IMAGE_CAPTURE1();
//		if (obc_ok == 1){
//			//HAL_UART_Transmit(&OBC_UART1,rrr, sizeof(rrr),1000);
//		}
//		HAL_Delay(1000);

//		IMAGE_CAPTURE1();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief UART8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART8_Init(void)
{

  /* USER CODE BEGIN UART8_Init 0 */

  /* USER CODE END UART8_Init 0 */

  /* USER CODE BEGIN UART8_Init 1 */

  /* USER CODE END UART8_Init 1 */
  huart8.Instance = UART8;
  huart8.Init.BaudRate = 115200;
  huart8.Init.WordLength = UART_WORDLENGTH_8B;
  huart8.Init.StopBits = UART_STOPBITS_1;
  huart8.Init.Parity = UART_PARITY_NONE;
  huart8.Init.Mode = UART_MODE_TX_RX;
  huart8.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart8.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart8) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART8_Init 2 */

  /* USER CODE END UART8_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  /* DMA1_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
  /* DMA1_Stream4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
  /* DMA2_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
  /* DMA2_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, cs_Pin|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pins : cs_Pin PB4 */
  GPIO_InitStruct.Pin = cs_Pin|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
	while (1) {
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
