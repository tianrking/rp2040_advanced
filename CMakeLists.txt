cmake_minimum_required(VERSION 3.13)
# set(PICO_SDK_PATH  /Users/icola/rp2040/pico-sdk)  #此处设置PICO SDK实际路径

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include($ENV{PICO_SDK_PATH}/../pico-extras/pico_sdk_import.cmake)

include(pico_sdk_import.cmake)
# include(FreeRTOS_Kernel_import.cmake)

set(PRJ_NAME rp2040_ssd1306)
project(${PRJ_NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${PRJ_NAME}
	main.cpp
        libs/U8g2/csrc/u8x8_8x8.c
        libs/U8g2/csrc/u8g2_setup.c
        libs/U8g2/csrc/u8x8_setup.c
        libs/U8g2/csrc/u8g2_d_setup.c
        libs/U8g2/csrc/u8x8_display.c
        libs/U8g2/csrc/u8x8_cad.c
        libs/U8g2/csrc/u8x8_byte.c
        libs/U8g2/csrc/u8g2_font.c
        libs/U8g2/csrc/u8g2_fonts.c
        libs/U8g2/csrc/u8x8_gpio.c
        libs/U8g2/csrc/u8g2_hvline.c
        libs/U8g2/csrc/u8g2_buffer.c
        libs/U8g2/csrc/u8g2_bitmap.c
        libs/U8g2/csrc/u8g2_d_memory.c
        libs/U8g2/csrc/u8g2_ll_hvline.c
        libs/U8g2/csrc/u8g2_intersection.c
        libs/U8g2/csrc/u8g2_cleardisplay.c
        libs/U8g2/csrc/u8x8_d_ssd1306_128x64_noname.c
)

target_include_directories(${PRJ_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/U8g2/csrc
        )

# target_link_libraries(${PRJ_NAME} PRIVATE pico_stdlib  hardware_spi  hardware_dma  FreeRTOS-Kernel FreeRTOS-Kernel-Heap4)
target_link_libraries(${PRJ_NAME} PRIVATE pico_stdlib  hardware_spi  hardware_dma)
pico_add_extra_outputs(${PRJ_NAME})