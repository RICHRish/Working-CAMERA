/*
 * variables.h
 *
 *  Created on: Sep 29, 2024
 *      Author: kriti
 */

#ifndef INC_VARIABLES_H_
#define INC_VARIABLES_H_

#include <configuration.h>
#include "string.h"


extern uint8_t OBC_HANDSHAKE_RX[7];
extern uint8_t OBC_HANDSHAKE_TX[7];



////FLAGS////

extern uint8_t OBC_RX_FLAG;
extern uint8_t OBC_TX_FLAG;

// OBC-CAM COMMUNICATION//
extern uint8_t OBC_COMMAND[3];
extern uint8_t OBC_CMD_RX[7];

//BUFFER//
extern uint8_t rgb_rx[IMG_BUFF];
extern uint8_t nir_rx[IMG_BUFF];
//PONIER//
extern uint32_t ptr;
// IMG SIZE//
extern uint8_t rgb_img_size[5];
extern uint8_t nir_img_size[5];
//WHOLE IMAGE//
extern uint8_t rgb_img;
extern uint8_t nir_img;

extern uint32_t rgb;
extern uint32_t nir;
extern uint8_t RGB_CAM;
extern uint8_t NIR_CAM;



#endif /* INC_VARIABLES_H_ */
