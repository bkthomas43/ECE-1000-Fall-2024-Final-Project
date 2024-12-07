////////////////////////////////////////////////////////////////////////////////////////
// OVERVIEW
////////////////////////////////////////////////////////////////////////////////////////
/*
DESCRIPTION: Practice Using Sensor  

AUTHOR: Tuan Kiet Le & Brendan Thomas.

COMMENTS:

HISTORY:

*/


///////////////////////////////////////////////////////////////////////////////////////
//INCLUDES
///////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////
//DEFINES, CONSTANT AND MACROS
int xPin    = 36;
int yPin    = 39;
int button  = 34;
int xVal;
int yVal;
int buttonState;
//////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
//GLOBALS
///////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
int getMotorStatus(int xVal, int yVal)// MODE 1: FULL SPEED, MODE 2: HALF-SPEED, MODE 3: QUARTER-SPEED
{
//If the joystick is pushed forward, increase speed to max speed
  if (xVal > 3500) {
    return 1;
//If the joystick is pulled backward, decrease speed to quarter speed
  } else if (xVal < 1000) {
    return 3;
//If the joystick is idle or not pushed/pulled to previous values, speed remains at half speed
  } else {
    return 2;
  }
}
void controlMotor(int motorStatus){
  switch(motorStatus){
    case 1: Serial.print("Full Speed");
            Serial.println();
            break;
    case 2: Serial.print("Half Speed");
            Serial.println();
            break;        
    case 3: Serial.print("Quarter Speed");
            Serial.println();
  }
}
//////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(button , INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Send out pulse and receive pulse
 
  xVal        = analogRead(xPin);
  yVal        = analogRead(yPin);
  buttonState = digitalRead(button);
 
  Serial.print("X: ");
  Serial.print(xVal);
  Serial.print(" | Y: ");
  Serial.print(yVal);
  Serial.print(" | button: ");
  Serial.print(buttonState);
  Serial.println();
 
  controlMotor(getMotorStatus(xVal, yVal));
  delay(1000);
}