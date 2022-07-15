#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h>
#endif

RH_ASK driver;
const int alarmPin = 4;
const int alarmDuration = 2; // seconds
const String keypadCode = "1234A";
const bool alarmStart = true;

void setup()
{
  pinMode(alarmPin, OUTPUT);
  
  #ifdef RH_HAVE_SERIAL
    Serial.begin(9600);
  #endif
    if (!driver.init())
  #ifdef RH_HAVE_SERIAL
    Serial.println("init failed");
  #else
    ;
  #endif

  for(int i = 0; i < 3; i++) {
    digitalWrite(alarmPin, HIGH);
    delay(30);
    digitalWrite(alarmPin, LOW);
    delay(100);
  }

  if (alarmStart) {
    digitalWrite(alarmPin, HIGH);
  }
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)){
    int i;
  
    //driver.printBuffer("Got:", buf, buflen);
  
    String data = ((String)(char*)buf);
    data.trim();
    data = data.substring(0, buflen);

    Serial.println(data);
    
    if (data == "on_p"){
      Serial.println("= ALARM ENABLED = ");
      digitalWrite(alarmPin, HIGH);
    }
    else if (data == "on_t"){
      Serial.println("= ALARM ENABLED = ");
      
      digitalWrite(alarmPin, HIGH);
      delay(alarmDuration * 1000);
      digitalWrite(alarmPin, LOW);

      Serial.println("= ALARM DISABLED = ");
    }
    else if (data == keypadCode){
      Serial.println("= ALARM DISABLED = ");
      
      for(int i = 0; i < 3; i++) {
        digitalWrite(alarmPin, HIGH);;+
        delay(30);
        digitalWrite(alarmPin, LOW);
        delay(100);
      }
    }
  }
}
