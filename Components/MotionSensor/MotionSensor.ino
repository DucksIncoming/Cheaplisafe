#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h>
#endif

const int sensorPin = 2;
const bool permAlarm = false; //Set to false for temporary alarm
RH_ASK driver;

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  driver.init();
}

void loop() {
  int motionData = digitalRead(sensorPin);
  Serial.println(motionData);

  if (motionData == 1){
    String msg = "on_t";
    
    if (permAlarm){
      msg = "on_p";
    }

    Serial.println("Motion detected!");
    Serial.println(msg.c_str());
    const char *sendMsg = msg.c_str();
    driver.send((uint8_t *)sendMsg, strlen(sendMsg));
    driver.waitPacketSent();

    delay(3500); // Motion sensor has a 3 second delay while it is on
  }
  
  delay(50);
}
