

#pragma once

#include <stdint.h>
#include <stm32f4xx_hal.h>

namespace device {
class motion_sensor {
   private:
    GPIO_TypeDef* const gpio_port = nullptr;
    const uint16_t gpio_pin = 0;

   public:
    motion_sensor(GPIO_TypeDef* gpio_port, uint16_t gpio_pin);
    void init();

    bool is_motion_detected();
};
}  // namespace device
