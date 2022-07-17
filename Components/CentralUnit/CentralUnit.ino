#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h>
#endif

RH_ASK driver;
const int alarmPin = 4;
const int alarmDuration = 2; // seconds
const bool alarmStart = false;

const int buttonPin = 2;
const String buttonFunction = "toggle"; // What command the button will send, currently only used for the SmartLock ("toggle" || "lock" || "unlock")
const int buttonOnState = 0; // Some buttons are normally closed, some normally open. Set to yours.

const String keypadCode = "1234A";


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

    // Alarm handling
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
        digitalWrite(alarmPin, HIGH);
        delay(30);
        digitalWrite(alarmPin, LOW);
        delay(100);
      }
    }
  }
  // Multifunction button
  int buttonState = digitalRead(buttonPin);
  Serial.print("Button State: ");
  Serial.println(buttonState);

  if (buttonState == buttonOnState){
    const char *msg = buttonFunction.c_str();
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.println("Button command triggered");
    delay(50);
  }
}
