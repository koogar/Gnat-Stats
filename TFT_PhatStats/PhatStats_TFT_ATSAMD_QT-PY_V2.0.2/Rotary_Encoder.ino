
#ifdef Encoder_PWM2
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
    analogWrite(TFT_backlight_PIN , brightness_count );

#ifdef Neo_BrightnessAuto // Adjust NeoPixel brightness with screen brightness
    pixels.setBrightness(brightness_count / Neo_DivideBy); //
#endif

  }
}
#endif

//---------------------------------------------------
#ifdef Encoder_HID

void rotaryInterrupt() // Volume control
{
  int rotaryState;

  // Read rotary state (Counter clockwise) -3, -2, -1, 0, 1, 2, 3 (Clockwise)
  rotaryState = rotary.read();

  if (rotaryState < 0)  {

    //Do Something Here
    Consumer.write(MEDIA_VOLUME_DOWN);
    Consumer.write(MEDIA_VOLUME_DOWN);


  } else {

    if (rotaryState > 0)  {

      //Do Something Here
      Consumer.write(MEDIA_VOLUME_UP);
      Consumer.write(MEDIA_VOLUME_UP);
    }
  }
}

#endif




#ifdef Debug
void print_PWM()
{
  tft.setFont(&Org_01);
  //tft.setTextColor(ILI9341_WHITE);
  tft.fillRoundRect  (105, 55, 94, 30, 4, ILI9341_RED); // print brightness % over CPU Freq
  tft.drawRoundRect  (105, 55, 94, 30, 4, ILI9341_WHITE);  // print brightness % over CPU Freq


  tft.setCursor(114, 66);
  tft.setTextSize(1);
  tft.print("Back- ");
  tft.setTextSize(1);
  tft.setCursor(114, 75);
  tft.print("Light");

  tft.setCursor(144, 74);
  tft.setTextSize(3);
  tft.print(brightness_count); // Print Scale in human 0-100%
  tft.setTextSize(2);
  tft.println("%");
}
#endif
