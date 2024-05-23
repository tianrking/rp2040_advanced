// protocol.c
#include "protocol.h"

void protocolSetup() {
  Serial.begin(115200);
  while (!Serial); // 等待串口准备好
  Serial.println("Ready to receive data...");
}

void handleSerialData() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(data);

    if (data == "hello") {
      Serial.println("Hello received!");
    } else if (data == "blink") {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("LED blinked!");
    } else {
      Serial.println("Command not recognized.");
    }
  }
}
