import json
import constants
import MQTTClientHelper
import uart
def processMQTTData(data: str):
  splitMessage = data.split(':')
  header = splitMessage[0]
  if(header == str(constants.HEADER_CONTROL_DEVICE)):
    #<HEADER_CONTROL_DEVICE>:<deviceID>:<value>:<ack>
    deviceID = splitMessage[1]
    value = splitMessage[2]
    ack = splitMessage[3]
    #send message to control device to MCU
    uart.sendData(f"!{constants.HEADER_CONTROL_DEVICE}{deviceID}{value}#")
    print(f'Control {deviceID} to {value}')
    #send ACK to mqtt
    MQTTClientHelper.mqttClientHelper.publish("ai", f'{constants.HEADER_ACK}:{ack}')


def processUartData(data: str):
  #replace charactor ! and # at start and end of data
  data = data.replace("!", "")
  data = data.replace("#", "")

  #spilit data to array with spilt charactor is ":" 
  splitMessage = data.split(":")
  header = splitMessage[0]
  # print(splitMessage)
  if(header == str(constants.HEADER_SENSOR_VALUE)):
    #receive sensor value
    deviceID = splitMessage[1]
    value = splitMessage[2]

    message = f"{constants.HEADER_SENSOR_VALUE}:{deviceID}:{value}"
    MQTTClientHelper.mqttClientHelper.publish(message)