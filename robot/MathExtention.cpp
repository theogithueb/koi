#include "MathExtention.h"
#include "Arduino.h"

int signum(int value) {
  if (value == 0) return  0;
  if (value >  0) return  1;
  if (value <  0) return -1;
  return 0;
}

/*
 * scales values between -512 to 512 to a range of -255 to 255
 */
int scale (int value) {
  if (abs(value) > 512) {
    return 255;
  }
  return signum(value) * map(abs(value), 0, 512, 0, 255 );
}
