// sevenSegment_4_Digit.h
#ifndef SEVENSEGMENT_4_DIGIT_H
#define SEVENSEGMENT_4_DIGIT_H

#include "stm32f4xx_hal.h"

/**
 * @brief SevenSegment_HandleTypeDef structure holds GPIO configuration for the 4-digit seven-segment display.
 */
typedef struct {
    GPIO_TypeDef *segmentPort;     /**< GPIO port for segment pins. */
    uint16_t segmentPins[8];       /**< GPIO pins for segments (A-G, DP). */
    GPIO_TypeDef *digitPort;       /**< GPIO port for digit pins. */
    uint16_t digitPins[4];         /**< GPIO pins for digit control (D1-D4). */
} SevenSegment_HandleTypeDef;

/**
 * @brief Configures the seven-segment display with given GPIO ports and pins.
 *
 * @param h7seg Pointer to SevenSegment_HandleTypeDef structure.
 * @param segmentPort GPIO port for segment control.
 * @param segmentPins Array of 8 GPIO pins for segment control.
 * @param digitPort GPIO port for digit control.
 * @param digitPins Array of 4 GPIO pins for digit control.
 */
void SevenSegment_Config(SevenSegment_HandleTypeDef *h7seg, GPIO_TypeDef *segmentPort, uint16_t segmentPins[8], GPIO_TypeDef *digitPort, uint16_t digitPins[4]);

/**
 * @brief Initializes the seven-segment display by resetting all segments and digits.
 *
 * @param h7seg Pointer to SevenSegment_HandleTypeDef structure.
 */
void SevenSegment_Init(SevenSegment_HandleTypeDef *h7seg);

/**
 * @brief Displays a specific digit at a given position on the seven-segment display.
 *
 * @param h7seg Pointer to SevenSegment_HandleTypeDef structure.
 * @param digit The digit to display (0-9).
 * @param position The position to display the digit (0-3 for 4-digit displays).
 */
void SevenSegment_DisplayDigit(SevenSegment_HandleTypeDef *h7seg, uint8_t digit, uint8_t position);
void SevenSegment_ClearDisplay(SevenSegment_HandleTypeDef *h7seg);
void sevenSegment_AllClear();
/**
 * @brief Displays a multi-digit number on the seven-segment display for a specified duration.
 *
 * @param h7seg Pointer to SevenSegment_HandleTypeDef structure.
 * @param number The number to display (0-9999).
 * @param duration_ms Duration in milliseconds for which the number should be displayed.void SevenSegment_DisplayNumber(SevenSegment_HandleTypeDef *h7seg, uint32_t number, uint32_t duration_ms);
 */


#endif // SEVENSEGMENT_4_DIGIT_H
