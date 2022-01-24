
#include "motion_sensor.h"
namespace device {
motion_sensor::motion_sensor(GPIO_TypeDef* gpio_port, uint16_t gpio_pin)
    : gpio_port(gpio_port), gpio_pin(gpio_pin) {
}
void motion_sensor::init() {
    // Enable the appropriate GPIO clock based on the GPIO port.
    if (gpio_port == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (gpio_port == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (gpio_port == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } else if (gpio_port == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    } else if (gpio_port == GPIOE) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    } else if (gpio_port == GPIOH) {
        __HAL_RCC_GPIOH_CLK_ENABLE();
    }

    GPIO_InitTypeDef init_struct = {
        .Pin = gpio_pin,
        .Mode = GPIO_MODE_INPUT,
        .Pull = GPIO_NOPULL,
    };
    HAL_GPIO_Init(gpio_port, &init_struct);
}

bool motion_sensor::is_motion_detected() {
    return HAL_GPIO_ReadPin(gpio_port, gpio_pin) == GPIO_PIN_SET;
}
}  // namespace device
