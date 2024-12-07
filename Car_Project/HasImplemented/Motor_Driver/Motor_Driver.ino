//These pins control left wheel
int i3 = 23;
int i4 = 22;
int eb = 21;
//These pins control right wheel
int i1 = 32;
int i2 = 33;
int ea = 25;

void setup(){
// Pins for left wheel  
//  pinMode(i3, OUTPUT);
//  pinMode(i4, OUTPUT);
//  pinMode(eb, OUTPUT);
// Pins for right wheel
pinMode(i1, OUTPUT);
pinMode(i2, OUTPUT);
pinMode(ea, OUTPUT);
}
 
void loop(){
  //Go Forward left wheel
//  digitalWrite(i3, HIGH);
//  digitalWrite(i4, LOW);
//  digitalWrite(eb, HIGH);
  //Rev left wheel
//  digitalWrite(i3, LOW);
//  digitalWrite(i4, HIGH);
//  digitalWrite(eb, HIGH);
// Go Forward Right Wheel
 // digitalWrite(i1, HIGH);
  //digitalWrite(i2, LOW);
  //digitalWrite(ea, HIGH);
  digitalWrite(i1, LOW);
  digitalWrite(i2, HIGH);
  digitalWrite(ea, HIGH);
    
}
