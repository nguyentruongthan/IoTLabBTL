
#include "global.h"

void setup(){

  Serial.begin(9600);
  pinMode(BLINK_LED, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  scheduler.addTask(blinkLedTask, 5, 50);
  scheduler.addTask(recvUart, 1, 1);
  scheduler.addTask(readLightSensor, 233, 1000);// period 10s
  scheduler.addTask(readDHTSensor, 1233, 1500);// period 15s
}


void loop(){
  scheduler.update();
  scheduler.dispatchTasks();
  delay(10);
}


