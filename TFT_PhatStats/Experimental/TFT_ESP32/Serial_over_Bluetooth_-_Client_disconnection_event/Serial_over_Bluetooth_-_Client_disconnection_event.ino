
//https://www.dfrobot.com/blog-1204.html
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  if(event == ESP_SPP_SRV_OPEN_EVT){
    Serial.println("Client Connected");
  }

  if(event == ESP_SPP_CLOSE_EVT ){
    Serial.println("Client disconnected");
  }
}

void setup() {
  Serial.begin(115200);

  SerialBT.register_callback(callback);

  if(!SerialBT.begin("ESP32")){
    Serial.println("An error occurred initializing Bluetooth");
  }else{
    Serial.println("Bluetooth initialized");
  }
}

void loop() {}
