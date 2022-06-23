#include <RadioHead.h>
#include <RH_ASK.h>
#include <SPI.h>

const int alarm = 2;
const int reciever = 11;
RH_ASK rf_driver;

long duration;
int distance;

void setup() {
  rf_driver.init();
  
  pinMode(alarm, OUTPUT);
  pinMode(reciever, INPUT);
  Serial.begin(9600);
}

void loop() {
  uint8_t buf[2];
  uint8_t buflen  = sizeof(buf);

  if (rf_driver.recv(buf, &buflen)){
    Serial.print("Message: ");
    Serial.println((char*)buf);
  }
  
}
