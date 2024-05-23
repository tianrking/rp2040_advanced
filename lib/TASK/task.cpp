// // task.c
// #include "task.h"
// #include "protocol.h"

// void protocolTask(void *pvParameters) {
//   (void)pvParameters; // 未使用参数

//   protocolSetup(); // 设置串口

//   for (;;) {
//     if (Serial.available() > 0) {
//       String data = Serial.readStringUntil('\n');
//       parseData(data);
//     }
//     vTaskDelay(pdMS_TO_TICKS(100)); // 轻微延迟以防止占用太多CPU
//   }
// }

// void createTasks() {
//   xTaskCreate(protocolTask, "Protocol Task", 2048, NULL, 1, NULL);
// }
