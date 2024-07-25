#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

void customInit() {
  tft.writecommand(ST7735_SLPOUT);  // 退出睡眠模式
  delay(120); 
  
  tft.writecommand(ST7735_FRMCTR1);  // 帧率控制
  tft.writedata(0x01);
  tft.writedata(0x2C);
  tft.writedata(0x2D);
  
  tft.writecommand(ST7735_FRMCTR2);
  tft.writedata(0x01);
  tft.writedata(0x2C);
  tft.writedata(0x2D);
  
  tft.writecommand(ST7735_FRMCTR3);
  tft.writedata(0x01);
  tft.writedata(0x2C);
  tft.writedata(0x2D);
  tft.writedata(0x01);
  tft.writedata(0x2C);
  tft.writedata(0x2D);
  
  tft.writecommand(ST7735_INVCTR);  // 显示反转控制
  tft.writedata(0x07);
  
  tft.writecommand(ST7735_PWCTR1);  // 电源控制
  tft.writedata(0xA2);
  tft.writedata(0x02);
  tft.writedata(0x84);
  
  tft.writecommand(ST7735_PWCTR2);
  tft.writedata(0xC5);
  
  tft.writecommand(ST7735_PWCTR3);
  tft.writedata(0x0A);
  tft.writedata(0x00);
  
  tft.writecommand(ST7735_PWCTR4);
  tft.writedata(0x8A);
  tft.writedata(0x2A);
  
  tft.writecommand(ST7735_PWCTR5);
  tft.writedata(0x8A);
  tft.writedata(0xEE);
  
  tft.writecommand(ST7735_VMCTR1);  // VCOM 控制
  tft.writedata(0x0E);
  
  tft.writecommand(ST7735_INVOFF);  // 不反转显示
  
  tft.writecommand(ST7735_MADCTL);  // 内存访问控制
  tft.writedata(0xC8);
  
  tft.writecommand(ST7735_COLMOD);  // 接口像素格式
  tft.writedata(0x05);
  
  tft.writecommand(ST7735_CASET);  // 列地址设置
  tft.writedata(0x00);
  tft.writedata(0x00);
  tft.writedata(0x00);
  tft.writedata(0x7F);
  
  tft.writecommand(ST7735_RASET);  // 行地址设置
  tft.writedata(0x00);
  tft.writedata(0x00);
  tft.writedata(0x00);
  tft.writedata(0x7F);
  
  tft.writecommand(ST7735_GMCTRP1);
  tft.writedata(0x02);
  tft.writedata(0x1C);
  tft.writedata(0x07);
  tft.writedata(0x12);
  tft.writedata(0x37);
  tft.writedata(0x32);
  tft.writedata(0x29);
  tft.writedata(0x2D);
  tft.writedata(0x29);
  tft.writedata(0x25);
  tft.writedata(0x2B);
  tft.writedata(0x39);
  tft.writedata(0x00);
  tft.writedata(0x01);
  tft.writedata(0x03);
  tft.writedata(0x10);
  
  tft.writecommand(ST7735_GMCTRN1);
  tft.writedata(0x03);
  tft.writedata(0x1D);
  tft.writedata(0x07);
  tft.writedata(0x06);
  tft.writedata(0x2E);
  tft.writedata(0x2C);
  tft.writedata(0x29);
  tft.writedata(0x2D);
  tft.writedata(0x2E);
  tft.writedata(0x2E);
  tft.writedata(0x37);
  tft.writedata(0x3F);
  tft.writedata(0x00);
  tft.writedata(0x00);
  tft.writedata(0x02);
  tft.writedata(0x10);
  
  tft.writecommand(ST7735_NORON);  // 正常显示模式开启
  delay(10);
  
  tft.writecommand(ST7735_DISPON);  // 显示开启
  delay(100);
}

void setup() {
  Serial.begin(115200);
  
  tft.init();
  customInit();  // 调用自定义初始化函数
  
  // 尝试不同的旋转设置 (0-3)
  tft.setRotation(2);
  
  // 如果需要，设置自定义视口
  // tft.setViewport(2, 3, 128, 128);
  
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("TFT 128x128 Test");
  
  delay(1000);
}

void loop() {
  // 绘制一些图形来测试显示
  tft.fillScreen(TFT_BLACK);
  
  // 绘制一些彩色矩形
  for(int i = 0; i < 5; i++) {
    tft.fillRect(random(tft.width()), random(tft.height()), 
                 20, 20, random(0xFFFF));
  }
  
  delay(2000);
  
  // 绘制一些文本
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(1);
  tft.setCursor(10, 50);
  tft.println("RP2040 + ST7735");
  tft.setCursor(10, 70);
  tft.println("128x128 Display");
  
  // 绘制一个圆形
  tft.drawCircle(64, 64, 30, TFT_YELLOW);
  
  delay(2000);
}