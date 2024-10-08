///* USER CODE BEGIN Header */
///**
// ******************************************************************************
// * @file           : main.c
// * @brief          : Main program body
// ******************************************************************************
// * @attention
// *
// * Copyright (c) 2024 STMicroelectronics.
// * All rights reserved.
// *
// * This software is licensed under terms that can be found in the LICENSE file
// * in the root directory of this software component.
// * If no LICENSE file comes with this software, it is provided AS-IS.
// *
// ******************************************************************************
// */
///* USER CODE END Header */
///* Includes ------------------------------------------------------------------*/
//#include "main.h"
//
///* Private includes ----------------------------------------------------------*/
///* USER CODE BEGIN Includes */
//#include <stdlib.h>
//#include <configuration.h>
//#include <variables.h>
//#include <functions.h>
//#include <littlefs_driver.h>
//
///* USER CODE END Includes */
//
///* Private typedef -----------------------------------------------------------*/
///* USER CODE BEGIN PTD */
//
///* USER CODE END PTD */
//
///* Private define ------------------------------------------------------------*/
///* USER CODE BEGIN PD */
//
///* USER CODE END PD */
//
///* Private macro -------------------------------------------------------------*/
///* USER CODE BEGIN PM */
//
///* USER CODE END PM */
//
///* Private variables ---------------------------------------------------------*/
//SPI_HandleTypeDef hspi2;
//
//UART_HandleTypeDef huart4;
//UART_HandleTypeDef huart8;
//UART_HandleTypeDef huart2;
//UART_HandleTypeDef huart6;
//DMA_HandleTypeDef hdma_uart8_tx;
//DMA_HandleTypeDef hdma_uart8_rx;
//DMA_HandleTypeDef hdma_usart6_tx;
//DMA_HandleTypeDef hdma_usart6_rx;
//
///* USER CODE BEGIN PV */
//
//
//uint8_t data[20];
//
///* USER CODE END PV */
//
///* Private function prototypes -----------------------------------------------*/
//void SystemClock_Config(void);
//static void MX_GPIO_Init(void);
//static void MX_DMA_Init(void);
//static void MX_UART8_Init(void);
//static void MX_USART2_UART_Init(void);
//static void MX_USART6_UART_Init(void);
//static void MX_UART4_Init(void);
//static void MX_SPI2_Init(void);
///* USER CODE BEGIN PFP */
//
///* USER CODE END PFP */
//
///* Private user code ---------------------------------------------------------*/
///* USER CODE BEGIN 0 */
//
///* USER CODE END 0 */
//
///**
//  * @brief  The application entry point.
//  * @retval int
//  */
//int main(void)
//{
//
//  /* USER CODE BEGIN 1 */
//
//  /* USER CODE END 1 */
//
//  /* MCU Configuration--------------------------------------------------------*/
//
//  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
//  HAL_Init();
//
//  /* USER CODE BEGIN Init */
//
//  /* USER CODE END Init */
//
//  /* Configure the system clock */
//  SystemClock_Config();
//
//  /* USER CODE BEGIN SysInit */
//
//  /* USER CODE END SysInit */
//
//  /* Initialize all configured peripherals */
//  MX_GPIO_Init();
//  MX_DMA_Init();
//  MX_UART8_Init();
//  MX_USART2_UART_Init();
//  MX_USART6_UART_Init();
//  MX_UART4_Init();
//  MX_SPI2_Init();
//  /* USER CODE BEGIN 2 */
////  int x=0;
////	HAL_UART_Transmit(&huart8, tx, sizeof(tx), 1000);
//////	HAL_UART_Transmit(&huart6, tx, sizeof(tx),1000);
////	if (HAL_OK
////			== HAL_UART_Receive(&huart8, rgb_img_size, sizeof(rgb_img_size),
////					3000)) {
////		HAL_UART_Transmit(&huart2, "Image size is : ",
////				sizeof("Image size is : "), 1000);
////
////		HAL_UART_Transmit(&huart2, rgb_img_size, sizeof(rgb_img_size), 1000);
////		ptr = atoi((char*) rgb_img_size);
////		RGB_CAM = 1;
////
////	}
////	if (HAL_OK
////			== HAL_UART_Receive(&huart6, nir_img_size, sizeof(nir_img_size),
////					3000)) {
////		HAL_UART_Transmit(&huart2, "Image size is : ",
////				sizeof("Image size is : "), 1000);
////
////		HAL_UART_Transmit(&huart2, nir_img_size, sizeof(nir_img_size), 1000);
////		ptr = atoi(nir_img_size);
////		NIR_CAM = 1;
////
////	}
////  uint16_t kriti[] ={'0xff','0xd8','0xff','0xe0','0x00','0x10','0x4a','0x46','0x49','0x46','0x00','0x01'};
////  Read_ID(&hspi2, GPIOB, GPIO_PIN_11, &data);
////  write_to_file("/CAM.txt", kriti);
//  /* USER CODE END 2 */
//
//  /* Infinite loop */
//  /* USER CODE BEGIN WHILE */
//	while (1) {
//		HAL_UART_Transmit(&huart2, (uint8_t*)"Camera is starting",sizeof ("Camera is starting"),1000);
//    /* USER CODE END WHILE */
//
//    /* USER CODE BEGIN 3 */
////		IMAGE_CAPTURE();
//		OBC_HANDSHAKE();
////
//		OBC_RX_FLAG = 0;
//
////		if(HAL_UART_Receive(&OBC_UART, OBC_CMD_RX, 7, 1000)== HAL_OK){
////			OCP_EN();
////			HAL_Delay(10);
////		}
//
//		do {
//			if(HAL_UART_Receive(&OBC_UART, OBC_CMD_RX, 7,1000) == HAL_OK){
//
//				if (OBC_CMD_RX[0] == 0x53 && OBC_CAM_RX[1] == 0x0C
//								&& OBC_CAM_RX[2] == 0x0A && OBC_CAM_RX[3] == 0X0e
//								&& OBC_CAM_RX[4] == 0X01 && OBC_CAM_RX[5] == 0X7e){
//					HAL_UART_Transmit(&OBC_UART, OBC_CMD_RX,sizeof(OBC_CMD_RX), 1000);
//				   OCP_EN();
//				   OBC_RX_FLAG =1;
//				break;
//				}
//			}
//		}while(1);
////		while (!OBC_RX_FLAG) {
////			myprintf("waiting for command from OBC.\r\n");
////			HAL_Delay(1000);
////		}
//		myprintf("Data received from OBC\r\n");
//
//		if (OBC_COMMAND[0] == 0x53 && OBC_COMMAND[1] == 0x0C
//				&& OBC_COMMAND[2] == 0x0A && OBC_COMMAND[3] == 0X0e
//				&& OBC_COMMAND[4] == 0X01 && OBC_COMMAND[5] == 0X7e) {
//			HAL_UART_Transmit(&OBC_UART,(uint8_t*)"ACK",sizeof("ACK"), 1000);
//			myprintf("command received from OBC\r\n");
//			IMAGE_CAPTURE();
//			HAL_Delay(10);
////
////				else if (OBC_COMMAND[0] == 0xac && OBC_COMMAND[1] == 0x0b && OBC_COMMAND[2] == 0x02) {
////					myprintf("Command received to take photo and classify....\r\n");
//////					uint32_t IMAGE_CAPTURE();
////
////					HAL_Delay(1);
////				}
//		} else {
//			myprintf("Data not received \r\n");
//			HAL_Delay(1);
//		}
//		if (rgb == 0 && nir == 0) {
//			HAL_UART_Transmit(&DEBUG_UART, "Both images received\n",
//					sizeof("Both images received\n"), 1000);
//			break;
//
//			//  send to flash
//		}
//       HAL_Delay(100);
//	}
//
//  /* USER CODE END 3 */
//}
//
///**
//  * @brief System Clock Configuration
//  * @retval None
//  */
//void SystemClock_Config(void)
//{
//  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//
//  /** Configure the main internal regulator output voltage
//  */
//  __HAL_RCC_PWR_CLK_ENABLE();
//  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
//
//  /** Initializes the RCC Oscillators according to the specified parameters
//  * in the RCC_OscInitTypeDef structure.
//  */
//  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//  RCC_OscInitStruct.PLL.PLLM = 4;
//  RCC_OscInitStruct.PLL.PLLN = 180;
//  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
//  RCC_OscInitStruct.PLL.PLLQ = 4;
//  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Activate the Over-Drive mode
//  */
//  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Initializes the CPU, AHB and APB buses clocks
//  */
//  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
//                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
//  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
//  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
//
//  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
//  {
//    Error_Handler();
//  }
//}
//
///**
//  * @brief SPI2 Initialization Function
//  * @param None
//  * @retval None
//  */
//static void MX_SPI2_Init(void)
//{
//
//  /* USER CODE BEGIN SPI2_Init 0 */
//
//  /* USER CODE END SPI2_Init 0 */
//
//  /* USER CODE BEGIN SPI2_Init 1 */
//
//  /* USER CODE END SPI2_Init 1 */
//  /* SPI2 parameter configuration*/
//  hspi2.Instance = SPI2;
//  hspi2.Init.Mode = SPI_MODE_MASTER;
//  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
//  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
//  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
//  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
//  hspi2.Init.NSS = SPI_NSS_SOFT;
//  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
//  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
//  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
//  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
//  hspi2.Init.CRCPolynomial = 10;
//  if (HAL_SPI_Init(&hspi2) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN SPI2_Init 2 */
//
//  /* USER CODE END SPI2_Init 2 */
//
//}
//
///**
//  * @brief UART4 Initialization Function
//  * @param None
//  * @retval None
//  */
//static void MX_UART4_Init(void)
//{
//
//  /* USER CODE BEGIN UART4_Init 0 */
//
//  /* USER CODE END UART4_Init 0 */
//
//  /* USER CODE BEGIN UART4_Init 1 */
//
//  /* USER CODE END UART4_Init 1 */
//  huart4.Instance = UART4;
//  huart4.Init.BaudRate = 115200;
//  huart4.Init.WordLength = UART_WORDLENGTH_8B;
//  huart4.Init.StopBits = UART_STOPBITS_1;
//  huart4.Init.Parity = UART_PARITY_NONE;
//  huart4.Init.Mode = UART_MODE_TX_RX;
//  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
//  if (HAL_UART_Init(&huart4) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN UART4_Init 2 */
//
//  /* USER CODE END UART4_Init 2 */
//
//}
//
///**
//  * @brief UART8 Initialization Function
//  * @param None
//  * @retval None
//  */
//static void MX_UART8_Init(void)
//{
//
//  /* USER CODE BEGIN UART8_Init 0 */
//
//  /* USER CODE END UART8_Init 0 */
//
//  /* USER CODE BEGIN UART8_Init 1 */
//
//  /* USER CODE END UART8_Init 1 */
//  huart8.Instance = UART8;
//  huart8.Init.BaudRate = 115200;
//  huart8.Init.WordLength = UART_WORDLENGTH_8B;
//  huart8.Init.StopBits = UART_STOPBITS_1;
//  huart8.Init.Parity = UART_PARITY_NONE;
//  huart8.Init.Mode = UART_MODE_TX_RX;
//  huart8.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart8.Init.OverSampling = UART_OVERSAMPLING_16;
//  if (HAL_UART_Init(&huart8) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN UART8_Init 2 */
//
//  /* USER CODE END UART8_Init 2 */
//
//}
//
///**
//  * @brief USART2 Initialization Function
//  * @param None
//  * @retval None
//  */
//static void MX_USART2_UART_Init(void)
//{
//
//  /* USER CODE BEGIN USART2_Init 0 */
//
//  /* USER CODE END USART2_Init 0 */
//
//  /* USER CODE BEGIN USART2_Init 1 */
//
//  /* USER CODE END USART2_Init 1 */
//  huart2.Instance = USART2;
//  huart2.Init.BaudRate = 115200;
//  huart2.Init.WordLength = UART_WORDLENGTH_8B;
//  huart2.Init.StopBits = UART_STOPBITS_1;
//  huart2.Init.Parity = UART_PARITY_NONE;
//  huart2.Init.Mode = UART_MODE_TX_RX;
//  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
//  if (HAL_UART_Init(&huart2) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN USART2_Init 2 */
//
//  /* USER CODE END USART2_Init 2 */
//
//}
//
///**
//  * @brief USART6 Initialization Function
//  * @param None
//  * @retval None
//  */
//static void MX_USART6_UART_Init(void)
//{
//
//  /* USER CODE BEGIN USART6_Init 0 */
//
//  /* USER CODE END USART6_Init 0 */
//
//  /* USER CODE BEGIN USART6_Init 1 */
//
//  /* USER CODE END USART6_Init 1 */
//  huart6.Instance = USART6;
//  huart6.Init.BaudRate = 115200;
//  huart6.Init.WordLength = UART_WORDLENGTH_8B;
//  huart6.Init.StopBits = UART_STOPBITS_1;
//  huart6.Init.Parity = UART_PARITY_NONE;
//  huart6.Init.Mode = UART_MODE_TX_RX;
//  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
//  if (HAL_UART_Init(&huart6) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN USART6_Init 2 */
//
//  /* USER CODE END USART6_Init 2 */
//
//}
//
///**
//  * Enable DMA controller clock
//  */
//static void MX_DMA_Init(void)
//{
//
//  /* DMA controller clock enable */
//  __HAL_RCC_DMA1_CLK_ENABLE();
//  __HAL_RCC_DMA2_CLK_ENABLE();
//
//  /* DMA interrupt init */
//  /* DMA1_Stream0_IRQn interrupt configuration */
//  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
//  /* DMA1_Stream6_IRQn interrupt configuration */
//  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
//  /* DMA2_Stream1_IRQn interrupt configuration */
//  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
//  /* DMA2_Stream6_IRQn interrupt configuration */
//  HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);
//
//}
//
///**
//  * @brief GPIO Initialization Function
//  * @param None
//  * @retval None
//  */
//static void MX_GPIO_Init(void)
//{
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
///* USER CODE BEGIN MX_GPIO_Init_1 */
///* USER CODE END MX_GPIO_Init_1 */
//
//  /* GPIO Ports Clock Enable */
//  __HAL_RCC_GPIOH_CLK_ENABLE();
//  __HAL_RCC_GPIOC_CLK_ENABLE();
//  __HAL_RCC_GPIOA_CLK_ENABLE();
//  __HAL_RCC_GPIOB_CLK_ENABLE();
//  __HAL_RCC_GPIOE_CLK_ENABLE();
//
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(cs_GPIO_Port, cs_Pin, GPIO_PIN_RESET);
//
//  /*Configure GPIO pin : cs_Pin */
//  GPIO_InitStruct.Pin = cs_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(cs_GPIO_Port, &GPIO_InitStruct);
//
///* USER CODE BEGIN MX_GPIO_Init_2 */
///* USER CODE END MX_GPIO_Init_2 */
//}
//
///* USER CODE BEGIN 4 */
//
///* USER CODE END 4 */
//
///**
//  * @brief  This function is executed in case of error occurrence.
//  * @retval None
//  */
//void Error_Handler(void)
//{
//  /* USER CODE BEGIN Error_Handler_Debug */
//	/* User can add his own implementation to report the HAL error return state */
//	__disable_irq();
//	while (1) {
//	}
//  /* USER CODE END Error_Handler_Debug */
//}
//
//#ifdef  USE_FULL_ASSERT
///**
//  * @brief  Reports the name of the source file and the source line number
//  *         where the assert_param error has occurred.
//  * @param  file: pointer to the source file name
//  * @param  line: assert_param error line source number
//  * @retval None
//  */
//void assert_failed(uint8_t *file, uint32_t line)
//{
//  /* USER CODE BEGIN 6 */
//  /* User can add his own implementation to report the file name and line number,
//     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
//  /* USER CODE END 6 */
//}
//#endif /* USE_FULL_ASSERT */
