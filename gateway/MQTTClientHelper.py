import paho.mqtt.client as mqtt
import handleData

class MQTTClientHelper:
  def __init__(self):
      
    self.mqttClient = mqtt.Client(mqtt.CallbackAPIVersion.VERSION1)
    self.mqttClient.username_pw_set('nguyentruongthan', "aio_qNbo71vk!!!!!0IuvOG!!!!utmbxMWMfphX8E".replace("!", ""))
    self.mqttClient.connect('io.adafruit.com', 1883, 60)

    #Register mqtt events
    self.mqttClient.on_connect = self.mqtt_connected
    self.mqttClient.on_subscribe = self.mqtt_subscribed
    self.mqttClient.on_message = self.mqtt_recv_message
    self.mqttClient.loop_start()
  

  def mqtt_connected(self, client, userdata, flags, rc):
      print("Connected succesfully!!")
      client.subscribe("nguyentruongthan/feeds/ai")

  def mqtt_subscribed(self, client, userdata, mid, granted_qos):
      print("Subscribed to Topic!!!")

  def mqtt_recv_message(self, client, userdata, message):
    payload = message.payload.decode("utf-8")
    handleData.processMQTTData(data = payload)

  def publish(self, message):
    self.mqttClient.publish(f'nguyentruongthan/feeds/ai', message)


mqttClientHelper = MQTTClientHelper()