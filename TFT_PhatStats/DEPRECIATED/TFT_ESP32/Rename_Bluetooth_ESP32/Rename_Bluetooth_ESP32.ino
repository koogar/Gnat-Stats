//https://techtutorialsx.com/2018/03/06/esp32-arduino-bluetooth-classic-setting-the-device-name/

#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_bt_device.h"
 
bool initBluetooth(const char *deviceName)
{
  if (!btStart()) {
    Serial.println("Failed to initialize controller");
    return false;
  }
 
  if (esp_bluedroid_init()!= ESP_OK) {
    Serial.println("Failed to initialize bluedroid");
    return false;
  }
 
  if (esp_bluedroid_enable()!= ESP_OK) {
    Serial.println("Failed to enable bluedroid");
    return false;
  }
 
  esp_bt_dev_set_device_name(deviceName);
 
  esp_bt_gap_set_scan_mode(ESP_BT_SCAN_MODE_CONNECTABLE_DISCOVERABLE);
 
}
 
void setup() {
  Serial.begin(115200);
 
  if(!initBluetooth("ESP32 BT")){
    Serial.println("Bluetooth init failed");
  };
 
}
 
void loop() {}
