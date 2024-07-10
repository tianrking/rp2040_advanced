cmake_minimum_required(VERSION 3.13)

# 引入 Pico-SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# 项目名称和语言设置
project(hello_pio C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# 初始化 Pico-SDK
pico_sdk_init()

# 创建可执行文件
add_executable(hello_pio
    main.cpp
)

# pico_generate_pio_header(hello_pio ${CMAKE_CURRENT_LIST_DIR}/hello.pio)

target_sources(hello_pio PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        )


# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_device
# for TinyUSB device support and tinyusb_board for the additional board support library used by the example
target_link_libraries(hello_pio PUBLIC 
	pico_stdlib 
    hardware_pio
	)

target_include_directories(hello_pio PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
#target_compile_definitions(dev_hid_composite PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)
# 设置 C 和 C++ 编译器标志
SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

# Pico 配置
pico_enable_stdio_usb(hello_pio 1)
pico_enable_stdio_uart(hello_pio 0)
add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

# 生成额外的输出文件
pico_add_extra_outputs(hello_pio)