/*
 * tp223b.h
 *
 *  Created on: May 1, 2024
 *      Author: Arif Mandal
 */

#ifndef INC_TP223B_H_
#define INC_TP223B_H_

#include "main.h"

#define TOUCH_PORT GPIOE
#define TOUCH_PIN  GPIO_PIN_1

uint8_t readTouchSensor(void);
uint8_t toggleTouchSensor(void);
uint32_t getTouchTime(void);

#endif /* INC_TP223B_H_ */
