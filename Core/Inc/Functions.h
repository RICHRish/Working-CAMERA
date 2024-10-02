/*
 * Functions.h
 *
 *  Created on: Sep 30, 2024
 *      Author: kriti
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_



#include "variables.h"
#include "stdarg.h"

int buffersize(char *buff);
int buffer(uint8_t *get_size);


void OBC_HANDSHAKE();
uint32_t IMAGE_CAPTURE();

void CS_Enable_RGB();
void CS_Disable_RGB();
void CS_Enable_NIR();
void CS_Disable_NIR();
void OCP_EN();

#endif /* INC_FUNCTIONS_H_ */
