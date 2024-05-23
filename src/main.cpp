#include <Arduino.h>
#include "protocol.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // 配置LED引脚
  protocolSetup();  // 初始化串口
}

void loop() {
  handleSerialData();  // 处理接收到的数据
  delay(100);  // 延时以减轻CPU负担
}
