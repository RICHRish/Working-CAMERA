/*
 * configuration.h
 *
 *  Created on: Sep 30, 2024
 *      Author: kriti
 */

#ifndef INC_CONFIGURATION_H_
#define INC_CONFIGURATION_H_


#include "main.h"

#define DEBUG_MODE
//#define CDC_USB_DEBUG
#define UART_DEBUG
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart8;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;
extern DMA_HandleTypeDef hdma_uart8_tx;
extern DMA_HandleTypeDef hdma_uart8_rx;
extern DMA_HandleTypeDef hdma_usart6_tx;
extern DMA_HandleTypeDef hdma_usart6_rx;

#define RGB_UART	    huart8
#define NIR_UART	    huart6
#define OBC_UART  	    huart4
#define DEBUG_UART	    huart2

#define ACK LEN           3
#define IMG_BUFF        18004
#endif /* INC_CONFIGURATION_H_ */
