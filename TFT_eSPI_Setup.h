#define ST7735_DRIVER

#define TFT_WIDTH  128
#define TFT_HEIGHT 128

// 取消注释一个适合你屏幕的选项
#define ST7735_REDTAB
//#define ST7735_GREENTAB
//#define ST7735_GREENTAB2
//#define ST7735_GREENTAB3
//#define ST7735_BLACKTAB

#define TFT_MISO  4
#define TFT_MOSI  3
#define TFT_SCLK  2
#define TFT_CS    5  // Chip select control pin
#define TFT_DC    1  // Data Command control pin
#define TFT_RST   0  // Reset pin (could connect to Arduino RESET pin)

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT

#define SPI_FREQUENCY  27000000