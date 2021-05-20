 #define CODE_VERS  "2.0.4.6.BT"  // Code version number
#define device_BT "TallmanLabs_BT"


/*
  uVolume, GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
  Rupert Hirst & Colin Conway © 2016 - 2021
  http://tallmanlabs.com
  http://runawaybrainz.blogspot.com/

  Licence
  --------
  GPL v2

  This Sketch Requires HardwareSerialMonitor v1.3 or higher

  https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md

  Board Manager ESP32
  -------------------
  Click on File > Preference, and fill Additional Boards Manager URLs with the url below:
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json



  Libraries
  ---------
  Adafruit Neopixel
  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit GFX Library
  https://github.com/adafruit/Adafruit-GFX-Library

  Adafruit ILI9341
  https://github.com/adafruit/Adafruit_ILI9341

  Rotary encoder
  https://github.com/koogar/ErriezRotaryEncoderFullStep

  ESP32 analogueWrite Function
  https://github.com/ERROPiX/ESP32_AnalogWrite

  Hookup Guide
  https://runawaybrainz.blogspot.com/2021/03/phat-stats-ili9341-tft-display-hook-up.html

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
               SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Fonts/Org_01.h>
#include <analogWrite.h>
#include <TML_ErriezRotaryFullStep.h>

#include "Configuration_Settings.h" // load settings
#include "Bitmaps.h"

#include "BluetoothSerial.h" //https://www.electronicshub.org/esp32-bluetooth-tutorial/


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!
#endif

BluetoothSerial SerialBT;    // Bluetooth Classic, not BLE
/*
  eBay Special Red PCB pinouots VCC(3.3v), GND, CS, RST, D/C, MOSI, SCK, BL, (MISO, T_CLK, T_CS, T_DIN, T_DO, T_IRQ)

  Wemos ESP32 Lolin32 v1   (Compiles/Tested)
  Wemos ESP32 Lolin32 Lite (Compiles/Untested)
  Wemos ESP32 LoLin32 D32  (Compiles/Untested)
  --------------------------------------------
  CS     =  17             (15)
  RST    =  19             (-1)
  DC     =  16             (2)

  SCLK   =  18
  MOSI   =  23

  MISO   =  19   (*Not Required for Reference only!!!)

  B.LIGHT =  4             (0, 13)
  ---------------------

  Rotary Encoder
  ---------------------

  EncoderA = 14           (14,2,4)
  EncoderB = 27           (27,15,16)

  EncButton= 0            (0,17)
  ---------------------
  i2c
  ---------------------
  SCL = 22  (*Not Required for Reference only!!!)
  SDA = 21  (*Not Required for Reference only!!!)
  ---------------------

  Neopixel / LED's
  ---------------------
  Built in LED =  5 (*Not Required for Reference only!!!)
  Neopixel     =  2       (32)
  ==========================================================================================================
*/


//---------------------------------------------------------------------------------------
#include <Adafruit_NeoPixel.h>
#define NEOPIN      2
#define NUM_PIXELS  16
Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

/* Pre-define Hex NeoPixel colours,  eg. pixels.setPixelColor(0, BLUE); https://htmlcolorcodes.com/color-names/ */
#define BLUE       0x0000FF
#define GREEN      0x008000
#define RED        0xFF0000
#define ORANGE     0xFFA500
#define DARKORANGE 0xFF8C00
#define YELLOW     0xFFFF00
#define WHITE      0xFFFFFF
#define BLACK      0x000000 // OFF

/*onboard BUILD in LED for RX*/
#define TX_LEDPin 5

//----------------------------------------------------------------------------

/* ILI9321 TFT setup */
#include <Adafruit_ILI9341.h>  // v1.5.6 Adafruit Standard

/* ATSAMD21 SPi Hardware only for speed*/
#define TFT_CS     17
#define TFT_DC     16
#define TFT_RST    19

/* These pins do not have to be defined as they are hardware pins */
//Connect TFT_SCLK to pin   18
//Connect TFT_MOSI to pin   23

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); // Use hardware SPI

//-----------------------------------------------------------------------------

/* Rotary Encoder*/
#define encoderOutA 27 // CLK
#define encoderOutB 14 // DT

RotaryFullStep rotary(encoderOutA, encoderOutB);

/* Encoder Button pin*/
int encoder_Button     = 0;
int enc_Button_counter = 0;

/* Screen TFT backlight Pin */
int TFT_backlight_PIN = 4;


/* Encoder TFT Brightness*/ //Reserved!!! not supported on ESP32 Reserved
//volatile int brightness_count = 150; // Start Up PWM Brightness, moved to CFG!!!
int brightness_countLast      = 0;   // Store Last PWM Value

//-----------------------------------------------------------------------------

/* Display screen rotation  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)*/
int ASPECT = 3; //Do not adjust,

/* More Display stuff*/
int displayDraw = 0;

// SideGauges tft
int topLevel = 0;
int bottomLevel = 0;
//-----------------------------------------------------------------------------

/* Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
boolean bootMode = true;

/* Vars for serial input*/
String inputString = "";
boolean stringComplete = false;

//-----------------------------  TFT Colours  ---------------------------------

#define ILI9341_TEST        0x6A4E
#define ILI9341_BLACK       0x0000
#define ILI9341_WHITE       0xFFFF
#define ILI9341_GREY        0x7BEF
#define ILI9341_LIGHT_GREY  0xC618
#define ILI9341_GREEN       0x07E0
#define ILI9341_LIME        0x87E0
#define ILI9341_BLUE        0x001F
#define ILI9341_RED         0xF800
#define ILI9341_AQUA        0x5D1C
#define ILI9341_YELLOW      0xFFE0
#define ILI9341_MAGENTA     0xF81F
#define ILI9341_CYAN        0x07FF
#define ILI9341_DARK_CYAN   0x03EF
#define ILI9341_ORANGE      0xFCA0
#define ILI9341_PINK        0xF97F
#define ILI9341_BROWN       0x8200
#define ILI9341_VIOLET      0x9199
#define ILI9341_SILVER      0xA510
#define ILI9341_GOLD        0xA508
#define ILI9341_NAVY        0x000F
#define ILI9341_MAROON      0x7800
#define ILI9341_PURPLE      0x780F
#define ILI9341_OLIVE       0x7BE0
//--------------------------------

void setup() {

#ifdef enable_DualSerialEvent
  SerialBT.begin(device_BT); //Bluetooth device name
#endif


#ifdef enable_BT
  //btStart();
  SerialBT.begin(device_BT); //Bluetooth device name
#else //USB
  //btStop();      // Turn off BT Radio
  //SerialBT.end(); // Turn off BT Radio
  Serial.begin(baud);  //  USB Serial Baud Rate
#endif

  inputString.reserve(200); // String Buffer

#ifdef Encoder_PWM2
  // Initialize pin change interrupt on both rotary encoder pins
  attachInterrupt(digitalPinToInterrupt(encoderOutA), rotaryInterrupt_PWM2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderOutB), rotaryInterrupt_PWM2, CHANGE);
#endif

  /* Set up the NeoPixel*/
  pixels.begin();    // This initializes the NeoPixel library.
  pixels.setBrightness(NeoBrightness); // Atmel Global Brightness (does not work for STM32!!!!)
  pixels.show(); // Turn off all Pixels

  /* Set up PINs*/
  pinMode(encoder_Button, INPUT_PULLUP);

  // Set resolution for a specific pin
  analogWriteResolution(TFT_backlight_PIN, 12); //ESP32 only

#ifdef enableTX_LED
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif

  backlightOFF();

  /* TFT SETUP */

  delay(1000); // Give the micro time to initiate the SPi bus
  tft.begin(); //ILI9341
  tft.setRotation(ASPECT);// Rotate the display :  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

  /* stops text wrapping*/
  tft.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters

  /* Clear Screen*/
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  
  splashScreen_Circle();

}

/* End of Set up */

void loop() {


#ifdef Encoder_PWM2
  void rotaryInterrupt_PWM();
#endif

#ifdef enableTX_LED
  /*ESP Activity LED */
  digitalWrite(TX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
#endif
  //-----------------------------

  /*Encoder Mode Button, moved to its own tab*/
  encoder_Modes();

}

/* END of Main Loop */


//-----------------------------  NeoPixels RGB  -----------------------------------
void allNeoPixelsOff() {
  for ( int i = 0; i < NUM_PIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 0 );
  }
  pixels.show();
}

void allNeoPixelsRED() {
  for ( int i = 0; i < NUM_PIXELS; i++ ) {
    pixels.setPixelColor(i, 255, 0, 0 );
  }
  pixels.show();
}

void allNeoPixelsGREEN() {
  for ( int i = 0; i < NUM_PIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 255, 0 );
  }
  pixels.show();
}

void allNeoPixelsBLUE() {
  for ( int i = 0; i < NUM_PIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 255 );
  }
  pixels.show();
}
//-----------------------------  Serial Events -------------------------------
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/

/* BlueTooth */
void serialBTEvent() {
  while (SerialBT.available()) {

    char inChar = (char)SerialBT.read();
    //Serial.print(inChar); // Debug Incoming Serial

    // add it to the inputString:
    inputString += inChar;
    // if the incoming character has '|' in it, set a flag so the main loop can do something about it:
    if (inChar == '|') {
      stringComplete = true;

      delay(Serial_eventDelay);   //delay screen event to stop screen data corruption

#ifdef enableTX_LED
      /* Serial Activity LED */
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif

//tft.fillRoundRect(297, 0,   22, 102 , 11, ILI9341_BLACK); // top right corner LS

    }
  }
}


/* USB Serial*/
void serialEvent() {
  while (Serial.available()) {

    char inChar = (char)Serial.read();
    //Serial.print(inChar); // Debug Incoming Serial

    // add it to the inputString:
    inputString += inChar;
    // if the incoming character has '|' in it, set a flag so the main loop can do something about it:
    if (inChar == '|') {
      stringComplete = true;

      delay(Serial_eventDelay);   //delay screen event to stop screen data corruption

#ifdef enableTX_LED
      /* Serial Activity LED*/
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif

    }
  }
}


//----------------------------- ActivityChecker  -------------------------------
void activityChecker() {

  if (millis() - lastActiveConn > lastActiveDelay)

    activeConn = false;
  else
    activeConn = true;

  if (!activeConn) {

    /* Turn off display when there is no activity, */
    backlightOFF ();

    //if (invertedStatus)

    //Turn off NeoPixel when there is no activity
    allNeoPixelsOff();
    /* Set Default Adafruit GRFX Font*/
    tft.setFont();

    tft.fillScreen(ILI9341_BLACK);
    tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
    tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
    tft.setTextColor(ILI9341_RED);
    tft.drawBitmap(82, 80, WaitingDataBMP2_90, 76, 154, ILI9341_RED);
    tft.setTextSize(2); tft.setCursor(40, 40); tft.println("NO COM DATA!!!");
    delay(2000);

    //Turn off display when there is no activity
    //tft.invertDisplay(0);
    displayDraw = 0;

    /* Clear Screen & Turn Off Backlight, */
    tft.fillScreen(ILI9341_BLACK);
    backlightOFF ();
    displayDraw = 0;

  }

}

//----------------------------- TFT Backlight  -------------------------------

void backlightON () {
  analogWrite(TFT_backlight_PIN, brightness_count); // TFT turn on backlight

}

void backlightOFF () {
  analogWrite(TFT_backlight_PIN, 0);        // TFT turn off backlight,

}

//----------------------------- Splash Screens --------------------------------
void splashScreen_Circle() {

  /*ST7789 240x240 Portrait & Landscape offsets,*/
  //#define X_Offset  40 // - Portrait
  //#define Y_Offset  0  // + Portrait
  //tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)


  /*ILI9341 240x320 Portrait offsets(centre),*/
  //#define X_Offset  40 // - Portrait
  //#define Y_Offset  40 // + Portrait


  /*ILI9341 240x320 Portrait offsets(Middle of PCB 86mm),*/
  //#define X_Offset 40 // - Portrait
  //#define Y_Offset 63 // + Portrait

  /*ILI9341 240x320 Landscape offsets(centre),*/
  //#define X_Offset  0 // - Landscape
  //#define Y_Offset  0 // + Landscape
  /* Initial Boot Screen, */

  tft.setFont(&Org_01);
  tft.fillScreen(ILI9341_BLACK);

  backlightON ();
  tft.drawCircle(160 - 24, 120 + 0, 115, ILI9341_RED); // // flash circle surround

  //tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);

  tft.drawBitmap(44 + 18, 20 - 5 , HSM_BG_BMP,  142, 128 , ILI9341_WHITE);
  tft.drawBitmap(44 + 18, 20 - 5 , HSM_BG2_BMP, 142, 128 , ILI9341_RED);
  tft.drawBitmap(44 + 18, 20 - 5, HSM_BMP,     142, 128 , ILI9341_GREY);

  tft.setCursor(20 + 18, 20 - 5);
  tft.setTextColor(ILI9341_WHITE);

  tft.setTextSize(3);
  tft.setCursor(86 + 18, 140 - 5);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("PHAT ");
  tft.setTextSize(3);
  tft.setCursor(78 + 18, 160 - 5);
  tft.println("TACHO");

  tft.setTextSize(2);
  tft.setCursor(22 + 18, 190 - 18);
  tft.setTextColor(ILI9341_SILVER);
  tft.print("PC Hardware Monitor");

  tft.setTextSize(2);
  tft.setCursor(22 + 48, 219 - 25);
  tft.setTextColor(ILI9341_RED);
  tft.print("tallmanlabs.com");


  //Set version
  tft.setFont(); // Set Default Adafruit GRFX Font
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(95 , 230 - 18);
  tft.print("TFT: v");
  tft.print (CODE_VERS);
  delay(2000);

  /**/

  tft.fillScreen(ILI9341_BLACK);
  tft.drawCircle(160 - 24, 120 + 0, 115, ILI9341_RED); // // flash circle surround

  tft.setTextSize(1);

  tft.setCursor(10, 305);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("If using USB Serial? Disconnect BT!!!");

  //backlightON();

  FeatureSet_Indicator2_Circle (); // Display Icons for enabled features

  delay(4000);

  tft.fillScreen(ILI9341_BLACK);

#ifdef enable_BT
  tft.drawCircle(160 - 24, 120 + 0, 115, ILI9341_RED); // // flash circle surround
  tft.drawBitmap(82 + 17, 62 - 35, WaitingDataBMP_BT, 76, 190, ILI9341_BLUE);

#else // USB
  tft.drawCircle(160 - 24, 120 + 0, 115, ILI9341_RED); // // flash circle surround
  tft.drawBitmap(82 + 17 , 62 - 35, WaitingDataBMP_USB, 76, 190, ILI9341_RED);
#endif
  tft.drawCircle(160 - 24 , 120 + 0, 115, ILI9341_RED); // // flash circle surround
#ifdef enable_DualSerialEvent

  tft.drawBitmap(82 + 17 , 62 - 35, WaitingDataBMP_USB, 76, 190, ILI9341_BLUE);
#endif

  delay(3000);

}

void splashScreen() {

  /* Initial Boot Screen, */

  allNeoPixelsOff();
  tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

  tft.setFont(&Org_01);
  tft.fillScreen(ILI9341_BLACK);

  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);

  //tft.drawBitmap(84, 56, JustGnatBMP, 64, 64, ILI9341_YELLOW);

  tft.drawBitmap(44, 20, HSM_BG_BMP,  142, 128, ILI9341_WHITE);
  tft.drawBitmap(44, 20, HSM_BG2_BMP, 142, 128, ILI9341_RED);
  tft.drawBitmap(44, 20, HSM_BMP,     142, 128, ILI9341_GREY);

  tft.setCursor(20, 20);
  tft.setTextColor(ILI9341_WHITE);
  tft.print(baud);//tft.println(" bits/s");

  tft.setTextSize(3);
  tft.setCursor(86, 140);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("PHAT ");
  tft.setTextSize(3);
  tft.setCursor(78, 160);
  tft.println("STATS");

  tft.setTextSize(2);
  tft.setCursor(22, 190);
  tft.setTextColor(ILI9341_SILVER);
  tft.print("PC Hardware Monitor");

  tft.setTextSize(3);
  tft.setCursor(22, 219);
  tft.setTextColor(ILI9341_RED);
  tft.print("tallmanlabs.com");

  /* Set version */
  tft.setFont(); // Set Default Adafruit GRFX Font
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(130, 290);
  tft.print("TFT: v");
  tft.print (CODE_VERS);

  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(); // Set Default Adafruit GRFX Font

  tft.setTextSize(1);

  tft.setCursor(10, 305);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("If using USB Serial? Disconnect BT!!!");

  backlightON();

  FeatureSet_Indicator2_Circle(); // Display Icons for enabled features

  delay(4000);

#ifdef enableNeopixelGauges

#ifdef enable_BT
  allNeoPixelsBLUE();
#else
  allNeoPixelsRED();
#endif

#endif

  tft.fillScreen(ILI9341_BLACK);

#ifdef enable_BT
  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(82, 62, WaitingDataBMP_BT, 76, 190, ILI9341_BLUE);

#else // USB
  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(82, 62, WaitingDataBMP_USB, 76, 190, ILI9341_RED);
#endif

#ifdef enable_DualSerialEvent
  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(82, 62, WaitingDataBMP_USB, 76, 190, ILI9341_BLUE);
#endif

  delay(3000);

}
