#include "uart.h"
#include <Arduino.h>

String messageUart;

uint8_t isBegin = 0;
uint8_t isEnd = 0;
uint8_t beginIndex = 255;
uint8_t endIndex = 255;
uint8_t index = 0;

char serialData[256];

void handleMessage(String message){
  //<header:1bit><deviceID:1bit><value:1bit>
  uint8_t header = message[0] - 48;
  // Serial.println("!" + message + "#");
  if(header == HEADER_CONTROL_DEVICE){
    //control device
    uint8_t deviceID = message[1] - 48;
    uint8_t value = message[2] - 48;
    value = value == 1 ? HIGH : LOW;
    if(deviceID == 4){//pin D2
      // Serial.println("!Control 4#");
      digitalWrite(2, value);
    }else if(deviceID == 5){//pin D3
      // Serial.println("!Control 5#");
      digitalWrite(3, value);
    }else{
      Serial.println("!MessageError#");
    }
  }else{
    Serial.println("!MessageError#");
  }
}
void recvUart(){
  if(Serial.available()){
    
    uint8_t data = Serial.read();
    serialData[index] = data;
    switch(data){
      case '!':
        isBegin = 1;
        beginIndex = index;
        break;
      case '#':
        if(isBegin){
          isEnd = 1;
        }
        endIndex = index;
        break;
      default: 
        break;
    }
    index = (index + 1) % 256;
    if(isBegin && isEnd){
      isBegin = 0;
      isEnd = 0;
      messageUart = "";
      uint8_t temp = beginIndex + 1;
      while(temp != endIndex){
        messageUart += serialData[temp];
        temp = (temp + 1) % 256;
      }
      handleMessage(messageUart);
    }
  }
}
