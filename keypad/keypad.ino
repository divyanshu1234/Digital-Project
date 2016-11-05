#include <Keypad.h>
#include <LiquidCrystal.h>

/*
 *        _                       _              _
 *       /  \       _  __        | |            |_|
 *      / /\ \     | |/ _|    ___| |    _   _    _    ____       ___
 *     / /__\ \    |  /      / _   |   | | | |  | |  |  _  \   /  _  \
 *    / ______ \   | |      | |_|  |   | |_| |  | |  | | | |  |  |_|  |     PARTH.D
 *   /_/      \_\  |_|       \_____|   \_____|  |_|  |_| |_|   \ ___ /
 *    
 */   

LiquidCrystal lcd(8,9,10,11,12,13);

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
    lcd.setCursor(0,0);

    for(int i=0;i<16;++i)
      lcd.print(' ');

     lcd.setCursor(0,0);
    
    int i=0;
    Serial.println("int i=0");
    
    char c;
     
    do
     {
      c=customKeypad.getKey();
      
      if(c==NULL)
        continue;
      else if(c=='A')
        break;
        
      else
      {
        Serial.println(c);
        lcd.print(c);
        c=customKeypad.getKey();
        ++i;
      }  
     }while(c!='A');
}
