#include <Servo.h>
Servo myservo;  
int pos = 20;
#include<SoftwareSerial.h>

SoftwareSerial ArduinoUno(0,1);
#include <LiquidCrystal.h>
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int IRSensor = 8; // connect ir sensor to arduino pin 2
int LED = 13; // conect Led to arduino pin 13
int LED2 = 12 ;

const int trigPin = 9;
const int echoPin = 10;

long duration;
float distance;

void setup() 
{
  myservo.attach(11);

  pinMode (IRSensor, INPUT); // sensor pin INPUT
  pinMode (LED, OUTPUT); // Led pin OUTPUT
  pinMode (LED2, OUTPUT);

  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");

  // put your setup code here, to run once:
  //randomSeed(analogRead(0));
  ArduinoUno.begin(9600);
  Serial.begin(9600);
  
  pinMode(0,INPUT);
  pinMode(1,OUTPUT);   


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.write(0);
}

void loop()
{
  Serial.begin(9600);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = 0.034*(duration/2);
  Serial.println(distance);
  
  int statusSensor = digitalRead (IRSensor);

  Serial.println(statusSensor);
  
  if (statusSensor == 0) 
  {
    if (distance < 7){
    digitalWrite(LED, LOW); // LED LOW
    digitalWrite(LED2, HIGH);
    lcd.print("Filled");
    myservo.write(0);
    ArduinoUno.print(0);}
    else {
    digitalWrite(LED, HIGH); // LED High
    myservo.write(180);delay(5000);
    digitalWrite(LED2, LOW);
    lcd.print("Empty");
    ArduinoUno.print(1);}   
  }
  else
  {
    digitalWrite(LED, LOW);
    digitalWrite(LED2, LOW);
    myservo.write(0);
    lcd.print("Empty");
    ArduinoUno.print(1);
  }

  //ArduinoUno.print(int(distance)); //this is sending to nodemcu

  delay(300);
}
