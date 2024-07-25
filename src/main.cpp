// // #include <Arduino.h>
// // #include <TFT_eSPI.h>
// // #include <SPI.h>

// // TFT_eSPI tft = TFT_eSPI();

// // void setup() {
// //   Serial.begin(115200);
// //   Serial.println("Setup started");

// //   // 手动控制RST引脚
// //   pinMode(TFT_RST, OUTPUT);
// //   digitalWrite(TFT_RST, HIGH);
// //   delay(10);
// //   digitalWrite(TFT_RST, LOW);
// //   delay(10);
// //   digitalWrite(TFT_RST, HIGH);
// //   delay(10);

// //   tft.init();
// //   Serial.println("TFT initialized");

// //   tft.setRotation(0);  // 尝试不同的旋转值(0-3)
// //   Serial.println("Screen rotation set");

// //   // 基本显示测试
// //   tft.fillScreen(TFT_RED);
// //   Serial.println("Screen filled with red");
// //   delay(1000);

// //   tft.fillScreen(TFT_GREEN);
// //   Serial.println("Screen filled with green");
// //   delay(1000);

// //   tft.fillScreen(TFT_BLUE);
// //   Serial.println("Screen filled with blue");
// //   delay(1000);

// //   // 显示文本
// //   tft.fillScreen(TFT_BLACK);
// //   tft.setTextColor(TFT_WHITE);
// //   tft.setTextSize(2);
// //   tft.setCursor(10, 30);
// //   tft.println("Hello,");
// //   tft.setCursor(10, 50);
// //   tft.println("RP2040!");
// //   Serial.println("Text displayed");

// //   // 绘制一些图形
// //   tft.drawRect(0, 0, 128, 128, TFT_YELLOW);
// //   tft.fillCircle(64, 64, 30, TFT_MAGENTA);
// //   Serial.println("Shapes drawn");
// // }

// // void loop() {
// //   // 在循环中添加一些动画效果
// //   static uint16_t color = 0;
// //   tft.drawFastHLine(0, random(128), 128, color);
// //   color += 1;
// //   delay(10);
// // }

// #include <Arduino.h>
// #include <TFT_eSPI.h>
// #include <SPI.h>

// TFT_eSPI tft = TFT_eSPI();

// void customInit() {
//   tft.writecommand(ST7735_SLPOUT);  // 退出睡眠模式
//   delay(120); 
  
//   tft.writecommand(ST7735_FRMCTR1);  // 帧率控制
//   tft.writedata(0x01);
//   tft.writedata(0x2C);
//   tft.writedata(0x2D);
  
//   tft.writecommand(ST7735_FRMCTR2);
//   tft.writedata(0x01);
//   tft.writedata(0x2C);
//   tft.writedata(0x2D);
  
//   tft.writecommand(ST7735_FRMCTR3);
//   tft.writedata(0x01);
//   tft.writedata(0x2C);
//   tft.writedata(0x2D);
//   tft.writedata(0x01);
//   tft.writedata(0x2C);
//   tft.writedata(0x2D);
  
//   tft.writecommand(ST7735_INVCTR);  // 显示反转控制
//   tft.writedata(0x07);
  
//   tft.writecommand(ST7735_PWCTR1);  // 电源控制
//   tft.writedata(0xA2);
//   tft.writedata(0x02);
//   tft.writedata(0x84);
  
//   tft.writecommand(ST7735_PWCTR2);
//   tft.writedata(0xC5);
  
//   tft.writecommand(ST7735_PWCTR3);
//   tft.writedata(0x0A);
//   tft.writedata(0x00);
  
//   tft.writecommand(ST7735_PWCTR4);
//   tft.writedata(0x8A);
//   tft.writedata(0x2A);
  
//   tft.writecommand(ST7735_PWCTR5);
//   tft.writedata(0x8A);
//   tft.writedata(0xEE);
  
//   tft.writecommand(ST7735_VMCTR1);  // VCOM 控制
//   tft.writedata(0x0E);
  
//   tft.writecommand(ST7735_INVOFF);  // 不反转显示
  
//   tft.writecommand(ST7735_MADCTL);  // 内存访问控制
//   tft.writedata(0xC8);
  
//   tft.writecommand(ST7735_COLMOD);  // 接口像素格式
//   tft.writedata(0x05);
  
//   tft.writecommand(ST7735_CASET);  // 列地址设置
//   tft.writedata(0x00);
//   tft.writedata(0x00);
//   tft.writedata(0x00);
//   tft.writedata(0x7F);
  
//   tft.writecommand(ST7735_RASET);  // 行地址设置
//   tft.writedata(0x00);
//   tft.writedata(0x00);
//   tft.writedata(0x00);
//   tft.writedata(0x7F);
  
//   tft.writecommand(ST7735_GMCTRP1);
//   tft.writedata(0x02);
//   tft.writedata(0x1C);
//   tft.writedata(0x07);
//   tft.writedata(0x12);
//   tft.writedata(0x37);
//   tft.writedata(0x32);
//   tft.writedata(0x29);
//   tft.writedata(0x2D);
//   tft.writedata(0x29);
//   tft.writedata(0x25);
//   tft.writedata(0x2B);
//   tft.writedata(0x39);
//   tft.writedata(0x00);
//   tft.writedata(0x01);
//   tft.writedata(0x03);
//   tft.writedata(0x10);
  
//   tft.writecommand(ST7735_GMCTRN1);
//   tft.writedata(0x03);
//   tft.writedata(0x1D);
//   tft.writedata(0x07);
//   tft.writedata(0x06);
//   tft.writedata(0x2E);
//   tft.writedata(0x2C);
//   tft.writedata(0x29);
//   tft.writedata(0x2D);
//   tft.writedata(0x2E);
//   tft.writedata(0x2E);
//   tft.writedata(0x37);
//   tft.writedata(0x3F);
//   tft.writedata(0x00);
//   tft.writedata(0x00);
//   tft.writedata(0x02);
//   tft.writedata(0x10);
  
//   tft.writecommand(ST7735_NORON);  // 正常显示模式开启
//   delay(10);
  
//   tft.writecommand(ST7735_DISPON);  // 显示开启
//   delay(100);
// }

// void setup() {
//   Serial.begin(115200);
  
//   tft.init();
//   customInit();  // 调用自定义初始化函数
  
//   // 尝试不同的旋转设置 (0-3)
//   tft.setRotation(2);
  
//   // 如果需要，设置自定义视口
//   // tft.setViewport(2, 3, 128, 128);
  
//   tft.fillScreen(TFT_BLACK);

//   tft.setTextColor(TFT_WHITE, TFT_BLACK);
//   tft.setTextSize(1);
//   tft.setCursor(0, 0);
//   tft.println("TFT 128x128 Test");
  
//   delay(1000);
// }

// void loop() {
//   // 绘制一些图形来测试显示
//   tft.fillScreen(TFT_BLACK);
  
//   // 绘制一些彩色矩形
//   for(int i = 0; i < 5; i++) {
//     tft.fillRect(random(tft.width()), random(tft.height()), 
//                  20, 20, random(0xFFFF));
//   }
  
//   delay(2000);
  
//   // 绘制一些文本
//   tft.setTextColor(TFT_WHITE, TFT_BLACK);
//   tft.setTextSize(1);
//   tft.setCursor(10, 50);
//   tft.println("RP2040 + ST7735");
//   tft.setCursor(10, 70);
//   tft.println("128x128 Display");
  
//   // 绘制一个圆形
//   tft.drawCircle(64, 64, 30, TFT_YELLOW);
  
//   delay(2000);
// }


// #include <Arduino.h>
// #include <TFT_eSPI.h>
// #include <SPI.h>

// TFT_eSPI tft = TFT_eSPI();
// TFT_eSprite sprite = TFT_eSprite(&tft);

// uint32_t frameCount = 0;
// uint32_t startTime = 0;
// uint32_t lastFpsTime = 0;
// float fps = 0;

// void setup() {
//   Serial.begin(115200);
//   while (!Serial) { delay(10); }
//   Serial.println("\n\nTFT Speed Test with Double Buffering");

//   tft.init();
//   tft.setRotation(1);  // 设置为横向
//   tft.fillScreen(TFT_BLACK);

//   // 创建一个与屏幕大小相同的sprite
//   sprite.createSprite(tft.width(), tft.height());

//   startTime = millis();
//   lastFpsTime = startTime;
// }

// void loop() {
//   uint32_t currentTime = millis();
//   frameCount++;

//   // 每秒计算一次FPS
//   if (currentTime - lastFpsTime >= 1000) {
//     fps = frameCount * 1000.0 / (currentTime - lastFpsTime);
//     lastFpsTime = currentTime;
//     frameCount = 0;

//     Serial.print("FPS: ");
//     Serial.println(fps);
//   }

//   // 在sprite上绘制，而不是直接在屏幕上
//   sprite.fillSprite(TFT_BLACK);

//   // 测试1：绘制多个随机矩形
//   for (int i = 0; i < 10; i++) {
//     int x = random(sprite.width());
//     int y = random(sprite.height());
//     int w = random(50) + 10;
//     int h = random(50) + 10;
//     sprite.fillRect(x, y, w, h, random(0xFFFF));
//   }

//   // 测试2：绘制多个随机圆
//   for (int i = 0; i < 10; i++) {
//     int x = random(sprite.width());
//     int y = random(sprite.height());
//     int r = random(20) + 5;
//     sprite.fillCircle(x, y, r, random(0xFFFF));
//   }

//   // 测试3：绘制多条随机线
//   for (int i = 0; i < 20; i++) {
//     int x1 = random(sprite.width());
//     int y1 = random(sprite.height());
//     int x2 = random(sprite.width());
//     int y2 = random(sprite.height());
//     sprite.drawLine(x1, y1, x2, y2, random(0xFFFF));
//   }

//   // 显示FPS
//   sprite.setTextColor(TFT_WHITE, TFT_BLACK);
//   sprite.setTextSize(2);
//   sprite.setCursor(5, 5);
//   sprite.print("FPS: ");
//   sprite.print(fps, 1);

//   // 将sprite推送到屏幕上
//   sprite.pushSprite(0, 0);

//   // 每30秒输出一次平均FPS
//   if (currentTime - startTime >= 30000) {
//     float avgFps = frameCount * 1000.0 / (currentTime - startTime);
//     Serial.print("Average FPS over 30 seconds: ");
//     Serial.println(avgFps);
//     startTime = currentTime;
//     frameCount = 0;
//   }
// }


#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

uint32_t frameCount = 0;
uint32_t startTime = 0;
uint32_t lastFpsTime = 0;
float fps = 0;

// 预分配颜色数组以避免重复调用random()
uint16_t colors[40];

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }
  Serial.println("\n\nOptimized TFT Speed Test with Double Buffering");

  tft.init();
  tft.setRotation(1);  // 设置为横向
  tft.fillScreen(TFT_BLACK);

  // 创建一个与屏幕大小相同的sprite
  sprite.createSprite(tft.width(), tft.height());

  // 预生成随机颜色
  for (int i = 0; i < 40; i++) {
    colors[i] = random(0xFFFF);
  }

  startTime = millis();
  lastFpsTime = startTime;
}

void loop() {
  uint32_t currentTime = millis();
  frameCount++;

  // 每秒计算一次FPS
  if (currentTime - lastFpsTime >= 1000) {
    fps = frameCount * 1000.0 / (currentTime - lastFpsTime);
    lastFpsTime = currentTime;
    frameCount = 0;

    Serial.print("FPS: ");
    Serial.println(fps);
  }

  // 使用DMA快速填充背景
  sprite.fillSprite(TFT_BLACK);

  // 测试1：绘制多个随机矩形
  for (int i = 0; i < 10; i++) {
    sprite.fillRect(random(sprite.width()), random(sprite.height()), 
                    random(50) + 10, random(50) + 10, colors[i]);
  }

  // 测试2：绘制多个随机圆
  for (int i = 10; i < 20; i++) {
    sprite.fillCircle(random(sprite.width()), random(sprite.height()), 
                      random(20) + 5, colors[i]);
  }

  // 测试3：绘制多条随机线
  for (int i = 20; i < 40; i++) {
    sprite.drawLine(random(sprite.width()), random(sprite.height()),
                    random(sprite.width()), random(sprite.height()), colors[i]);
  }

  // 显示FPS
  sprite.setTextColor(TFT_WHITE, TFT_BLACK);
  sprite.setTextSize(2);
  sprite.setCursor(5, 5);
  sprite.print("FPS: ");
  sprite.print(fps, 1);

  // 使用DMA将sprite推送到屏幕上
  tft.startWrite();
  sprite.pushSprite(0, 0);
  tft.endWrite();

  // 每30秒输出一次平均FPS
  if (currentTime - startTime >= 30000) {
    float avgFps = frameCount * 1000.0 / (currentTime - startTime);
    Serial.print("Average FPS over 30 seconds: ");
    Serial.println(avgFps);
    startTime = currentTime;
    frameCount = 0;
  }
}