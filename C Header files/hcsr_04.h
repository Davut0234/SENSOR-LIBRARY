// hcsr_04.h

#ifndef HCSR_04_H
#define HCSR_04_H

#include "stm32f4xx_hal.h"
extern TIM_HandleTypeDef htim2; // Declare the TIM2 handle



typedef struct
{
    uint32_t triggerPin;
    uint32_t echoPin;
} HCSR04_HandleTypeDef;

void HCSR04_Init(HCSR04_HandleTypeDef *hcsr, TIM_HandleTypeDef *htim2, GPIO_TypeDef *port, uint32_t triggerPin, uint32_t echoPin);
uint32_t HCSR04_GetDistance(HCSR04_HandleTypeDef *hcsr);
void HCSR04_PrintDistance(UART_HandleTypeDef *huart, uint32_t distance);

#endif // HCSR_04_H
