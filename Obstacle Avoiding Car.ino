#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define Lpwm_pin  5     //pin of controlling speed---- ENA of motor driver board
#define Rpwm_pin  6    //pin of controlling speed---- ENB of motor driver board
int pinLB=2;             //pin of controlling turning---- IN1 of motor driver board
int pinLF=4;             //pin of controlling turning---- IN2 of motor driver board
int pinRB=7;            //pin of controlling turning---- IN3 of motor driver board
int pinRF=8;            //pin of controlling turning---- IN4 of motor driver board

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

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
{
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print(" Ready to go :)");
  lcd.print(" BABY ON BOARD ");
}
   
   myservo.attach(A2);
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
 pinMode(pinLB,OUTPUT); // /pin 2
  pinMode(pinLF,OUTPUT); // pin 4
  pinMode(pinRB,OUTPUT); // pin 7
  pinMode(pinRF,OUTPUT);  // pin 8
  pinMode(Lpwm_pin,OUTPUT);  // pin 5 (PWM) 
  pinMode(Rpwm_pin,OUTPUT);  // pin6(PWM) 
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


void Set_Speed(unsigned char pwm) //function of setting speed
{
  analogWrite(Lpwm_pin,pwm);
  analogWrite(Rpwm_pin,pwm);
}
void advance()    //  going forward
    {
     digitalWrite(pinRB,LOW);  // making motor move towards right rear
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,LOW);  // making motor move towards left rear
     digitalWrite(pinLF,HIGH); 
   
    }
void turnR()        //turning right(dual wheel)
    {
     digitalWrite(pinRB,LOW);  //making motor move towards right rear
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,LOW);  //making motor move towards left front
  
    }
void turnL()         //turning left(dual wheel)
    {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,LOW );   //making motor move towards right front
     digitalWrite(pinLB,LOW);   //making motor move towards left rear
     digitalWrite(pinLF,HIGH);
    
    }    
void stopp()        //stop
    {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,HIGH);
    
    }
void back()         //back up
    {
     digitalWrite(pinRB,HIGH);  //making motor move towards right rear     
     digitalWrite(pinRF,LOW);
     digitalWrite(pinLB,HIGH);  //making motor move towards left rear
     digitalWrite(pinLF,LOW);
      
    }
