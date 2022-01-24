
#include "status_led.h"

namespace device {

status_led::status_led(GPIO_TypeDef* port, uint16_t pin)
    : port(port), pin(pin) {
}

void status_led::init() {
    // Enable the appropriate GPIO clock based on the GPIO port.
    if (port == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (port == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (port == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } else if (port == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    } else if (port == GPIOE) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    } else if (port == GPIOH) {
        __HAL_RCC_GPIOH_CLK_ENABLE();
    }

    // Pack the configuration for the LED hardware into a struct.
    GPIO_InitTypeDef GPIO_InitStruct;
    // Use the desired pin number
    GPIO_InitStruct.Pin = pin;
    // Use open drain mode.
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    // Don't use any pull up/pull down resistors
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    // Configure for low frequency since we don't have to switch the pin fast.
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    // Initialize the port and pin with our configuration.
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}
void status_led::deinit() {
    // Deinitialize the pin on the GPIO port.
    HAL_GPIO_DeInit(port, pin);

    // NOTE: We cannot safely disable the GPIO clock without coordination
    // from higher level sofware since the clock is shared between many GPIO
    // pins.
}
void status_led::set_state(bool state) {
    if (state) {
        // Set the GPIO pin to GND, which should illuminate the LED.
        HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
    } else {
        // Set the GPIO pin to 3.3V, which should turn off the LED.
        HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
    }
}

bool status_led::get_state() const {
    // Read the state of the LED directly from the GPIO pin.
    return HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET;
}

void status_led::toggle() {
    HAL_GPIO_TogglePin(port, pin);
}

}  // namespace device
