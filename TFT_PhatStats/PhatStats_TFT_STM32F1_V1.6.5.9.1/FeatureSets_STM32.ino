

void FeatureSet_Indicator2 () {

// Feature Indicator Test

#define X_Offset 0
#define Y_Offset 210

  int featureDelay = 200;
  delay(featureDelay);

  tft.setFont(&Org_01);
  tft.setTextSize(1);


  //------ 1 PWM Brightness
#ifdef Encoder_PWM
  tft.drawBitmap(20 + X_Offset, 24 + Y_Offset, PWM_BL_BMP, 36, 36, ILI9341_YELLOW);

  // Show default TFT backlight brightness setting
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(31 + X_Offset, 78 + Y_Offset); tft.print(TFT_brightness);
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(30 + X_Offset, 68 + Y_Offset); tft.print("PWM");

#else
  tft.drawBitmap(20 + X_Offset, 24 + Y_Offset, PWM_BL_BMP, 36, 36, ILI9341_GREY);
  tft.setTextColor(ILI9341_GREY); tft.setCursor(30 + X_Offset, 68 + Y_Offset); tft.print("Off");
#endif
  delay(featureDelay);

#ifdef Static_PWM
  tft.drawBitmap(62 + X_Offset, 24 + Y_Offset, PWM_BL_BMP, 36, 36, ILI9341_WHITE);

  // Show default TFT backlight brightness setting
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(74 + X_Offset, 78 + Y_Offset); tft.print(TFT_brightness);
  tft.fillCircle(80 + X_Offset, 42 + Y_Offset,  11,         ILI9341_YELLOW);
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(66 + X_Offset, 68 + Y_Offset); tft.print("FIXED");

#else
  tft.drawBitmap(62 + X_Offset, 24 + Y_Offset, PWM_BL_BMP, 36, 36, ILI9341_GREY);
  tft.fillCircle(80 + X_Offset, 42 + Y_Offset,  11,         ILI9341_GREY);
  tft.setTextColor(ILI9341_GREY); tft.setCursor(72 + X_Offset, 68 + Y_Offset); tft.print("Off");
#endif

  delay(featureDelay);
  tft.setFont(); // Set Default Adafruit GRFX Font
}
