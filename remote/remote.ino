/*
   controll the robot with an joystick attached direkt to the robot.
*/

#include "MathExtention.h"
#include "WirelessCommunication.h"
#define JOYSTICK_TOTAL     1024
#define JOYSTICK_RANGE     512
#define MOTOR_MAXIMUM      255

#define JOYSTICK_X         A0 //A0
#define JOYSTICK_Y         A1 //A1
#define JOYSTICK_BUTTON    13 //D13


void setup () {
  Serial.begin(9600);
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  digitalWrite(JOYSTICK_BUTTON, HIGH);
  Serial.println("Setup Finished");
}

void loop () {
  int xJoy = analogRead(JOYSTICK_X) - JOYSTICK_RANGE;
  int yJoy = analogRead(JOYSTICK_Y) - JOYSTICK_RANGE;
  int button = digitalRead(JOYSTICK_BUTTON);

  // x after scale: x value of joystick scaled to PWM values (0 to 255), appield backlash of 15 afterwards
  // y after scale: y value of joystick scaled to PWM values (0 to 255), appield backlash of 15 afterwards
  int xTrimmed = backlash(scale(xJoy, MOTOR_MAXIMUM, JOYSTICK_RANGE), 10);
  int yTrimmed = backlash(scale(yJoy, MOTOR_MAXIMUM, JOYSTICK_RANGE), 10);

  // v straight velocity of the robot from 0 to 255
  // w angular  velocity of the robot from 0 to 255
  int v =  xTrimmed;
  int w = -yTrimmed;

  deliver(v,w);
  Serial.println("Delivered");
  Serial.print("x: ");
  Serial.print(xTrimmed);
  
  Serial.print(" y: ");
  Serial.print(yTrimmed);

  Serial.print(" v: ");
  Serial.print(v);
  
  Serial.print(" w: ");
  Serial.print(w);
}
