#include "WirelessCommunication.h"
#include "Arduino.h"

int recieve(int i){
  int recieved_numbers[2];
  recieved_numbers[1]=0;
  recieved_numbers[2]=0;
  return recieved_numbers[i];
}
void deliver(int v,int w) {
  int deliver_numbers[2];
  deliver_numbers[1]=v;
  deliver_numbers[2]=w;
}
