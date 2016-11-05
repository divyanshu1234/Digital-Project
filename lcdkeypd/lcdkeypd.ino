#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(10,9,4,5,6,8);

char hexakeys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
  };

byte rowPins[4] = {30,32,34,36};
byte colPins[4] = {38,40,42,44};

Keypad customKeypad = Keypad(makeKeymap(hexakeys),rowPins,colPins,4,4);


void setup() {
  lcd.begin(16,2);
  Serial.begin(9600); 
}

void loop() {

  char c = customKeypad.getKey();

  if(c!=NO_KEY){
    if(c=='A')
      lcd.clear();
    else
      lcd.print(c);
  }

}
