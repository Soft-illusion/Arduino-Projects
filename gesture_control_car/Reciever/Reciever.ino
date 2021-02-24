
#include "SR04.h"
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define TRIG_PIN A1
#define ECHO_PIN A0
#define MY_RF24_CE_PIN 10 
#define MY_RF24_CS_PIN 9
#define DISTANCE_THRESHOLD 20
#define Servo_compensation 90 // centre of the robot
#define SERVO_PIN 3
#define A1Out 7
#define A2Out 8
#define B1Out 4
#define B2Out 2
#define Aspeed 6 
#define Bspeed 5
#define angle_deadband 30
#define dead_speed 150
#define max_speed 255



Servo myservo;
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

long a;
long a1=1000;
float Pitch = 0;
float Roll = 0;
float package[2];

RF24 radio(MY_RF24_CE_PIN, MY_RF24_CS_PIN); // CE, CSN
const byte addresses[][6] = {"00001","00002"};
void setup() {
  Serial.begin(9600);
  Serial.println("Code is here start ");
  pinMode(12, OUTPUT);
  radio.begin();
  myservo.attach(SERVO_PIN);
  myservo.write(Servo_compensation);// move servos to center position -> 90°
   
  
  pinMode(A1Out, OUTPUT);
  pinMode(A2Out, OUTPUT);
  pinMode(B1Out, OUTPUT);
  pinMode(B2Out, OUTPUT);
  pinMode(Aspeed, OUTPUT);
  pinMode(Bspeed, OUTPUT);
  
  Serial.println("Radio");
  radio.openReadingPipe(1, addresses[0]); // 00001
//  radio.setChannel(115);
  radio.setPALevel(RF24_PA_MIN);
  analogWrite(Aspeed, 180);
  analogWrite(Bspeed, 255);
  
}
void loop() {
//    for(int i=0; i<181;i=i+5){
//      myservo.write(i);
//      Serial.println(i);
//      delay(500);
//      }
  a=sr04.Distance();
  radio.startListening();
  while (!radio.available()){
    Serial.println("No data ... ");
    }
  radio.read(&package, sizeof(package));
  Serial.println("Reading data ... ");
  Serial.println(package[0]);
  Serial.println(package[1]);
  
  Pitch=package[0];
  Roll=package[1];
  radio.stopListening();
  myservo.write(Servo_compensation-Roll);
  wheel_move(Pitch,Roll);
//  speedControl();
//  delay(100);
  
  
  
}

void wheel_move(float pitch,float roll) {
//  Serial.println("pitch");
//  Serial.println(pitch);
//  Serial.println("roll");
//  Serial.println(roll);
  Serial.print("Distance Sensor :");
  Serial.println(a);
  if(pitch>angle_deadband){
    Serial.println("in pitch >20" );
   digitalWrite(A1Out, LOW);
   digitalWrite(A2Out, HIGH);
   digitalWrite(B1Out, HIGH);
   digitalWrite(B2Out, LOW);
   speed_writer(pitch);
  }
  else if (pitch < -angle_deadband && a>DISTANCE_THRESHOLD){
    Serial.println("in pitch <-20");
   digitalWrite(A1Out, HIGH); //front
   digitalWrite(A2Out, LOW);
   digitalWrite(B1Out, LOW); //front
   digitalWrite(B2Out, HIGH);
    speed_writer(-pitch);
  }
  else if(roll > angle_deadband && a>DISTANCE_THRESHOLD){
    Serial.println("in roll >20");
   digitalWrite(A1Out, HIGH);
   digitalWrite(A2Out, LOW);
   digitalWrite(B1Out, HIGH);
   digitalWrite(B2Out, LOW);
    speed_writer(roll);
  }
  else if(roll < -angle_deadband && a>DISTANCE_THRESHOLD) {
    Serial.println("in roll <-20");
   digitalWrite(A1Out, LOW);
   digitalWrite(A2Out, HIGH);
   digitalWrite(B1Out, LOW);
   digitalWrite(B2Out, HIGH);
    speed_writer(-roll);
  }
  else{
   digitalWrite(A1Out, HIGH);
   digitalWrite(A2Out, HIGH);
   digitalWrite(B1Out, HIGH);
   digitalWrite(B2Out, HIGH);
   speed_writer(angle_deadband);
  }  
  }


void speed_writer(float num){
  int speed_n = dead_speed+(max_speed-dead_speed)*(num-angle_deadband)/(90-angle_deadband);
  analogWrite(Aspeed, int(speed_n));
  analogWrite(Bspeed, int(speed_n));
  Serial.print("Speed :");
  Serial.println(int(speed_n));
  }




  void speedControl() {
  // Turn on motors
   digitalWrite(A1Out, HIGH); //front
   digitalWrite(A2Out, LOW);
   digitalWrite(B1Out, LOW); //front
   digitalWrite(B2Out, HIGH);
  
  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i=i+5) {
    analogWrite(Aspeed, i);
    analogWrite(Bspeed, 150);
    Serial.println(i);
    
    delay(500);
  }
  
  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; i=i-5) {
    analogWrite(Aspeed, i);
    analogWrite(Bspeed, i);
    Serial.println(i);
    delay(500);
  }
  
   digitalWrite(A1Out, LOW); //front
   digitalWrite(A2Out, LOW);
   digitalWrite(B1Out, LOW); //front
   digitalWrite(B2Out, LOW);
}
