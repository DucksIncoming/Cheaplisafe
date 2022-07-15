#include <RadioHead.h>
#include <RH_ASK.h>
#include <SPI.h>


const int soundPin = A4; //Analog
const int sampleDuration = 50; //milliseconds
const int threshold = 90; // in dB, arbitrary

const String mode = "T"; // Set alarm activation mode ("T" || "P")

RH_ASK driver;

void setup() {
  pinMode(soundPin, INPUT);
  driver.init();
  Serial.begin(9600);
}

void loop() {
  unsigned long startMillis = millis();
  float peak2peak = 0;

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while(millis() - startMillis < sampleDuration){
    int audioVoltage = analogRead(soundPin);
    if (audioVoltage < 1024){
      if (audioVoltage > signalMax){
        signalMax = audioVoltage;
      }
      else if (audioVoltage < signalMin){
        signalMin = audioVoltage;
      }
    }
  }

  peak2peak = signalMax - signalMin;
  int dB = map(peak2peak, 20, 900, 49.5, 90);

  Serial.print("dB: ");
  Serial.println(dB);

  if (dB >= 90){
    String msg = "on_t";
    
    if (mode == "P"){
      msg = "on_p";
    }

    const char *sendMsg = msg.c_str();
    Serial.print("MSG: ");
    Serial.println(msg);

    driver.send((uint8_t *)sendMsg, strlen(sendMsg));
    driver.waitPacketSent();
    Serial.println("Sent command to alarm.");
  }
}
