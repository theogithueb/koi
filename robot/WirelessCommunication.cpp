#include "WirelessCommunication.h"
#include "Arduino.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



int recieve(int i){
  RF24 radio(7, 8);
  int numbers[2];
  numbers[1]=0;
  numbers[2]=0;
  if (radio.available()) {
    radio.read(&numbers, sizeof(numbers));
    Serial.println(numbers[1]);
    Serial.print("&");
    Serial.print(numbers[1]);
  }
  return numbers[i];
}
void deliver(int v,int w) {
  RF24 radio(7, 8);
  int numbers[2];
  numbers[1]=v;
  numbers[2]=w;
  radio.write(&numbers, sizeof(numbers));
}
