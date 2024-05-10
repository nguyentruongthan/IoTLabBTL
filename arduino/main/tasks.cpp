#include "tasks.h"
#include "DHT.h"
#include <Arduino.h>
DHT dht(4, DHT22);


uint8_t blinkLedState = 0;
void blinkLedTask(){
  if(!blinkLedState){
    digitalWrite(BLINK_LED, 1);
    blinkLedState = 1;
  }else{
    digitalWrite(BLINK_LED, 0);
    blinkLedState = 0;
  }
}


void readLightSensor(){
  uint32_t value;
  value = analogRead(A0);
  Serial.println("!" + String(HEADER_SENSOR_VALUE) + ":0:" + String(value) + "#");
}

// void readHumiSolidSensor(void* args){
//   HumiSolidSensor *humiSolidSensor = static_cast<HumiSolidSensor*>(args);
//   humiSolidSensor->readSensorValue();
//   Serial.println("!" + String(HEADER_SENSOR_VALUE) + ":" + String(TYPE_HUMISOLID_SENSOR) + ":A" + String(humiSolidSensor->pin) + ":" + String(humiSolidSensor->value) + "#");
// }

void readDHTSensor(){
  
  dht.begin();
  float doAm = dht.readHumidity();
  float nhietDo = dht.readTemperature();
  
  Serial.println("!" + String(HEADER_SENSOR_VALUE) + ":2:" + String(doAm) + "#");
  Serial.println("!" + String(HEADER_SENSOR_VALUE) + ":3:" + String(nhietDo) + "#");
}

