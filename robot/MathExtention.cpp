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
 * return the scaleTarget if value is greater or equal to scaleOrigin
 */
int scale (int value, int scaleTarget, int scaleOrigin) {
  if (abs(value) >= scaleOrigin) {
    return signum(value) * scaleTarget;
  }
  return signum(value) * map(abs(value), 0, scaleOrigin, 0, scaleTarget );
}

/*
 * returns the value if its absolute value is above the backlash, returns zero instead
 */
int backlash(int value, int backlash) {
  return (abs(value) > backlash) ? value : 0; 
}
