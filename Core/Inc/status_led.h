
#pragma once

#include <stm32f4xx_hal.h>

namespace device {

/**
 * @brief A status LED driver class.
 *
 * This class implements an LED with the GPIO sinking the current.
 * V+     Resistor     LED    GPIO
 * V+-----/\/\/\/------>|-----GPIO
 *
 */
template <bool enabled = false>
class status_led {
   private:
    /**
     * @brief The GPIO port for the LED.
     *
     */
    GPIO_TypeDef* const port = nullptr;
    /**
     * @brief The GPIO pin for the LED.
     *
     */
    const uint16_t pin = 0;

   public:
    /**
     * @brief Construct a new status LED.
     *
     * NOTE: Does not initialize the hardware, use the init() method to
     * initialize hardware.
     *
     * @param port The GPIO port connected to the LED.
     * @param pin The GPIO pin connected to the LED.
     */
    template <bool e = enabled>
    requires(enabled) status_led(GPIO_TypeDef* port, uint16_t pin)
        : port(port), pin(pin) {
    }

    template <bool e = enabled>
    requires(!enabled) status_led(GPIO_TypeDef* port, uint16_t pin) {
        UNUSED(port);
        UNUSED(pin);
    }

    template <bool e = enabled>
    requires(enabled) void init() {
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
        // Configure for low frequency since we don't have to switch the pin
        // fast.
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

        // Initialize the port and pin with our configuration.
        HAL_GPIO_Init(port, &GPIO_InitStruct);
    }
    template <bool e = enabled>
    requires(!enabled) void init() {
    }
    /**
     * @brief Deinitialize the hardware for the LED.
     *
     * This function will deinitialize the port and pin for the LED. It
     * does not disable the GPIO clock since other pins may also have enabled
     * the clock.
     *
     */
    template <bool e = enabled>
    requires(enabled) void deinit() {
        // Deinitialize the pin on the GPIO port.
        HAL_GPIO_DeInit(port, pin);

        // NOTE: We cannot safely disable the GPIO clock without coordination
        // from higher level sofware since the clock is shared between many GPIO
        // pins.
    }
    /**
     * @brief Set the state of the LED.
     *
     * @param state The desired state of the LED. Truthy values are illuminated,
     * False values are off.
     */
    template <bool e = enabled>
    requires(enabled) void set_state(bool state) {
        if (state) {
            // Set the GPIO pin to GND, which should illuminate the LED.
            HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
        } else {
            // Set the GPIO pin to 3.3V, which should turn off the LED.
            HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
        }
    }
    template <bool e = enabled>
    requires(!enabled) void set_state(bool state) {
        UNUSED(state);
    }
    /**
     * @brief Get the state of the LED.
     *
     * @return true The LED is illuminated.
     * @return false The LED is off.
     */
    template <bool e = enabled>
    requires(enabled) bool get_state() const {
        // Read the state of the LED directly from the GPIO pin.
        return HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET;
    }
    /**
     * @brief Toggle the state of the LED.
     *
     */
    template <bool e = enabled>
    requires(enabled) void toggle() {
        HAL_GPIO_TogglePin(port, pin);
    }
};

}  // namespace device
