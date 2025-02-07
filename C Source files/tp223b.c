/*
 * tp223b.c
 *
 *  Created on: May 1, 2024
 *      Author: Davut Beyazkaya
 */

#include "tp223b.h"

uint8_t readTouchSensor(){

	uint8_t touchValue = 0;
	touchValue = HAL_GPIO_ReadPin(TOUCH_PORT, TOUCH_PIN);
	return touchValue;
}

uint8_t toggleTouchSensor(){

	uint8_t touchValue = 0;
	touchValue = HAL_GPIO_ReadPin(TOUCH_PORT, TOUCH_PIN);
	return !touchValue;
}

uint32_t getTouchTime(){

	uint32_t touchStartTime = HAL_GetTick();
	while(1){
		uint8_t touchValue = readTouchSensor();
		if (touchValue == 0) {
			break;
		}
	}
	uint32_t currentTime = HAL_GetTick();
	uint32_t touchDuration = currentTime - touchStartTime;
	return touchDuration;
}

