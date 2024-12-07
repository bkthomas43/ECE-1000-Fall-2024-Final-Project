///////////////////////////////////////////////////////////////////////////////////////
// OVERVIEW
////////////////////////////////////////////////////////////////////////////////////////
/*
DESCRIPTION: Practice Using Sensor  

AUTHOR: Tuan Kiet Le & Brendan Thomas.

COMMENTS:

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
int getMotorStatus(int xVal, int yVal)// MODE 1: FORWARD, MODE 2: REVERSE, MODE 3: LEFT, MODE 4: RIGHT
{
  if (yVal > 3500) {
    if (xVal > 3500) {
      return 1;
    }else if (xVal < 1000) {
      return 2;
    }else
      return 4;
  }else if (yVal < 1000) {
    if (xVal > 3500) {
      return 1;
    }else if (xVal < 1000) {
      return 2;
    }else
      return 3;
  }else if (xVal > 3500) {
    return 1;
  }else if (xVal < 1000) {
    return 2;
  }else
  return 0;
}
void controlMotor(int motorStatus){
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
