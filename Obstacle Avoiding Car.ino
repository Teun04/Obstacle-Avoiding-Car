#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define Lpwm_pin  5    
#define Rpwm_pin  6   
int pinLB=2;            
int pinLF=4;           
int pinRB=7;        
int pinRF=8;           

Servo myservo;
volatile int DL;
volatile int DM;
volatile int DR;

float checkdistance() {
  digitalWrite(A1, LOW);
  delayMicroseconds(2);
  digitalWrite(A1, HIGH);
  delayMicroseconds(10);
  digitalWrite(A1, LOW);
  float distance = pulseIn(A0, HIGH) / 58.00;
  delay(10);
  return distance;
}


void Detect_obstacle_distance() {
  myservo.write(160);
  for (int i = 0; i < 3; i = i + 1) {
    DL = checkdistance();
    delay(100);
  }
  myservo.write(20);
  for (int i = 0; i<3; i = i + 1) {
    DR = checkdistance();
    delay(100);
  }
}

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
{
  lcd.begin();

  lcd.backlight();
  lcd.print(" Ready to go :)");
}
   
   myservo.attach(A2);
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
 pinMode(pinLB,OUTPUT); 
  pinMode(pinLF,OUTPUT); 
  pinMode(pinRB,OUTPUT); 
  pinMode(pinRF,OUTPUT);  
  pinMode(Lpwm_pin,OUTPUT);  
  pinMode(Rpwm_pin,OUTPUT);  
  DL = 0;
  DM = 0;
  DR = 0;
  myservo.write(90);
}

void loop(){
  DM = checkdistance();
  if (DM < 44) {
    stopp();
    Set_Speed(-10);
    delay(1000);
    Detect_obstacle_distance();
    if (DL < 25 || DR < 25) {
      if (DL > DR) {
        myservo.write(90);
        turnL();
        Set_Speed(300);
        delay(200);
        advance();
        Set_Speed(300);

      } else {
        myservo.write(90);
        turnR();
        Set_Speed(200);
        delay(200);
        advance();
        Set_Speed(200);

      }

    } else {
      if (random(1, 10) > 5) {
        myservo.write(90);
        turnL();
        Set_Speed(200);
        delay(200);
        advance();
        Set_Speed(200);

      } else {
        myservo.write(90);
        turnR();
        Set_Speed(200);
        delay(200);
        advance();
        Set_Speed(200);

      }

    }

  } else {
    advance();
    Set_Speed(150);

  }

}


void Set_Speed(unsigned char pwm) 
{
  analogWrite(Lpwm_pin,pwm);
  analogWrite(Rpwm_pin,pwm);
}
void advance()    
    {
     digitalWrite(pinRB,LOW);  
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,LOW);  
     digitalWrite(pinLF,HIGH); 
   
    }
void turnR()       
    {
     digitalWrite(pinRB,LOW);  
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,LOW);  
  
    }
void turnL()      
    {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,LOW );   
     digitalWrite(pinLB,LOW);  
     digitalWrite(pinLF,HIGH);
    
    }    
void stopp()  
    {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,HIGH);
    
    }
void back()
    {
     digitalWrite(pinRB,HIGH);  
     digitalWrite(pinRF,LOW);
     digitalWrite(pinLB,HIGH);  
     digitalWrite(pinLF,LOW);
      
    }
