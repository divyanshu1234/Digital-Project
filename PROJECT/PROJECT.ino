#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <SoftwareSerial.h>

Servo myservo;
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


int screen = 0;
int keyCount = 0; 
String pin = "1111";
String key = "";
String newKey = "";
String newKey2 = "";
boolean doorUnlocked = false;
boolean clear = true;
int pos = 0;

const int trigPin = 13;
const int echoPin = 12;
const int buzzerPin = 52;

void setup() {  
  pinMode(buzzerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  myservo.attach(2);
  lcd.begin(16,2);
  myservo.write(180);
  Serial.begin(9600); 
}

void clear_screen(){
if(clear){
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,0);
    clear = false;
  }
}

void ultrasonic1(){  
  double duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration / 29.0 / 2.0;
  

  if(distance < 20){
    digitalWrite(buzzerPin, HIGH);
    }
  else{
        digitalWrite(buzzerPin, LOW);
    }
  }

void loop() {

if(!doorUnlocked)
{
  ultrasonic1();
}
 
switch(screen){
  case 0: screen0();
          break;
  case 1: screen1();
          break;
  case 2: screen2();
          break;
  case 3: screen3();
          break;
  case 4: screen4();
          break;
  case 5: screen5();
          break;
  case 6: screen6();
          break;
  case 7: screen7();
          break;
  case 8: screen8();
          break;
  }
}

void screen0(){
  //lcd.clear_screen();
  
  lcd.setCursor(0,0);
  lcd.print("WELCOME");
  lcd.setCursor(0,1);
  lcd.print("ENTER PIN");
  
  char c=customKeypad.getKey();

  if(c!= NO_KEY){
    key = key + c;
    keyCount=1;
    screen=1;
    //lcd.clear
    clear = true;
    }
  }

void screen1(){
  
  clear_screen();

  lcd.setCursor(0,0);
  
  for(int i=1;i<=keyCount;++i){
   lcd.print("*");
  }
  
  char c=customKeypad.getKey();
  if(c!=NO_KEY){
    key = key + c;
    ++keyCount;

    if(keyCount==4){
      //lcd.clear;
      clear = true;
      
      if(key != pin){
        lcd.setCursor(0,0);
        lcd.print("INCORRECT");
        lcd.setCursor(0,1);
        lcd.print("TRY AGAIN");
        delay(2000);

        screen = 0;
        key="";
        keyCount=0;
        }
      else{
        screen = 2;
        key="";
        keyCount=0;
        doorUnlocked = true;

        lcd.setCursor(0,0);
        lcd.print("UNLOCKED");
        Serial.print(1);
        delay(1000);
        for (pos = 180; pos >= 0; pos -= 1) {
          myservo.write(pos);              
          delay(15);
         }
        }
      }
    }
  }

void screen2(){
  //lcd.clear_screen();
  
  clear_screen();
   
  lcd.setCursor(0,0);
  lcd.print("C-Change Pin");
  lcd.setCursor(0,1);
  lcd.print("D-Lock");
  

  char c=customKeypad.getKey();

  if(c!=NO_KEY){
    if(c=='D'){
      //lcd.clear_screen();
      clear = true;
      
     
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");

      lcd.setCursor(0,0);
      lcd.print("LOCKED");
      delay(1000);

      for (pos = 0; pos <= 180; pos += 1) {
        myservo.write(pos);              
        delay(15);
      } 

      doorUnlocked = false;
      screen=0;
    }

    else if(c=='C')
    {
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");

      lcd.setCursor(0,0);
      lcd.print("CHANGE PIN");
      delay(2000);
      screen=3;
      clear = true;
    }
  }
}

void screen3(){
  clear_screen();

  lcd.setCursor(0,0);
  lcd.print("ENTER");
  lcd.setCursor(0,1);
  lcd.print("ORIGINAL PIN");
  
  char c=customKeypad.getKey();

  if(c!= NO_KEY){
    key = key + c;
    keyCount=1;
    screen=4;
    //lcd.clear
    clear = true;
    }
}

void screen4(){
  clear_screen();

  lcd.setCursor(0,0);
  
  for(int i=1;i<=keyCount;++i){
   lcd.print("*");
  }
  
  char c=customKeypad.getKey();
  if(c!=NO_KEY){
    key = key + c;
    ++keyCount;

    if(keyCount==4){
      //lcd.clear;
      clear = true;
      
      if(key != pin){
        lcd.setCursor(0,0);
        lcd.print("INCORRECT");
        delay(2000);

        screen = 2;
        key="";
        keyCount=0;
        }
      else{
        screen = 5;
        key="";
        keyCount=0;

      }
    }
  }
}

void screen5(){
  clear_screen();

  lcd.setCursor(0,0);
  lcd.print("ENTER");
  lcd.setCursor(0,1);
  lcd.print("NEW PIN");
  
  char c=customKeypad.getKey();

  if(c!= NO_KEY){
    newKey = newKey + c;
    keyCount=1;
    screen=6;
    //lcd.clear
    clear = true;
    }
}

void screen6(){
  clear_screen();

  lcd.setCursor(0,0);
  
  for(int i=1;i<=keyCount;++i){
   lcd.print("*");
  }
  
  char c=customKeypad.getKey();
  if(c!=NO_KEY){
    newKey = newKey + c;
    ++keyCount;

    if(keyCount==4){
      //lcd.clear;
      clear = true;
      keyCount = 0;

      screen = 7;
    }
  }
}

void screen7(){
  clear_screen();

  lcd.setCursor(0,0);
  lcd.print("ENTER NEW PIN");
  lcd.setCursor(0,1);
  lcd.print("AGAIN");
  
  char c=customKeypad.getKey();

  if(c!= NO_KEY){
    newKey2 = newKey2 + c;
    keyCount=1;
    screen=8;
    //lcd.clear
    clear = true;
    }
}

void screen8(){
  clear_screen();

  lcd.setCursor(0,0);
  
  for(int i=1;i<=keyCount;++i){
   lcd.print("*");
  }
  
  char c=customKeypad.getKey();
  if(c!=NO_KEY){
    newKey2 = newKey2 + c;
    ++keyCount;

    if(keyCount==4){
      //lcd.clear;
      clear = true;

      if(newKey2 != newKey){
        lcd.setCursor(0,0);
        lcd.print("PINS DO NOT");
        lcd.setCursor(0,1);
        lcd.print("MATCH");
        delay(2000);

        screen = 2;
        newKey="";
        newKey2="";
        keyCount=0;
        }
      else{
        screen = 2;
        keyCount=0;
        pin = newKey;

        newKey="";
        newKey2="";
        lcd.setCursor(0,0);
        lcd.print("PIN CHANGED");
        delay(2000);
      }
    }
  }
}
