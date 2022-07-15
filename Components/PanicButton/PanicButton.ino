#include <RadioHead.h>
#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;
const int button = 2;

void setup() {
  rf_driver.init();
  Serial.begin(9600);
  pinMode(button, INPUT);
}

void loop() {
  const char *msg = "open_t";
  int buttonState = digitalRead(button);
  // Serial.println(buttonState);

  if (buttonState == 1) {
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    Serial.println("Packet Sent");
  }
  else {
    Serial.println("...");
  }
  delay(10);
}
