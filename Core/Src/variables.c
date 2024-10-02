/*
 * variables.c
 *
 *  Created on: Sep 29, 2024
 *      Author: kriti
 */
#include "variables.h"

///***-----OBC HANDSHAKE------****///
uint8_t OBC_HANDSHAKE_RX[7];
uint8_t OBC_HANDSHAKE_TX[7];

/// OBC FLAGS
uint8_t OBC_RX_FLAG = 0;
uint8_t OBC_TX_FLAG = 0;



////-----OBC_CAM_MISSION_COMMUNICTAION---//
uint8_t OBC_COMMAND[3];
uint8_t OBC_CMD_RX[7];

// Receiving buffer//
uint8_t rgb_rx[IMG_BUFF];
uint8_t nir_rx[IMG_BUFF];

//pointer//
uint32_t ptr;

// Image size//
uint8_t rgb_img_size[5];
uint8_t nir_img_size[5];

//Whole image//
uint8_t rgb_img;
uint8_t nir_img;

// Camera flags//
uint32_t rgb = 0;
uint32_t nir = 0;
uint8_t RGB_CAM = 0;
uint8_t NIR_CAM = 0;

