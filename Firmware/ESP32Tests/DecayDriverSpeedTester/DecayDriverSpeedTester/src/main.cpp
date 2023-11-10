#include <Arduino.h>

#define INPUT_PIN 32
#define OUTPUT_PIN 33
#define LEDD 22

int resetMillis = 0;
int dutyMillis = 0;
int printMillis = 0;
int ledState = false;

bool state = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT);
  pinMode(LEDD, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  //fastest is ON 100%
  //slowest is 1 second on/off

  int potVal = analogRead(INPUT_PIN);
  int dutyCycle = map(potVal, 40, 4095 , 0, 500);
  dutyCycle = dutyCycle < 0 ? 0: dutyCycle; 

  int timeToWait = 0;
  if(state)
  {
    timeToWait = 45;//min reliable extend time
  }
  else
  {
    timeToWait = dutyCycle; //min reliable retract time around 42?
  }

  if(millis() - dutyMillis > timeToWait)
  {
    //Serial.printf("OFF, %d\n", dutyCycle, potVal);
    dutyMillis = millis();
    state = !state;
    digitalWrite(OUTPUT_PIN, state);
  }


  //determines min extend time, doing a short pulse every 2 seconds (pulse decided by POT)
  // //solenoid is ON
  // if(millis() - resetMillis > 1000 && !state)
  // {
  //   resetMillis = millis();
  //   dutyMillis = resetMillis;

  //   Serial.printf("ON\n");

  //   state = true;
  //   digitalWrite(OUTPUT_PIN, state);
  // }

  // //turn OFF
  // if(millis() - dutyMillis > dutyCycle && state)
  // {
  //   Serial.printf("OFF, %d\n", dutyCycle, potVal);
  //   state = false;
  //   digitalWrite(OUTPUT_PIN, state);
  // }



  if(millis() - printMillis >= 100)
  {
    digitalWrite(LEDD, ledState);
    printMillis = millis();
    Serial.printf("Duty Cycle: %d/500\n", dutyCycle);
    ledState = ! ledState;
  }
  



}

