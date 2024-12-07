///////////////////////////////////////////////////////////////////////////////////////
// OVERVIEW
////////////////////////////////////////////////////////////////////////////////////////
/*
DESCRIPTION: Receiver setup and loop

AUTHOR: Tuan Kiet Le & Brendan Thomas.

COMMENTS:

*/

#include "Receiver.h"

void setup() {
  //These pins control left wheel
  leftMotor.input1Pin = 23;
  leftMotor.input2Pin = 21;
  leftMotor.enablePin = 18;
  
  //These pins control right wheel
  rightMotor.input1Pin = 33;
  rightMotor.input2Pin = 26;
  rightMotor.enablePin = 27;

  //Initialize Serial monitor
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  //Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //Once ESPNow is successfully Init, we will register for recv CB to
  //get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);
  //Initialize peerInfo
  esp_now_peer_info_t peerInfo;
  //Copy the receiver MAC address to the peer_addr
  memcpy(peerInfo.peer_addr, RxMACaddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if(esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
  // Pins for left wheel  
  pinMode(leftMotor.input1Pin, OUTPUT);
  pinMode(leftMotor.input2Pin, OUTPUT);
  pinMode(leftMotor.enablePin, OUTPUT);
  // Pins for right wheel
  pinMode(rightMotor.input1Pin, OUTPUT);
  pinMode(rightMotor.input2Pin, OUTPUT);
  pinMode(rightMotor.enablePin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Status:\t");
  Serial.println(receivedData.motorStatus);
  Serial.print("Speed:\t");
  Serial.println(receivedData.motorSpeed);
  Serial.print("Mode:\t");
  Serial.println(receivedData.motorMode);

  sentData.rightSensor = rightSonar.ping_cm();
  sentData.leftSensor = leftSonar.ping_cm();
  sentData.middleSensor = middleSonar.ping_cm();

  
  esp_err_t result = esp_now_send(RxMACaddress, (uint8_t *) &sentData, sizeof(sentData));
  if (result == ESP_OK) Serial.println("Sent with success");
  else Serial.println("Error sending the data");
  if (receivedData.motorMode == 0) {
    //Get the speed from the received data
    Speed = motorSpeed(receivedData.motorSpeed);
    //Speed = 255;
    if(receivedData.motorStatus == 1){
      //Go Forward Right Wheel
    GoForward(rightMotor, leftMotor, Speed);
    }else if(receivedData.motorStatus == 2){
      GoBackward(rightMotor, leftMotor, Speed);
    }else if(receivedData.motorStatus == 3){
      TurnLeft(rightMotor, leftMotor, Speed);
      delay(500);
      Station(rightMotor, leftMotor);
      delay(1000);
    }else if(receivedData.motorStatus == 4){
      TurnRight(rightMotor, leftMotor, Speed);
      delay(500);
      Station(rightMotor, leftMotor);
      delay(1000);
    }else{
      Station(rightMotor, leftMotor);
    }

    /////// AUTODRIVE ////////
  } else if (receivedData.motorMode == 1) {
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
    AutoDrive(middleSensor_DIS, rightSensor_DIS, leftSensor_DIS);
  }
  
}
