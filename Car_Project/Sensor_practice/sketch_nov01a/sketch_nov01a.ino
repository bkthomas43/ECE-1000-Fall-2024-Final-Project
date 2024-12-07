#include "NewPing.h"//Include this library

#define MAX_DISTANCE 400

#define rightSensor_TRIG  32
#define rightSensor_ECHO  25

#define leftSensor_TRIG  15
#define leftSensor_ECHO  2

#define middleSensor_TRIG  13
#define middleSensor_ECHO  12

float rightSensor_DIS;
float leftSensor_DIS;
float middleSensor_DIS;

NewPing rightSonar(rightSensor_TRIG, rightSensor_ECHO, MAX_DISTANCE);
NewPing leftSonar(leftSensor_TRIG, leftSensor_ECHO, MAX_DISTANCE);
NewPing middleSonar(middleSensor_TRIG, middleSensor_ECHO, MAX_DISTANCE);
void setup() {
  
//Initialize NewPing on rightSonar
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Get the distance of rightSensor
  rightSensor_DIS = rightSonar.ping_cm();
  //Get the distance of leftSensor
  leftSensor_DIS = leftSonar.ping_cm();
  //Get the distance of middleSensor
  middleSensor_DIS = middleSonar.ping_cm();
  Serial.print("Right Sensor: ");
  Serial.print(rightSensor_DIS);
  Serial.print(" | Middle Sensor: ");
  Serial.print(middleSensor_DIS);
  Serial.print(" | Left Sensor: ");
  Serial.print(leftSensor_DIS);
  Serial.print("x");
  Serial.println();
  delay(500);
  delay(200);
}
