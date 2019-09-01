
/*
 * controll the robot with an joystick attached direkt to the robot.
 */

#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_BUTTON 13

#define LEFT_PWM_PIN 9
#define LEFT_FORWARD_PIN 4
#define LEFT_BACKWARD_PIN 5

#define RIGHT_PWM_PIN 10
#define RIGHT_FORWARD_PIN 6
#define RIGHT_BACKWARD_PIN 7

void setup ()
{
  Serial.begin(9600);
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  digitalWrite(JOYSTICK_BUTTON,HIGH);
  Serial.println("Setup Finished");
}

void loop ()
{
  int offset = 512;
  int x = analogRead(JOYSTICK_X) - offset;
  int y = analogRead(JOYSTICK_Y) - offset;
  int button = digitalRead(JOYSTICK_BUTTON);

  // x after scale: x value of joystick scaled to PWM values (0 to 255)
  // y after scale: y value of joystick scaled to PWM values (0 to 255)
  x = scale(x); 
  y = scale(y);

  // v straight velocity of the robot from 0 to 255
  // w angular  velocity of the robot from 0 to 255
  int v =  x;
  int w = -y;

  Serial.print("v= ");
  Serial.print(v);

  Serial.print(" w= ");
  Serial.print(w);

  int l;
  int r;

  if (abs(w) > 10) {
    l = v - w;
    r = v + w;
    if (abs(l) > 255 || abs(r) > 255) {
      int maximum = max(abs(l), abs(r));
      l = signum(l) * map(abs(l), 0, maximum, 0, 255);
      r = signum(r) * map(abs(r), 0, maximum, 0, 255);
    }
  } else {
    l = v;
    r = v;    
  }

  turnWheel(LEFT_PWM_PIN,  LEFT_FORWARD_PIN,  LEFT_BACKWARD_PIN,  l);
  turnWheel(RIGHT_PWM_PIN, RIGHT_FORWARD_PIN, RIGHT_BACKWARD_PIN, r);

  Serial.print(" l= ");
  Serial.print(l);

  Serial.print(" r= ");
  Serial.print(r);
  
  //Serial.print(" x: ");
  //Serial.print(x);

  //Serial.print(" x_scaled: ");
  //Serial.print(x_scaled);
  
  //Serial.print(" y: ");
  //Serial.print(y);

  //Serial.print(" y_scaled: ");
  //Serial.print(y_scaled);

  Serial.print(" button: ");
  Serial.print(button);
  Serial.println();
  delay(500);
}


int scale (int value) {
  if (abs(value) > 512) {
    return 0;
  }
  if (abs(value) > 15) {
    return signum(value) * map(abs(value), 0, 512, 0, 255 );
  }
  return 0;
}

int signum(int value) {
  if (value == 0) return  0;
  if (value >  0) return  1;
  if (value <  0) return -1;
  return 0;
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
