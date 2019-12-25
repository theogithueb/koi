
/*
   controll the robot with an joystick attached direkt to the robot.
*/

#include "MathExtention.h"

#define JOYSTICK_TOTAL     1024
#define JOYSTICK_RANGE     512
#define MOTOR_MAXIMUM      255

#define JOYSTICK_X         A0
#define JOYSTICK_Y         A1
#define JOYSTICK_BUTTON    13

#define LEFT_PWM_PIN       9
#define LEFT_FORWARD_PIN   4
#define LEFT_BACKWARD_PIN  5

#define RIGHT_PWM_PIN      10
#define RIGHT_FORWARD_PIN  6
#define RIGHT_BACKWARD_PIN 7

void setup ()
{
  Serial.begin(9600);
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  digitalWrite(JOYSTICK_BUTTON, HIGH);
  Serial.println("Setup Finished");
}

void loop ()
{
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

  int l = 0;
  int r = 0;

  if (abs(w) > 10) {
    int maximum = abs(v) + abs(w);
    l = scale(l, MOTOR_MAXIMUM, maximum);
    r = scale(r, MOTOR_MAXIMUM, maximum);
  } else {
    l = v;
    r = v;
  }

  turnWheel(LEFT_PWM_PIN,  LEFT_FORWARD_PIN,  LEFT_BACKWARD_PIN,  l);
  turnWheel(RIGHT_PWM_PIN, RIGHT_FORWARD_PIN, RIGHT_BACKWARD_PIN, r);
}

void turnWheel(byte pwmPin, byte forwardPin, byte backwardPin, int velocity) {
  if (velocity > 0) {
    digitalWrite(forwardPin,  HIGH);
    digitalWrite(backwardPin, LOW );
  }
  if (velocity < 0) {
    digitalWrite(forwardPin,  LOW );
    digitalWrite(backwardPin, HIGH);
  }
  analogWrite(pwmPin, abs(velocity));
}
