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
boolean clear = true;
int pos = 0;
boolean doorUnlocked = false;

const int trigPin = 13;
const int echoPin = 12;
const int buzzerPin = 3;

void setup() {  
  pinMode(buzzerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  myservo.attach(11);
  lcd.begin(16,2);
  Serial.begin(9600); 
}

void clear_screen(){
if(clear){
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
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
  

  if(distance > 20){
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
    
  if(Serial.available()){
    delay(100);
    char blueInput = (char)Serial.read();
    Serial.println(blueInput);

    switch(blueInput){
      case '0': unlockDoor();
                break;
      case '1': lockDoor();
                break;
    }

  }

}

void unlockDoor(){  
  doorUnlocked = true;
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);              
    delay(15); 
  }
}



void lockDoor(){    
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);              
    delay(15);
  } 

  doorUnlocked = false;
}
