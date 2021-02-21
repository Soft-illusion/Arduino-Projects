
#include "SR04.h"
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define TRIG_PIN 12
#define ECHO_PIN 11
#define MY_RF24_CE_PIN 10 
#define MY_RF24_CS_PIN 9
Servo myservo;
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;
long a1=1000;
int A1Out = 2;
int A2Out = 4;
int B1Out = 5;
int B2Out = 7;
float Pitch = 0;
float Roll = 0;
float package[2];

RF24 radio(MY_RF24_CE_PIN, MY_RF24_CS_PIN); // CE, CSN
const byte addresses[][6] = {"00001"};
void setup() {
  Serial.println("Code is here start ");
  pinMode(12, OUTPUT);
  radio.begin();
  myservo.attach(8);
  myservo.write(90);// move servos to center position -> 90°
   
  Serial.begin(9600);
  pinMode(A1Out, OUTPUT);
  pinMode(A2Out, OUTPUT);
  pinMode(B1Out, OUTPUT);
  pinMode(B2Out, OUTPUT);
  Serial.println("Radio");
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}
void loop() {

  a=sr04.Distance();
  radio.startListening();
  while (!radio.available()){
    Serial.println("No data ... ");
    }
  radio.read(&package, sizeof(package));
  Serial.println("Reading data ... ");
  Pitch=package[0];
  Roll=package[1];
  
  wheel_move(Pitch,Roll);
  radio.stopListening();
}

void wheel_move(float pitch,float roll) {
  Serial.println("pitch");
  Serial.println(pitch);
  Serial.println("roll");
  Serial.println(roll);
  a=a1;
  Serial.println(a);
  if(pitch>20){
    Serial.println("in pitch >20");
   digitalWrite(A1Out, LOW);
   digitalWrite(A2Out, HIGH);
   digitalWrite(B1Out, HIGH);
   digitalWrite(B2Out, LOW);
   myservo.write(30);
   if(a<10){
   digitalWrite(A1Out, HIGH);
   digitalWrite(A2Out, HIGH);
   digitalWrite(B1Out, HIGH);
   digitalWrite(B2Out, HIGH);
  }
  }
  else if (pitch < -20){
    Serial.println("in pitch <-20");
   digitalWrite(A1Out, HIGH); //front
   digitalWrite(A2Out, LOW);
   digitalWrite(B1Out, LOW); //front
   digitalWrite(B2Out, HIGH);
      myservo.write(60);
   if(a<10){
   digitalWrite(A1Out, HIGH);
   digitalWrite(A2Out, HIGH);
   digitalWrite(B1Out, HIGH);
   digitalWrite(B2Out, HIGH);
  }
  }
  else if(roll > 20){
    Serial.println("in roll >20");
   digitalWrite(A1Out, HIGH);
   digitalWrite(A2Out, LOW);
   digitalWrite(B1Out, HIGH);
   digitalWrite(B2Out, LOW);
      myservo.write(120);
   if(a<10){
   digitalWrite(A1Out, HIGH);
   digitalWrite(A2Out, HIGH);
   digitalWrite(B1Out, HIGH);
   digitalWrite(B2Out, HIGH);
  }
  }
  else if(roll < -20) {
    Serial.println("in roll <-20");
   digitalWrite(A1Out, LOW);
   digitalWrite(A2Out, HIGH);
   digitalWrite(B1Out, LOW);
   digitalWrite(B2Out, HIGH);
      myservo.write(90);
   if(a<10){
   digitalWrite(A1Out, HIGH);
   digitalWrite(A2Out, HIGH);
   digitalWrite(B1Out, HIGH);
   digitalWrite(B2Out, HIGH);
  }
  }
  else{
   digitalWrite(A1Out, HIGH);
   digitalWrite(A2Out, HIGH);
   digitalWrite(B1Out, HIGH);
   digitalWrite(B2Out, HIGH);
  }
  }
