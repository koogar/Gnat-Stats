
void FeatureSet_Indicator () {

  // Feature Indicator Test
  //#define WIFI // Reserved
  //#define BT   // Reserved

#define X_Offset 0
#define Y_Offset 230

#define radius      15 // Indicator Draw Circle Radius
#define radius_fill 14 // Indicator Fill Circle Radius

  int featureDelay = 200;
  delay(featureDelay);

  tft.setFont(&Org_01);
  tft.setTextSize(1);

  //------ 1 PWM Brightness
#ifdef Encoder_PWM2
  //                   (X,   Y,   W,   H,  R,    Colour);
  //tft.drawRoundRect  (2,   6,  36,  36,  3,    ILI9341_WHITE);
  tft.drawCircle       (20 + X_Offset, 24 + Y_Offset,  radius_fill,    ILI9341_WHITE);
  tft.drawCircle       (20 + X_Offset, 24 + Y_Offset,  radius,         ILI9341_WHITE);
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(12 + X_Offset, 26 + Y_Offset); tft.print("PWM");
#else
  //                   (X,   Y,   W,   H,  R,    Colour);
  //tft.drawRoundRect  (2 + X_Offset,   6 + Y_Offset,  36,  36,  3,    ILI9341_GREY);
  tft.drawCircle       (20 + X_Offset, 24 + Y_Offset,  radius_fill,    ILI9341_GREY);
  tft.drawCircle       (20 + X_Offset, 24 + Y_Offset,  radius,         ILI9341_GREY);
  tft.setTextColor(ILI9341_GREY); tft.setCursor(12 + X_Offset, 26 + Y_Offset); tft.print("PWM");
#endif
  delay(featureDelay);

  //------ 2 Tacho

#ifdef enableNeopixelGauges
  //                   (X,   Y,   W,   H,  R,    Colour);
  //tft.drawRoundRect  (42 + X_Offset,  6 + Y_Offset,  36,  36,  3,    ILI9341_WHITE);
  tft.drawCircle       (60 + X_Offset, 24 + Y_Offset,  radius_fill,    ILI9341_WHITE);
  tft.drawCircle       (60 + X_Offset, 24 + Y_Offset,  radius,         ILI9341_WHITE);
  tft.setTextColor(ILI9341_CYAN); tft.setCursor(49 + X_Offset, 26 + Y_Offset); tft.print("TACH");
#else
  //                   (X,   Y,   W,   H,  R,    Colour);
  //tft.drawRoundRect  (42 + X_Offset,  6 + Y_Offset,  36,  36,  3,    ILI9341_GREY);
  tft.drawCircle       (60 + X_Offset, 24 + Y_Offset,  radius_fill,    ILI9341_GREY);
  tft.drawCircle       (60 + X_Offset, 24 + Y_Offset,  radius,         ILI9341_GREY);
  tft.setTextColor(ILI9341_GREY); tft.setCursor(49 + X_Offset, 26 + Y_Offset); tft.print("TACH");
#endif
  delay(featureDelay);

  //------ 3 Volume
#ifdef Encoder_HID
  //                   (X,   Y,   W,   H,  R,    Colour);
  //tft.drawRoundRect  (82 + X_Offset,  6 + Y_Offset,  36,  36,  3,    ILI9341_WHITE);
  tft.drawCircle       (100 + X_Offset, 24 + Y_Offset,  radius_fill,   ILI9341_WHITE);
  tft.drawCircle       (100 + X_Offset, 24 + Y_Offset,  radius,        ILI9341_WHITE);
  tft.setTextColor(ILI9341_ORANGE); tft.setCursor(92 + X_Offset, 26 + Y_Offset); tft.print("VOL");
#else
  //                   (X,   Y,   W,   H,  R,    Colour);
  //tft.drawRoundRect  (82 + X_Offset,  6 + Y_Offset,  36,  36,  3,    ILI9341_GREY);
  tft.drawCircle       (100 + X_Offset, 24 + Y_Offset,  radius_fill,   ILI9341_GREY);
  tft.drawCircle       (100 + X_Offset, 24 + Y_Offset,  radius,        ILI9341_GREY);
  tft.setTextColor(ILI9341_GREY); tft.setCursor(92 + X_Offset, 26 + Y_Offset); tft.print("VOL");
#endif
  delay(featureDelay);


  //------ 4 InfraRed
#ifdef enableIR
  //                   (X,   Y,   W,   H,  R,    Colour);
  //tft.drawRoundRect  (122 + X_Offset, 6 + Y_Offset,  36,  36,  3,   ILI9341_WHITE);
  tft.drawCircle       (140 + X_Offset, 24 + Y_Offset,  radius_fill,  ILI9341_WHITE);
  tft.drawCircle       (140 + X_Offset, 24 + Y_Offset,  radius,       ILI9341_WHITE);
  tft.setTextColor(ILI9341_RED); tft.setCursor(135 + X_Offset, 26 + Y_Offset); tft.print("IR");
#else
  //                   (X,   Y,   W,   H,  R,    Colour);
  //tft.drawRoundRect  (122+ X_Offset, 6 + Y_Offset,  36,  36,  3,    ILI9341_GREY);
  tft.drawCircle       (140 + X_Offset, 24 + Y_Offset,  radius_fill,  ILI9341_GREY);
  tft.drawCircle       (140 + X_Offset, 24 + Y_Offset, radius,        ILI9341_GREY);
  tft.setTextColor(ILI9341_GREY); tft.setCursor(135 + X_Offset, 26 + Y_Offset); tft.print("IR");
#endif
  delay(featureDelay);

  //------ 5 BT
#ifdef BT // Reserved
  //                   (X,    Y,   W,   H,  R,    Colour);
  //tft.drawRoundRect  (162 + X_Offset,  6 + Y_Offset,  36,  36,  3,  ILI9341_WHITE);
  tft.drawCircle       (180 + X_Offset, 24 + Y_Offset,  radius_fill,  ILI9341_WHITE);
  tft.drawCircle       (180 + X_Offset, 24 + Y_Offset,  radius,       ILI9341_WHITE);
  tft.setTextColor(ILI9341_BLUE); tft.setCursor(175 + X_Offset, 26 + Y_Offset); tft.print("BT");
#else
  //                   (X,    Y,   W,   H,  R,    Colour);
  //tft.drawRoundRect  (162 + X_Offset,  6 + Y_Offset,  36,  36,  3,  ILI9341_GREY);
  tft.drawCircle       (180 + X_Offset, 24 + Y_Offset,  radius_fill,  ILI9341_GREY);
  tft.drawCircle       (180 + X_Offset, 24 + Y_Offset,  radius,       ILI9341_GREY);
  tft.setTextColor(ILI9341_GREY); tft.setCursor(175 + X_Offset, 26 + Y_Offset); tft.print("BT");
#endif
  delay(featureDelay);


  //------ 6 WiFi
#ifdef WIFI // Reserved
  //                   (X,    Y,   W,   H,  R,    Colour);
  //tft.drawRoundRect  (202 + X_Offset,  6 + Y_Offset,  36,  36,  3,  ILI9341_WHITE);
  tft.drawCircle       (220 + X_Offset, 24 + Y_Offset,  radius_fill,  ILI9341_WHITE);
  tft.drawCircle       (220 + X_Offset, 24 + Y_Offset,  radius,       ILI9341_WHITE);
  tft.setTextColor(ILI9341_GREEN); tft.setCursor(213 + X_Offset, 26 + Y_Offset); tft.print("WiFi");
#else
  //                   (X,    Y,   W,   H,  R,    Colour);
  //tft.drawRoundRect  (202 + X_Offset,  6 + Y_Offset,  36,  36,  3,  ILI9341_GREY);
  tft.drawCircle       (220 + X_Offset, 24 + Y_Offset,  radius_fill,  ILI9341_GREY);
  tft.drawCircle       (220 + X_Offset, 24 + Y_Offset,  radius,       ILI9341_GREY);
  tft.setTextColor(ILI9341_GREY); tft.setCursor(213 + X_Offset, 26 + Y_Offset); tft.print("WiFi");
#endif

  delay(featureDelay);
  tft.setFont(); // Set Default Adafruit GRFX Font
}
