

#ifdef Encoder_PWM2

#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
//ICACHE_RAM_ATTR
#endif

void rotaryInterrupt_PWM2() // TFT PWM Brightness Adjust
{
  int rotaryState;

  // Read rotary state (Counter clockwise) -2, -1, 0, 1, 2 (Clockwise)
  rotaryState = rotary.read();
  // Count up or down by using rotary speed
  if (rotaryState == 0) {
    // No change
    return;

  } else if (abs(rotaryState) >= 2) {
    brightness_count += rotaryState * 2;

  } else {

    brightness_count += rotaryState;
  }

  // Limit count to a minimum and maximum value
  if (brightness_count > 100) {
    brightness_count = 100;

  }
  if (brightness_count < 0) {
    brightness_count = 0;
  }

  if (brightness_countLast != brightness_count) {
    brightness_countLast = brightness_count;
    //analogWrite(TFT_backlight_PIN , brightness_count );// Reserved!!! not supported on ESP32 Reserved
  }
}
#endif

//---------------------------------------------------
#ifdef Encoder_HID // Reserved!!! not supported on ESP32 Reserved

void rotaryInterrupt() // Volume control
{
  int rotaryState;

  // Read rotary state (Counter clockwise) -3, -2, -1, 0, 1, 2, 3 (Clockwise)
  rotaryState = rotary.read();

  if (rotaryState < 0)  {
    //Do Something Down

  } else {

    if (rotaryState > 0)  {
      //Do Something UP

    }
  }
}

#endif
