#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/dma.h"
// #include "FreeRTOS.h"
// #include "task.h"
#include "u8g2.h"

// #define OLED_TASK_PRIORITY      (tskIDLE_PRIORITY + 1UL)
// #define OTHER_TASK_PRIORITY     (tskIDLE_PRIORITY + 2UL)
//PIN settings
#define SPI_PORT0               spi0
#define SPI0_SPEED              9000 * 1000
#define PIN_OLED_DC             2
#define PIN_OLED_MOSI           3
#define PIN_OLED_MISO           4 //用不上，无需焊接
#define PIN_OLED_CS             5
#define PIN_OLED_SCK            6
#define PIN_OLED_RES            7 //拉低

// 烟花的9种状态
const uint8_t epd_bitmap_frame_01[]  = {0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00};
const uint8_t epd_bitmap_frame_02[]  = {0x00, 0x00, 0x28, 0x10, 0x28, 0x00, 0x00, 0x00};
const uint8_t epd_bitmap_frame_03[]  = {0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00, 0x00};
const uint8_t epd_bitmap_frame_04[]  = {0x82, 0x44, 0x28, 0x00, 0x28, 0x44, 0x82, 0x00};
const uint8_t epd_bitmap_frame_05[]  = {0x82, 0x44, 0x00, 0x10, 0x00, 0x44, 0x82, 0x00};
const uint8_t epd_bitmap_frame_06[]  = {0x82, 0x00, 0x10, 0x38, 0x10, 0x00, 0x82, 0x00};
const uint8_t epd_bitmap_frame_07[]  = {0x00, 0x10, 0x10, 0x6c, 0x10, 0x10, 0x00, 0x00};
const uint8_t epd_bitmap_frame_08[]  = {0x10, 0x10, 0x00, 0xc6, 0x00, 0x10, 0x10, 0x00};
const uint8_t epd_bitmap_frame_09[]  = {0x10, 0x00, 0x00, 0x82, 0x00, 0x00, 0x10, 0x00};

const unsigned char* epd_bitmap_allArray[9] = {epd_bitmap_frame_01, epd_bitmap_frame_02, epd_bitmap_frame_03, epd_bitmap_frame_04, epd_bitmap_frame_05, epd_bitmap_frame_06, epd_bitmap_frame_07, epd_bitmap_frame_08, epd_bitmap_frame_09};

const int sprite_count = 10;
uint8_t sprite_x[sprite_count];
uint8_t sprite_y[sprite_count];
uint8_t sprite_img[sprite_count];


// TaskHandle_t                    OLEDTask_Handler;
u8g2_t                          u8g2;
uint16_t                        displayWidth;
uint16_t                        displayHeight;

uint8_t                         dma_spi0_tx;
dma_channel_config              dma_spi0_cfg;


//------------------------------------------------------------------
// millis()返回启动以来的毫秒数
//------------------------------------------------------------------
uint32_t millis()
{
    return  to_ms_since_boot( get_absolute_time());
}
//------------------------------------------------------------------
// micros()返回启动以来的微秒数
//------------------------------------------------------------------
uint32_t micros() 
{
    return  to_us_since_boot(get_absolute_time ());
}

void dma_spi_write(spi_inst_t* spi, uint8_t * data, uint8_t length)
{
    if (dma_channel_is_busy(dma_spi0_tx)) return; 
    dma_channel_configure(dma_spi0_tx, &dma_spi0_cfg, &spi_get_hw(spi)->dr, data, length, true);
    dma_channel_wait_for_finish_blocking(dma_spi0_tx);
}

uint8_t u8x8_byte_pico_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) 
{
    uint8_t *data;
    switch (msg) {
        case U8X8_MSG_BYTE_SEND:
            data = (uint8_t *)arg_ptr;
            //spi_write_blocking(SPI_PORT0, data, arg_int);
            dma_spi_write(SPI_PORT0, data, arg_int);
            break;

        case U8X8_MSG_BYTE_INIT:
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
            break;

        case U8X8_MSG_BYTE_SET_DC:
            u8x8_gpio_SetDC(u8x8, arg_int);
            break;

        case U8X8_MSG_BYTE_START_TRANSFER:
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);
            u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->post_chip_enable_wait_ns, NULL);
            break;

        case U8X8_MSG_BYTE_END_TRANSFER:
            u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->pre_chip_disable_wait_ns, NULL);
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
            break;

        default:
            return 0;
    }
    return 1;
}

uint8_t u8x8_gpio_and_delay_template(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) 
{
    switch (msg) {
        case U8X8_MSG_GPIO_AND_DELAY_INIT: 
            spi_init(SPI_PORT0, SPI0_SPEED);
            gpio_set_function(PIN_OLED_MISO, GPIO_FUNC_SPI);
            gpio_set_function(PIN_OLED_CS, GPIO_FUNC_SIO);
            gpio_set_function(PIN_OLED_SCK, GPIO_FUNC_SPI);
            gpio_set_function(PIN_OLED_MOSI, GPIO_FUNC_SPI);
 
            gpio_init(PIN_OLED_DC);
            gpio_set_dir(PIN_OLED_DC, GPIO_OUT);
            gpio_put(PIN_OLED_DC,  false);

            gpio_init(PIN_OLED_CS);
            gpio_set_dir(PIN_OLED_CS, GPIO_OUT);
            gpio_put(PIN_OLED_CS, true);

            gpio_init(PIN_OLED_RES);
            gpio_set_dir(PIN_OLED_RES, GPIO_IN);
            gpio_set_pulls(PIN_OLED_RES, true, false);
            gpio_put(PIN_OLED_RES, false);

            dma_spi0_tx = dma_claim_unused_channel(true);
            dma_spi0_cfg = dma_channel_get_default_config(dma_spi0_tx);
            channel_config_set_dreq(&dma_spi0_cfg, spi_get_dreq(SPI_PORT0, true));
            channel_config_set_read_increment(&dma_spi0_cfg, true); 
            channel_config_set_write_increment(&dma_spi0_cfg, false);
            channel_config_set_dreq(&dma_spi0_cfg, DREQ_SPI0_TX);
            channel_config_set_transfer_data_size(&dma_spi0_cfg, DMA_SIZE_8);

            break;

        case U8X8_MSG_DELAY_NANO:
            sleep_us(1 * arg_int);
            break;
        case U8X8_MSG_DELAY_100NANO:
            sleep_us(100 * arg_int);
            break;
        case U8X8_MSG_DELAY_10MICRO:
            sleep_us(arg_int * 10);
            break;
        case U8X8_MSG_DELAY_MILLI:
            sleep_ms(arg_int);
            break;
        case U8X8_MSG_DELAY_I2C:
            break;
        case U8X8_MSG_GPIO_D0:
            break;
        case U8X8_MSG_GPIO_D1:
            break;
        case U8X8_MSG_GPIO_D2:
            break;
        case U8X8_MSG_GPIO_D3:
            break;
        case U8X8_MSG_GPIO_D4:
            break;
        case U8X8_MSG_GPIO_D5:
            break;
        case U8X8_MSG_GPIO_D6:
            break;
        case U8X8_MSG_GPIO_D7:
            break;
        case U8X8_MSG_GPIO_E:
            break;
        case U8X8_MSG_GPIO_CS:
            gpio_put(PIN_OLED_CS, arg_int);
            break;
        case U8X8_MSG_GPIO_DC:
            gpio_put(PIN_OLED_DC, arg_int);
            break;
        case U8X8_MSG_GPIO_RESET:
            break;
        case U8X8_MSG_GPIO_CS1:
            break;
        case U8X8_MSG_GPIO_CS2:
            break;
        case U8X8_MSG_GPIO_I2C_CLOCK:
            break;
        case U8X8_MSG_GPIO_I2C_DATA:
            break;
        case U8X8_MSG_GPIO_MENU_SELECT:
            u8x8_SetGPIOResult(u8x8, 0);
            break;
        case U8X8_MSG_GPIO_MENU_NEXT:
            u8x8_SetGPIOResult(u8x8, 0);
            break;
        case U8X8_MSG_GPIO_MENU_PREV:
            u8x8_SetGPIOResult(u8x8, 0);
            break;
        case U8X8_MSG_GPIO_MENU_HOME:
            u8x8_SetGPIOResult(u8x8, 0);
            break;
        default:
            u8x8_SetGPIOResult(u8x8, 1);
            break;
    }
    return 1;
}


//------------------------------------------------------------------
//烟花处理函数
//------------------------------------------------------------------
void fireworks_show()
{
    
    for (int i = 0; i < sprite_count; i++) 
    {
        sprite_img[i]++; 
        if (sprite_img[i] > 8) 
        {
            sprite_x[i] = rand()%120;
            sprite_y[i] = random()%56;
            sprite_img[i] = 0;
        }  
    }

    for (int i = 0; i < sprite_count; i++) {
        u8g2_DrawXBM(&u8g2, sprite_x[i], sprite_y[i], 8, 8, epd_bitmap_allArray[sprite_img[i]]);
    }
    
    u8g2_DrawStr(&u8g2, 128/2 - u8g2_GetStrWidth(&u8g2,"Congratulations!")/2, 32, "Congratulations!");
}

//--------------------------------------------------------------------+
// setup_OLED
//--------------------------------------------------------------------+
void setup_OLED()
{
    u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_pico_hw_spi, u8x8_gpio_and_delay_template);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);
    u8g2_SetContrast(&u8g2, 200);
    u8g2_SetFont(&u8g2, u8g2_font_6x13_tr);
}

//--------------------------------------------------------------------+
// OLED TASK
//--------------------------------------------------------------------+
// void OLED_Task(void *params)
void OLED_Task()
{
    setup_OLED();
    for(;;)
    {
        u8g2_ClearBuffer(&u8g2);
        fireworks_show();
        u8g2_SendBuffer(&u8g2);
        // vTaskDelay(pdMS_TO_TICKS(50));
    }
}
/*************************************************************/
//                      FREERTOS入口
/*************************************************************/
// void FreeRTOSprvEntry() {
//     xTaskCreate(OLED_Task, "OLED TASK", 8 * 1024, NULL, OLED_TASK_PRIORITY, &OLEDTask_Handler);
//     vTaskStartScheduler();
// }
/*###########################################################*/
//                      主程序入口
/*###########################################################*/
int main(void)
{
    stdio_init_all();
    // FreeRTOSprvEntry();
    OLED_Task();
    return 0;
}
/*###########################################################*/
//                      主程序结尾
/*###########################################################*/

