#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "stdint.h"
#include "scheduler.h"
#include "tasks.h"
#include <Arduino.h>

#include "uart.h"

#define BLINK_LED 13
#define TYPE_LIGHT_SENSOR 0
#define TYPE_HUMISOLID_SENSOR 1
#define TYPE_DHT_SENSOR 2
#define TYPE_DIGITAL_OUTPUT 3
#define TYPE_DIGITAL_SERVO 4

#define HEADER_CREATE 0
#define HEADER_DELETE 1
#define HEADER_SENSOR_VALUE 2
#define HEADER_CONTROL_DEVICE 3



#endif /* INC_GLOBAL_H_ */