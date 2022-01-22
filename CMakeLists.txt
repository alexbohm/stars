project(stars ASM C CXX)

cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

# HAL and CMSIS need to have the microcontroller defined.
# We define this at a global level since this project only targets
# this single type of microcontroller.
add_compile_definitions(STM32F411xE)

add_library(STM32::F4 INTERFACE IMPORTED)
target_compile_options(STM32::F4
  INTERFACE

  # Options for CPU
  -mcpu=cortex-m4
  # Options for FPU (floating point unit)
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard

  -mthumb

  -Wall
  # Place each data item and each function into its own section.
  # This allows the linker to perform optimizations during the linking
  # stage.
  -fdata-sections
  -ffunction-sections

  # Remove unused/dead code during the linking stage. This relies on
  # the -fdata-sections and -ffunction-sections options.
  -Wl,--gc-sections
)
target_link_options(STM32::F4
  INTERFACE
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard
  -Wall
  -fdata-sections
  -ffunction-sections
  -Wl,--gc-sections
)



add_library(CMSIS INTERFACE)
target_compile_definitions(CMSIS INTERFACE USE_HAL_DRIVER)
target_include_directories(CMSIS
  INTERFACE
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    Drivers/CMSIS/Include
)
target_link_libraries(CMSIS
  INTERFACE
    STM32::F4
)

add_library(HAL)
target_sources(HAL
  PUBLIC
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cec.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cryp_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dcmi_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dfsdm.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma2d.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dsi.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_eth.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpi2c_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpsmbus.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_fmpsmbus_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hash_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_hcd.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2s_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_irda.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_iwdg.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_lptim.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_mmc.c
    # Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_msp_template.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nand.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_nor.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pccard.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_qspi.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sai_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sd.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_smartcard.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_smbus.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spdifrx.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
    # Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_timebase_rtc_alarm_template.c
    # Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_timebase_rtc_wakeup_template.c
    # Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_timebase_tim_template.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_wwdg.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_adc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_crc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_dac.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_dma2d.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_dma.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_exti.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmpi2c.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_gpio.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_i2c.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_lptim.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_pwr.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_rcc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_rng.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_rtc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_sdmmc.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_spi.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_tim.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usart.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_utils.c
)
target_include_directories(HAL
PUBLIC
  Drivers/STM32F4xx_HAL_Driver/Inc
  Core/Inc
)
target_link_libraries(HAL
  PUBLIC
    CMSIS
)


add_executable(stars)
target_include_directories(stars
  PUBLIC
    Core/Inc
)
target_sources(stars
  PUBLIC
    Core/Src/led_buffer.cc
    Core/Src/dma.c
    Core/Src/gpio.c
    Core/Src/main.cc
    Core/Src/spi.c
    Core/Src/stm32f4xx_hal_msp.c
    Core/Src/stm32f4xx_it.c
    Core/Src/system_stm32f4xx.c
    startup_stm32f411xe.s
    # Core/Src/.c
)
target_link_libraries(stars
  PUBLIC
    STM32::F4
    HAL
    c
    m
    nosys
    -T../STM32F411CEUx_FLASH.ld
)
# Generate a binary file for DFU using bootloaders.
add_custom_target(stars.bin ALL DEPENDS $<TARGET_FILE:stars>)
add_custom_command(TARGET stars.bin COMMAND ${CMAKE_OBJCOPY} ARGS -O binary -S $<TARGET_FILE:stars> stars.bin)
