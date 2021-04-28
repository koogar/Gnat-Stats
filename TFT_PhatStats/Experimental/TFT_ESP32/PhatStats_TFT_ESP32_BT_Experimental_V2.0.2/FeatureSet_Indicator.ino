

void FeatureSet_Indicator2 () {

#define X_Offset 0
#define Y_Offset 210

  int featureDelay = 200;
  delay(featureDelay);

  tft.setFont(&Org_01);
  tft.setTextSize(1);


  //------ 1 PWM Brightness
#ifdef Encoder_PWM2
  tft.drawBitmap(20 + X_Offset, 24 + Y_Offset, PWM_BL_BMP, 36, 36, ILI9341_WHITE);

  // Show default TFT backlight brightness setting
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(31 + X_Offset, 78 + Y_Offset); tft.print(brightness_count);
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(30 + X_Offset, 68 + Y_Offset); tft.print("PWM");

#else
  //tft.drawBitmap(20 + X_Offset, 24 + Y_Offset, PWM_BL_BMP, 36, 36, ILI9341_GREY);
  //tft.setTextColor(ILI9341_GREY); tft.setCursor(30 + X_Offset, 68 + Y_Offset); tft.print("Off");

  // Fixed PWM PWM Brightness , Show default TFT backlight brightness setting
  tft.drawBitmap(20 + X_Offset, 24 + Y_Offset, PWM_BL_BMP, 36, 36, ILI9341_WHITE);
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(31 + X_Offset, 78 + Y_Offset); tft.print(brightness_count);
  tft.fillCircle(38 + X_Offset, 41 + Y_Offset,  11,         ILI9341_YELLOW);
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(24 + X_Offset, 68 + Y_Offset); tft.print("FIXED");
#endif
  delay(featureDelay);

  //------ 2A Tacho
#ifdef enableNeopixelGauges
  tft.drawBitmap(62 + X_Offset, 24 + Y_Offset, Neo_Gauges_BMP, 36, 36, ILI9341_WHITE);

  // Show default NeoPixel brightness setting
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(72 + X_Offset, 68 + Y_Offset); tft.print("NEO");
  //tft.setTextColor(ILI9341_WHITE); tft.setCursor(74 + X_Offset, 78 + Y_Offset); tft.print(NeoBrightness);

#else
  tft.drawBitmap(62 + X_Offset, 24 + Y_Offset, Neo_Gauges_BMP, 36, 36, ILI9341_GREY);

  tft.setTextColor(ILI9341_GREY); tft.setCursor(72 + X_Offset, 68 + Y_Offset); tft.print("Off");
#endif
  delay(featureDelay);

  //------ 2B Neo_BrightnessAuto
#ifdef Neo_BrightnessAuto

  tft.drawBitmap(62 + X_Offset, 24 + Y_Offset, Neo_Gauges_BMP, 36, 36, ILI9341_WHITE);
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(72 + X_Offset, 68 + Y_Offset); tft.print("NEO");
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(69 + X_Offset, 78 + Y_Offset); tft.print("AUTO");

#endif
  delay(featureDelay);



  //------ 3 Volume
#ifdef Encoder_HID
  tft.drawBitmap(104 + X_Offset, 24 + Y_Offset, Volume_BMP, 36, 36, ILI9341_WHITE);

  tft.setTextColor(ILI9341_WHITE); tft.setCursor(114 + X_Offset, 68 + Y_Offset); tft.print("Vol");
#else
  tft.drawBitmap(104 + X_Offset, 24 + Y_Offset, Volume_BMP, 36, 36, ILI9341_GREY);
  tft.setTextColor(ILI9341_GREY);  tft.setCursor(114 + X_Offset, 68 + Y_Offset); tft.print("Off");

#endif
  delay(featureDelay);


  //------ 4 InfraRed
#ifdef enableIR
  tft.drawBitmap(146 + X_Offset, 24 + Y_Offset, InfraRed_BMP, 36, 36, ILI9341_WHITE);
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(158 + X_Offset, 68 + Y_Offset); tft.print("IR");
#else
  tft.drawBitmap(146 + X_Offset, 24 + Y_Offset, InfraRed_BMP, 36, 36, ILI9341_GREY);
  tft.setTextColor(ILI9341_GREY);  tft.setCursor(156 + X_Offset, 68 + Y_Offset); tft.print("Off");
#endif
  delay(featureDelay);


  //------ 5 BT
#ifdef enable_BT // Reserved
  tft.drawBitmap(188 + X_Offset, 24 + Y_Offset, BT_BMP, 36, 36, ILI9341_BLUE);
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(200 + X_Offset, 68 + Y_Offset); tft.print("BT");

#else
  tft.drawBitmap(188 + X_Offset, 24 + Y_Offset, BT_BMP, 36, 36, ILI9341_GREY);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(192 + X_Offset, 47 + Y_Offset); tft.print("USB");
  tft.setTextSize(1);
  
  tft.setTextColor(ILI9341_GREY); tft.setCursor(198 + X_Offset, 68 + Y_Offset); tft.print("OFF");
#endif


  delay(featureDelay);
  tft.setFont(); // Set back to default Adafruit GRFX font
}
