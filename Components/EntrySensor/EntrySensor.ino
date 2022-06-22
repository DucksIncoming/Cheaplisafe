#include <RH_ASK.h>
#include <SPI.h>

const int trig = 6;
const int echo = 4;
const int LED = 8;
char *msg = "0";

long duration;
int distance;
int incoming;

RH_ASK rf_driver;

void setup() {
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

  if (distance > 5) {
    digitalWrite(LED, HIGH);
    msg = "1";
  }
  else {
    digitalWrite(LED, LOW);
    msg = "0";
  }

  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();
  delay(500);

  Serial.print(distance);
  Serial.println('\n');
}
