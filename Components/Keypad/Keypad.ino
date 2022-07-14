#include <Keypad.h>
#include <RadioHead.h>
#include <RH_ASK.h>
#include <SPI.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
String currentCode = "";

//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
RH_ASK driver;

void setup(){
  driver.init();
  
  Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
    if (customKey == '#'){
      const char *charCode = currentCode.c_str();
      driver.send((uint8_t *)charCode, strlen(charCode));
      driver.waitPacketSent();
      Serial.print("Sent Code: ");
      Serial.println(charCode);
      
      currentCode = "";
    }
    else {
      currentCode += customKey;
    }
  }

  delay(10);
}
