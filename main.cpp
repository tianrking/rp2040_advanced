#include "pico/stdlib.h"
#include "hardware/pio.h"
#include <stdio.h>

// PIO程序定义
const uint16_t blink_program_instructions[] = {
    0x80a0, //  0: pull   block
    0xe001, //  1: set    pins, 1    [1]
    0x80a0, //  2: pull   block
    0xe000, //  3: set    pins, 0    [1]
};

// 将程序包装在 pio_program_t 结构中
const struct pio_program blink_program = {
    .instructions = blink_program_instructions,
    .length = 4,
    .origin = -1,
};

int main() {
    // 初始化标准 IO
    stdio_init_all();

    // 等待串口准备就绪
    sleep_ms(2000);
    printf("PIO Blink program starting...\n");

    // 初始化 PIO
    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &blink_program);

    printf("PIO program loaded at offset %d\n", offset);

    // 配置状态机
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_set_pins(&c, 25, 1);
    pio_gpio_init(pio, 25);
    pio_sm_set_consecutive_pindirs(pio, sm, 25, 1, true);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);
    pio_sm_init(pio, sm, offset, &c);

    printf("State machine configured\n");

    // 启动状态机
    pio_sm_set_enabled(pio, sm, true);

    printf("State machine enabled, starting main loop\n");

    // 主循环
    int count = 0;
    pio_sm_put_blocking(pio, sm, 4); 
    sleep_ms(500);
    pio_sm_put_blocking(pio, sm, 1); 
    while (true) {

        // pio_sm_put_blocking(pio, sm, 1);  // 关闭 LED 500ms
        sleep_ms(500);
        if (++count % 10 == 0) {
            printf("Blink cycle: %d\n", count);
        }
    }
}