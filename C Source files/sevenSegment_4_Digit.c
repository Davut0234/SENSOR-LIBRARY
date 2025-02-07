#include "sevenSegment_4_Digit.h"

static const uint8_t segmentMap[10] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90
};



void SevenSegment_Config(SevenSegment_HandleTypeDef *h7seg, GPIO_TypeDef *segmentPort, uint16_t segmentPins[8], GPIO_TypeDef *digitPort, uint16_t digitPins[4]) {
    h7seg->segmentPort = segmentPort;
    for (int i = 0; i < 8; i++) {
        h7seg->segmentPins[i] = segmentPins[i];
    }
    h7seg->digitPort = digitPort;
    for (int i = 0; i < 4; i++) {
        h7seg->digitPins[i] = digitPins[i];
    }
}

void SevenSegment_Init(SevenSegment_HandleTypeDef *h7seg) {
    // Initialize all segment and digit pins
    for (int i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(h7seg->segmentPort, h7seg->segmentPins[i], GPIO_PIN_RESET);
    }
    for (int i = 0; i < 4; i++) {
        HAL_GPIO_WritePin(h7seg->digitPort, h7seg->digitPins[i], GPIO_PIN_RESET);
    }
}

void SevenSegment_DisplayDigit(SevenSegment_HandleTypeDef *h7seg, uint8_t digit, uint8_t position) {
    if (digit > 9 || position > 3) return;

    uint8_t value = segmentMap[digit];

    // Set segment pins
    for (int i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(h7seg->segmentPort, h7seg->segmentPins[i], (value >> i) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    // Activate the corresponding digit pin
    HAL_GPIO_WritePin(h7seg->digitPort, h7seg->digitPins[position], GPIO_PIN_SET);
}

void SevenSegment_ClearDigit(SevenSegment_HandleTypeDef *h7seg, uint8_t position) {
    if (position < 4) {
        HAL_GPIO_WritePin(h7seg->digitPort, h7seg->digitPins[position], GPIO_PIN_RESET);
    }
}

void SevenSegment_All_Digit_Clear(SevenSegment_HandleTypeDef *h7seg) {
    // Clear all digits
    for (int i = 0; i < 4; i++) {
        SevenSegment_ClearDigit(h7seg, i);
    }
}

void SevenSegment_DisplayNumber(SevenSegment_HandleTypeDef *h7seg, uint32_t number, uint32_t duration_ms) {
    if (number > 9999) return;

    // Split the number into individual digits
    uint8_t digits[4] = {
        (number / 1000) % 10,
        (number / 100) % 10,
        (number / 10) % 10,
        number % 10
    };

    uint32_t start_time = HAL_GetTick();
    uint32_t last_update_time = HAL_GetTick();
    uint8_t current_digit = 0;

    while (HAL_GetTick() - start_time < duration_ms) {
        uint32_t current_time = HAL_GetTick();

        // Update display every 5ms (multiplexing)
        if (current_time - last_update_time >= 5) {
            // Clear the previous digit
            SevenSegment_ClearDigit(h7seg, current_digit);

            // Move to the next digit
            current_digit = (current_digit + 1) % 4;

            // Display the new digit
            SevenSegment_DisplayDigit(h7seg, digits[current_digit], current_digit);

            last_update_time = current_time;  // Update the last update time
        }
    }

    // Clear all digits after the display duration is over
    SevenSegment_All_Digit_Clear(h7seg);
}
