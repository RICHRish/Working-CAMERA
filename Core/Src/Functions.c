/*
 * Functions.c
 *
 *  Created on: Sep 30, 2024
 *      Author: kriti
 */

#include "functions.h"
#include <stdlib.h>
#include<math.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include <configuration.h>


#ifdef DEBUG_MODE
#ifndef TRACE_MODE

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
//	char log[100];
//	sprintf(log,"Data received of size %d", sizeof(log));
//	HAL_UART_Transmit(&DEBUG_UART, log,sizeof(log),1000);
//}
int buffersize(char *buff) {
	int i = 0;
	while (*buff++ != '\0')
		i++;
	return i;
}
void myprintf(const char *fmt, ...) {
	static char temp[100];
	va_list args;
	va_start(args, fmt);
	vsnprintf(temp, sizeof(temp), fmt, args);
	va_end(args);
	int len = buffersize(temp);

#ifdef CDC_USB_DEBUG
	CDC_Transmit_FS((uint8_t*) temp, len);
//	HAL_Delay(1);
#endif

#ifdef UART_DEBUG
	HAL_UART_Transmit(&DEBUG_UART, (uint8_t*) temp, len, 1000);
//	while (DEBUG_TX_FLAG != 1) {
//	}
//	DEBUG_TX_FLAG = 0;
#endif
}

#endif // TRACE_MODE
#endif // DEBUG_MODE

uint8_t obc_data, rx_data[7],i;

void OBC_HANDSHAKE() {
	while (OBC_RX_FLAG != 1) {
		if (HAL_UART_Receive(&huart4, &obc_data, 1, 1000) == HAL_OK) {
			HAL_UART_Transmit(&DEBUG_UART, &obc_data, 1, 100);
			rx_data[i++] = obc_data;
			i = i % 8;
			if (i == 7)
				OBC_RX_FLAG = 1;
		}

	}
	if (OBC_RX_FLAG == 1) {
		HAL_UART_Transmit(&huart4, rx_data, sizeof(rx_data), 1000);
		HAL_UART_Transmit(&DEBUG_UART, &rx_data, 1, 100);
		}
	}
//void OBC_HANDSHAKE() {
//
//	HAL_UART_Receive_IT(&OBC_UART, OBC_HANDSHAKE_RX, 5);
//	while (OBC_RX_FLAG != 1) {
//		myprintf("waiting for data to be received from OBC\r\n");
//		HAL_Delay(2000);
//	}
//	OBC_RX_FLAG = 0;
//	myprintf("Data received from OBC\r\n");
//	HAL_Delay(1);
//
//	for (int i = 0; i < 5; i++) {
//		OBC_HANDSHAKE_TX[i] = OBC_HANDSHAKE_RX[i];
//	}
//	if (HAL_UART_Transmit(&OBC_UART, OBC_HANDSHAKE_TX, 5, 5000) == HAL_OK) {
//		myprintf("ACK Transmitted to OBC successfully...\r\n");
//		HAL_Delay(1);
//	} else {
//		myprintf("data transmission error.....\r\n");
//		HAL_Delay(1);
//	}
//	memset(OBC_HANDSHAKE_RX, '\0', 5);
//}


uint32_t IMAGE_CAPTURE(){
	uint8_t CAM_tx[] = { 'C', 'A', 'M', 'O', 'N' };
	uint32_t size1=0;


	HAL_UART_Transmit(&RGB_UART, CAM_tx, sizeof(CAM_tx), 1000);
	HAL_UART_Transmit(&NIR_UART, CAM_tx, sizeof(CAM_tx),1000);
	if (HAL_OK
			== HAL_UART_Receive(&RGB_UART, rgb_img_size, sizeof(rgb_img_size),
					7000)) {
		HAL_UART_Transmit(&DEBUG_UART,(uint8_t*) "Image size is : ",
				sizeof("Image size is : "), 1000);

		ptr = atoi((char*)rgb_img_size);
		data_rec = (uint8_t *) malloc(ptr);
//		HAL_UART_Receive_DMA(&RGB_UART, data_rec, ptr);
		if(HAL_UART_Receive(&RGB_UART, data_rec, ptr, 1000) == HAL_OK){
			HAL_UART_Transmit(&RGB_UART, data_rec, ptr,1000);
		}


		HAL_UART_Transmit(&DEBUG_UART, rgb_img_size, sizeof(rgb_img_size), 1000);
		RGB_CAM = 1;
		//HAL_Delay(20000);

	}
 char logs[100];
	while(1){
		if (RGB_CAM == 1) {
			HAL_UART_Receive_DMA(&RGB_UART, rgb_rx, rgb_img_size);
//			do {
//
//				if (HAL_OK
//						== HAL_UART_Receive(&RGB_UART, &rgb_img, sizeof(rgb_img),
//								1000)) {
//					rgb_rx[rgb++] = rgb_img;
////					HAL_UART_Transmit(&DEBUG_UART, &rgb_img, sizeof(rgb_img), 1000);
//					if(rgb%1000 == 0){
//						sprintf(logs, "\n Data size received is %d",rgb);
//
//
//						HAL_UART_Transmit(&DEBUG_UART, logs, sizeof(logs),1000);
//					}
//
//				}
//			} while (rgb_img != 0xd9);

//			rgb_rx[rgb++] = '\0';
//				RGB_CAM = 0;
//
//				HAL_UART_Transmit(&DEBUG_UART, "\nData size received is ", sizeof("\nData size received is "),1000);
//
//				HAL_UART_Transmit(&DEBUG_UART, &rgb_rx, sizeof(rgb_rx),1000);
//           myprintf()

			//		HAL_UART_Transmit(&huart2, rx, strlen(rx), 1000);
			//		memset(rx, "\0", sizeof(rx));
			//		while(i<= ptr){
			//			if(HAL_OK == HAL_UART_Receive(&huart8, &img, sizeof(img), 1000)){
			//						rx[i++]=img;
			//					}
			//
			//		}
			// Additional processing can be done here
//			HAL_UART_Transmit(&DEBUG_UART, rgb_rx, ptr, 10000);
//			//		x=100;
//			rgb = 0;

		}
//		if (HAL_OK
//				== HAL_UART_Receive(&NIR_UART, nir_img_size, sizeof(nir_img_size),
//						3000)) {
//			HAL_UART_Transmit(&DEBUG_UART,(uint8_t*) "Image size is : ",
//					sizeof("Image size is : "), 1000);
//
//			HAL_UART_Transmit(&DEBUG_UART, nir_img_size, sizeof(nir_img_size), 1000);
//			ptr = atoi((char*)nir_img_size);
//			NIR_CAM = 1;
//
//		}
//
//		if (NIR_CAM == 1) {
//			do {
//
//				if (HAL_OK
//						== HAL_UART_Receive(&NIR_UART, &nir_img, sizeof(nir_img),
//								1000)) {
//					nir_rx[nir++] = nir_img;
//
//					HAL_UART_Transmit(&DEBUG_UART, &nir_img, sizeof(nir_img), 1000);
//				}
//			} while (nir_img != 0xd9);
//			nir_rx[nir++] = '\0';
//			NIR_CAM = 0;
//			//		HAL_UART_Transmit(&huart2, rx, strlen(rx), 1000);
//			//		memset(rx, "\0", sizeof(rx));
//			//		while(i<= ptr){
//			//			if(HAL_OK == HAL_UART_Receive(&huart8, &img, sizeof(img), 1000)){
//			//						rx[i++]=img;
//			//					}
//			//
//			//		}
//			// Additional processing can be done here
//			HAL_UART_Transmit(&DEBUG_UART, nir_rx, ptr, 10000);
//			//		x=100;
//			nir = 0;
//		}

	}
	return 0;
}
	void CS_Enable_RGB() {
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_Delay(1);
	}

	void CS_Disable_RGB() {
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_Delay(1);
	}
	void CS_Enable_NIR() {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_Delay(1);
	}

	void CS_Disable_NIR() {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_Delay(1);
	}

	void OCP_EN() {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_Delay(100);
	}
