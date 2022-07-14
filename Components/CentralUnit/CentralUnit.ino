#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

RH_ASK driver;

const int alarmPin = 4
;
const int alarmDuration = 2; // seconds

Serial.begin(9600);

pinMode(alarmPin, OUTPUT);

// Alarm beeps for initialization
digitalWrite(alarmPin, HIGH);
delay(30);
digitalWrite(alarmPin, LOW);
delay(100);
digitalWrite(alarmPin, HIGH);
delay(30);
digitalWrite(alarmPin, LOW);
delay(100);
digitalWrite(alarmPin, HIGH);
delay(30);
digitalWrite(alarmPin, LOW);
delay(100);

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen))
    {
  int i;

  uint8_t alarmCode = 72;

  if (buf == alarmCode){
    Serial.println("Alarm");
  }
  

  // Message with a good checksum received, dump it.
  driver.printBuffer("Got:", buf, buflen);
  digitalWrite(alarmPin, HIGH);
  
  delay(alarmDuration * 1000);
  digitalWrite(alarmPin, LOW);
    }
    else {
      Serial.println("No packet alert");
      // digitalWrite(alarmPin, LOW);
    }
}
