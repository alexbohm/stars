
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
class status_led {
   private:
    /**
     * @brief The GPIO port for the LED.
     *
     */
    GPIO_TypeDef* const port;
    /**
     * @brief The GPIO pin for the LED.
     *
     */
    const uint16_t pin;

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
    status_led(GPIO_TypeDef* port, uint16_t pin);
    /**
     * @brief Initialize the hardware for the LED.
     *
     * This function will initialize the port, pin, and appropriate GPIO clock
     * for the LED.
     *
     */
    void init();
    /**
     * @brief Deinitialize the hardware for the LED.
     *
     * This function will deinitialize the port and pin for the LED. It
     * does not disable the GPIO clock since other pins may also have enabled
     * the clock.
     *
     */
    void deinit();
    /**
     * @brief Set the state of the LED.
     *
     * @param state The desired state of the LED. Truthy values are illuminated,
     * False values are off.
     */
    void set_state(bool state);
    /**
     * @brief Get the state of the LED.
     *
     * @return true The LED is illuminated.
     * @return false The LED is off.
     */
    bool get_state() const;
    /**
     * @brief Toggle the state of the LED.
     *
     */
    void toggle();
};

}  // namespace device
