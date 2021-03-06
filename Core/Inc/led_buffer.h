
#pragma once

#include <stm32f4xx_hal.h>

#include <array>
#include <cstring>

namespace device {

typedef struct __attribute__((packed)) {
    uint8_t global_brightness : 5 = 0b11111;
    uint8_t id : 3 = 0b111;
    std::array<uint8_t, 3> led{0x00, 0x00, 0x00};
} sk9822;

template <std::size_t NUM_LEDS>
class sk9822_buffer {
   private:
    uint8_t active_index = 0;
    uint8_t inactive_index = 1;
    std::array<std::array<sk9822, NUM_LEDS + 2>, 2> buffer;

    SPI_HandleTypeDef* const spi_handle = nullptr;

   public:
    static constexpr std::size_t size() {
        return NUM_LEDS;
    }

    sk9822_buffer(SPI_HandleTypeDef& spi) : spi_handle(&spi) {
        for (auto& b : buffer) {
            // Zero packet first.
            b[0].id = 0b000;
            b[0].global_brightness = 0b00000;
            b[0].led[0] = 0x00;
            b[0].led[1] = 0x00;
            b[0].led[2] = 0x00;

            // High packet last.
            b[b.size() - 1].id = 0b111;
            b[b.size() - 1].global_brightness = 0b11111;
            b[b.size() - 1].led[0] = 0xFF;
            b[b.size() - 1].led[1] = 0xFF;
            b[b.size() - 1].led[2] = 0xFF;
        }
    }

    void init() {
    }

    void update() {
        std::swap(active_index, inactive_index);
        // Wait for the DMA to be ready.
        while (HAL_DMA_GetState(spi_handle->hdmatx) != HAL_DMA_STATE_READY) {
        }
        // Transfer the active data to the LEDs.
        HAL_SPI_Transmit_DMA(
            spi_handle, reinterpret_cast<uint8_t*>(buffer[active_index].data()),
            sizeof(sk9822) * buffer[active_index].size());
        // Copy the active data to the inactive buffer.
        std::memcpy(buffer[inactive_index].data(), buffer[active_index].data(),
                    sizeof(sk9822) * buffer[inactive_index].size());
    }

    sk9822& operator[](std::size_t index) {
        return buffer[inactive_index][index + 1];
    }
};
}  // namespace device
