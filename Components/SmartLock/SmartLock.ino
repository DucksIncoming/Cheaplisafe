#include <ServoTimer2.h>
#include <RadioHead.h>
#include <RH_ASK.h>
#include <SPI.h>

const int servoPin = 8;
const int LEDpin = 9;
ServoTimer2 serv;
//int pos = 0;
bool state = false;
RH_ASK driver;

void setup() {
  serv.attach(servoPin);
  Serial.begin(9600);
  
  driver.init();
}

void loop() {
  if (state) {
    digitalWrite(LEDpin, HIGH);
    serv.write(90);
  }
  else {
    digitalWrite(LEDpin, LOW);
    serv.write(0);
  }

  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)){
    int i;

    String data = ((String)(char*)buf);
    data.trim();
    data = data.substring(0, buflen);

    Serial.println(data);

    if (data == "lock"){
      state = true;
    }
    else if (data == "unlock"){
      state = false;
    }
    else if (data="toggle"){
      state = !state;
    }

    delay(1000);
  }
}
