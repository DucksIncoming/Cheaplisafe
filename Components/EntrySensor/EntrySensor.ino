#include <RadioHead.h>
#include <RH_ASK.h>
#include <SPI.h>

const int trig = 6;
const int echo = 4;
const int LED = 8;
const int transmit = 12;
RH_ASK rf_driver;

long duration;
int distance;

void setup() {
  rf_driver.init();
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration*0.034 / 2;
  char msg = "1";

  if (distance > 5) {
    digitalWrite(LED, HIGH);
    msg = "1";
  }
  else {
    digitalWrite(LED, LOW);
    msg = "0";
  }
  Serial.print(distance);
  Serial.println('\n');

  const char *newMsg = msg;

  rf_driver.send((uint8_t *)newMsg, strlen(newMsg));
  rf_driver.waitPacketSent();
}
