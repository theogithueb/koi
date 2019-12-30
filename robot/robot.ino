/*
   controll the robot with an joystick attached direkt to the robot.
*/

#include "MathExtention.h"
#include "WirelessCommunication.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define JOYSTICK_TOTAL     1024
#define JOYSTICK_RANGE     512
#define MOTOR_MAXIMUM      255

#define LEFT_PWM_PIN       9  //D9
#define LEFT_FORWARD_PIN   4  //D4
#define LEFT_BACKWARD_PIN  5  //D5

#define RIGHT_PWM_PIN      10 //D10
#define RIGHT_FORWARD_PIN  6  //D6
#define RIGHT_BACKWARD_PIN 3  //D3

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup () {
  Serial.begin(9600);
  Serial.println("Setup Finished");
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop () {
  int v = recieve(1);
  int w = recieve(2);
  
  int l = 0;
  int r = 0;

  if (abs(w) > 5) {
    l = v - w;
    r = v + w;
    int maximum = max(abs(l),abs(r));
    if (maximum > MOTOR_MAXIMUM) {
      l = scale(l, MOTOR_MAXIMUM, maximum);
      r = scale(r, MOTOR_MAXIMUM, maximum);
    }
    if (v > 0 && w > 0 || v > 0 && w < 0) {
      l = l;
      r = r;  
    }
    if (v < 0 && w < 0 || v < 0 && w > 0) {
      int fooL = l;
      int fooR = r;
      l = fooR;
      r = fooL;
    }
    
  } else {
    l = v;
    r = v;
  }

  Serial.print(" v: ");
  Serial.print(v);
  
  Serial.print(" w: ");
  Serial.print(w);

  Serial.print(" l: ");
  Serial.print(l);
  
  Serial.print(" r: ");
  Serial.print(r);

  Serial.println();

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
