#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {

  pinMode(35, INPUT);//rec reader
  pinMode(32, OUTPUT);//rec power
  digitalWrite(32, HIGH);//rec power ON

  pinMode(33, OUTPUT);//emitter power
  digitalWrite(33, HIGH);//emitter power ON

  //trigger
  pinMode(5, INPUT_PULLUP);

  //magTrig
  pinMode(17, INPUT_PULLUP); //(HIGH = ON)
  pinMode(4, OUTPUT); //buzzer

  Serial.begin(9600);
  
  pinMode(22, OUTPUT);//LED (LOW=ON)
  pinMode(25, OUTPUT);//Solenoid (HIGH=ON)

}

void loop() {
  // put your main code here, to run repeatedly:

  /*
  int inputt = analogRead(35);
  if(digitalRead(5) == LOW )//&& inputt > 0)
  {
    Serial.println(inputt);
  }*/

  //use trigger to push solenoid
  digitalWrite(25, !digitalRead(5));
  digitalWrite(22, digitalRead(5));

  digitalWrite(4, !digitalRead(17));



}
