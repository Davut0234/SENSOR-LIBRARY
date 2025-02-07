#include "hcsr_04.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>

// Initialize the HCSR04 sensor
void HCSR04_Init(HCSR04_HandleTypeDef *hcsr, TIM_HandleTypeDef *htim2, GPIO_TypeDef *port, uint32_t triggerPin, uint32_t echoPin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Assuming GPIOA for both Trigger and Echo pins

    // Configure Trigger Pin
    GPIO_InitStruct.Pin = triggerPin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(port, &GPIO_InitStruct);

    // Configure Echo Pin
    GPIO_InitStruct.Pin = echoPin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING; // Interrupt mode for Echo
    HAL_GPIO_Init(port, &GPIO_InitStruct);

    // Enable Timer clock
    __HAL_RCC_TIM2_CLK_ENABLE();

    // Configure TIM2 for measuring pulse width on Echo pin
    htim2->Instance = TIM2;
    htim2->Init.Prescaler = 0;
    htim2->Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2->Init.Period = 0xFFFF;
    htim2->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(htim2);

    // Store the pin configuration for later use
    hcsr->triggerPin = triggerPin;
    hcsr->echoPin = echoPin;
}

// Get the distance from the HCSR04 sensor
uint32_t HCSR04_GetDistance(HCSR04_HandleTypeDef *hcsr)
{
    uint32_t pulseWidth = 0;

    // Reset and start the timer for continuous measurement
    __HAL_TIM_SET_COUNTER(&htim2, 0);  // Reset the counter before starting measurement
    HAL_TIM_Base_Start(&htim2);  // Start the timer

    // Trigger the sensor (send a 10us pulse on the Trigger pin)
    HAL_GPIO_WritePin(GPIOA, hcsr->triggerPin, GPIO_PIN_SET);
    HAL_Delay(10); // Delay for 10ms to generate a pulse
    HAL_GPIO_WritePin(GPIOA, hcsr->triggerPin, GPIO_PIN_RESET);

    // Wait for the Echo pin to go high
    while (HAL_GPIO_ReadPin(GPIOA, hcsr->echoPin) == GPIO_PIN_RESET)
    {
        // Wait for Echo pin to go high
    }

    // Start timing when Echo pin goes high
    uint32_t start = __HAL_TIM_GET_COUNTER(&htim2);

    // Wait for the Echo pin to go low
    while (HAL_GPIO_ReadPin(GPIOA, hcsr->echoPin) == GPIO_PIN_SET)
    {
        // Wait for Echo pin to go low
    }

    // Measure pulse width
    pulseWidth = __HAL_TIM_GET_COUNTER(&htim2) - start;

    // Calculate distance (in cm, previously it was in mm)
    uint32_t distance = pulseWidth / 58; // Pulse width in microseconds, divided by 58 for mm distance
    distance /= 10; // Convert to cm from mm

    // Stop the timer after measurement
    HAL_TIM_Base_Stop(&htim2);

    return distance;
}

// Print the distance via UART
void HCSR04_PrintDistance(UART_HandleTypeDef *huart, uint32_t distance)
{
    char msg[20];
    if (distance > 0) {
        sprintf(msg, "Distance: %lu cm\n", distance);
    } else {
        sprintf(msg, "Distance: 0 cm\n"); // If no valid distance, show 0
    }
    HAL_UART_Transmit(huart, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}
