///////////////////////////////////////////////////////////////////////////////////////
// OVERVIEW
////////////////////////////////////////////////////////////////////////////////////////
/*
DESCRIPTION: Receiver setup and loop

AUTHOR: Tuan Kiet Le & Brendan Thomas.

COMMENTS:

*/

///////////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <ESP32_NOW.h>
#include <WiFi.h>
#include "NewPing.h"
///////////////////////////////////////////////////////////////////////////////////////

//DEFINES, CONSTANT AND MACROS
//Define the message structure
typedef struct sensor_message{
  int middleSensor;
  int rightSensor;
  int leftSensor;
}sensor_message;
struct sensor_message sentData;
uint8_t RxMACaddress[] = {0x88,0x13,0xbf,0x00,0xd2,0x24};
typedef struct struct_message
{
  int motorStatus;
  int motorSpeed;
  int motorMode;
}struct_message;
struct_message receivedData;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
//Define motor structure
typedef struct motor{
    int enablePin;
    int input1Pin;
    int input2Pin;
}motor;
//Initialize left and right motor
motor rightMotor;
motor leftMotor;

int Speed;

//Define constant and pin out for three sensor
#define MAX_DISTANCE 400

#define rightSensor_TRIG  13
#define rightSensor_ECHO  12

#define leftSensor_TRIG  15
#define leftSensor_ECHO  4

#define middleSensor_TRIG  14
#define middleSensor_ECHO  36
//Initialize distance of each sensor
float rightSensor_DIS;
float leftSensor_DIS;
float middleSensor_DIS;
//Minimum Distance Before Action
const int autoSpeed = 191;
const float MIN_DISTANCE = 10.00;
const int AUTO_DRIVE = 1;
const int MANUAL_DRIVE = 0;
//Initialize module NewPing for each sensor
NewPing rightSonar(rightSensor_TRIG, rightSensor_ECHO, MAX_DISTANCE);
NewPing leftSonar(leftSensor_TRIG, leftSensor_ECHO, MAX_DISTANCE);
NewPing middleSonar(middleSensor_TRIG, middleSensor_ECHO, MAX_DISTANCE);

//////////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
int motorSpeed(int motorStatus) {
  if (motorStatus == 1) {
    return 255;
  } else if (motorStatus == 2) {
    return 191;
  } else if (motorStatus == 3) {
    return 137;
  }
}
//Go Forward Function
void GoForward(struct motor rightMotor, struct motor leftMotor, int speed) {
  //Go Forward Right Wheel
  digitalWrite(rightMotor.input1Pin, HIGH);
  digitalWrite(rightMotor.input2Pin, LOW);
  analogWrite(rightMotor.enablePin, speed);
  // Go Forward Left Wheel
  digitalWrite(leftMotor.input1Pin, HIGH);
  digitalWrite(leftMotor.input2Pin, LOW);
  analogWrite(leftMotor.enablePin, speed);
}
//Reverse Funtion
void GoBackward(struct motor rightMotor, struct motor leftMotor, int speed) {
  //Reverse Right wheel
  digitalWrite(rightMotor.input1Pin, LOW);
  digitalWrite(rightMotor.input2Pin, HIGH);
  analogWrite(rightMotor.enablePin, speed);
  //Reverse Left Wheel
  digitalWrite(leftMotor.input1Pin, LOW);
  digitalWrite(leftMotor.input2Pin, HIGH);
  analogWrite(leftMotor.enablePin, speed);
}

//Turn Left Function
void TurnLeft(struct motor rightMotor, struct motor leftMotor, int speed) {
  // Go Forward Right Wheel
  digitalWrite(rightMotor.input1Pin, HIGH);
  digitalWrite(rightMotor.input2Pin, LOW);
  analogWrite(rightMotor.enablePin, speed);
  //Rev left wheel
  digitalWrite(leftMotor.input1Pin, LOW);
  digitalWrite(leftMotor.input2Pin, HIGH);
  analogWrite(leftMotor.enablePin, speed);
}

//Turn Right Function
void TurnRight(struct motor rightMotor, struct motor leftMotor, int speed) {
  //Go Forward left wheel
  digitalWrite(rightMotor.input1Pin, LOW);
  digitalWrite(rightMotor.input2Pin, HIGH);
  analogWrite(rightMotor.enablePin, speed);
  //Reverse Right Wheel
  digitalWrite(leftMotor.input1Pin, HIGH);
  digitalWrite(leftMotor.input2Pin, LOW);
  analogWrite(leftMotor.enablePin, speed);
}

void Station(struct motor rightMotor, struct motor leftMotor){
  digitalWrite(rightMotor.input1Pin, LOW);
  digitalWrite(rightMotor.input2Pin, LOW);
  digitalWrite(rightMotor.enablePin, LOW);
  // Go Forward Left Wheel
  digitalWrite(leftMotor.input1Pin, LOW);
  digitalWrite(leftMotor.input2Pin, LOW);
  digitalWrite(leftMotor.enablePin, LOW);
}

//Callback function that will be executed when data is received
void OnDataRecv(const esp_now_recv_info_t  *mac_addr, const uint8_t *incomingData, int len) { 
  memcpy(&receivedData, incomingData, sizeof(receivedData));//Copy the incomingData to the receivedData
  Serial.print("\r\nMotor status:\t ");
  Serial.println(receivedData.motorStatus);
  //Speed
  Serial.print("\r\nMotor Speed:\t ");
  Serial.println(receivedData.motorSpeed);
}
//Based on the motor print the output of the motor's action
void controlMotor(int motorStatus, int motorSpeed){
  switch(motorStatus){
    case 1: Serial.print("Forward");
             Serial.println();
             break;
    case 2: Serial.print("REv");
             Serial.println();
             break;        
    case 3: Serial.print("left");
             Serial.println();
             break;
    case 4: Serial.print("right");
             Serial.println();
             break;
    case 0: Serial.print("do nothing");
             Serial.println();
             break;
  }
  switch(motorSpeed){
    case 1: Serial.print("Full Speed");
              Serial.println();
              break;
    case 2: Serial.print("Half Speed");
              Serial.println();
              break;
    case 3: Serial.print("Quarter Speed");
              Serial.println();
              break;
  }
}
//////////////////////////////////
// AutoDrive
//////////////////////////////////

void AutoDrive(float middleSensor_DIS, float rightSensor_DIS, float leftSensor_DIS){
  if(middleSensor_DIS > MIN_DISTANCE){
      GoForward(rightMotor, leftMotor, autoSpeed);
    } else {
      if(rightSensor_DIS <= MIN_DISTANCE){
        TurnLeft(rightMotor, leftMotor, Speed);
        delay(500);
        Station(rightMotor, leftMotor);
        delay(1000);
      } else if(leftSensor_DIS <= MIN_DISTANCE){
        TurnRight(rightMotor, leftMotor, Speed);
        delay(500);
        Station(rightMotor, leftMotor);
        delay(1000);
      } else {
        GoBackward(rightMotor, leftMotor, autoSpeed);
        delay(1000);
        TurnRight(rightMotor, leftMotor, autoSpeed);
      }
    }
  }  

