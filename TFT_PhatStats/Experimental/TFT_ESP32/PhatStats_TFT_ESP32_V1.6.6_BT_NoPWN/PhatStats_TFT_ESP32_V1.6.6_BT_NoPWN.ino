#define CODE_VERS  "1.6.5.BT"  // Code version number
/*
  GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
  Rupert Hirst & Colin Conway © 2016 - 2018
  http://tallmanlabs.com
  http://runawaybrainz.blogspot.com/

  Licence
  --------
  GPL v2

  This Sketch Requires HardwareSerialMonitor v1.3 or higher
  UNO / NANO / MINI are not supported!!!

  Board Manager ESP32 Core
  -------------------
  Click on File > Preference, and fill Additional Boards Manager URLs with the url below:

  Use this link in the "Additional Boards Managers URLs" field:
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json


  Libraries
  ---------
  Adafruit Neopixel
  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit GFX Library
  https://github.com/adafruit/Adafruit-GFX-Library

  Adafruit ILI9341
  https://github.com/adafruit/Adafruit_ILI9341

  https://runawaybrainz.blogspot.com/2021/03/phat-stats-ili9341-tft-display-hook-up.html

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
               SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/


#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>   //https://github.com/adafruit/Adafruit-GFX-Library
#include <Fonts/Org_01.h>
#include "Configuration_Settings.h" // load settings
#include "bitmap.h"
#include "bitmap_large.h"
#include "Sumo_bitmap.h"

#include "BluetoothSerial.h" //https://www.electronicshub.org/esp32-bluetooth-tutorial/
BluetoothSerial SerialBT;

/*
  eBay Special Red PCB pinouots VCC(3.3v), GND, CS, RST, D/C, MOSI, SCK, BL, (MISO, T_CLK, T_CS, T_DIN, T_DO, T_IRQ)

  ESP32 Lolin32 v1 (Tested)
  -------------------------
  CS     =  17     (15)
  RST    =  19     (-1)
  DC     =  16     (2)

  SCLK   =  18
  MOSI   =  23

  MISO   =  19   (*Not Required for Reference only!!!)

  B.LIGHT =  4   (0, 13) Note: analogWrite() PWM is not supported in the ESP32 Core
  ---------------------

  Rotary Encoder
  Note: When uploading the sketch to the ESP32
  disconnect the Rotary Encoder. Or it may fail to upload
  ---------------------
  EncoderA = 2  (4)
  EncoderB = 15 (16)

  EncButton= 0  (17)
  ---------------------
  i2c
  ---------------------
  SCL = 22  (*Not Required for Reference only!!!)
  SDA = 21  (*Not Required for Reference only!!!)
  ---------------------

  Neopixel / LED's
  ---------------------
  Built in LED =  5
  Neopixel     =  32
  ==========================================================================================================
*/

#define RX_LEDPin 5

#include <Adafruit_NeoPixel.h>
#define NEOPIN     32
#define NUM_PIXELS 16


/* Pre-define Hex NeoPixel colours,  eg. pixels.setPixelColor(0, BLUE); https://htmlcolorcodes.com/color-names/ */
#define BLUE       0x0000FF
#define GREEN      0x008000
#define RED        0xFF0000
#define ORANGE     0xFFA500
#define DARKORANGE 0xFF8C00
#define YELLOW     0xFFFF00
#define WHITE      0xFFFFFF
#define BLACK      0x000000 // OFF

//Adafruit_NeoPixel_ZeroDMA pixels(NUM_PIXELS, NEOPIN, NEO_GRB);
Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

//---------------------------------------------------------------------------------------

/* ILI9321 TFT setup */
#include <Adafruit_ILI9341.h>  // v1.5.6 Adafruit Standard

/* ATSAMD21 SPi Hardware only for speed*/
#define TFT_CS     17
#define TFT_DC     16
#define TFT_RST    19 //-1 // connect to RESET/EN Pin 

/* These pins do not have to be defined as they are hardware pins */
//Connect TFT_SCLK to pin   18
//Connect TFT_MOSI to pin   23

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); // Use hardware SPI

//---------------------------------------------------------------------------------------

/* Rotary Encoder*/
#define encoderOutA 2  // CLK
#define encoderOutB 15 // DT

int PWM_Percent_Scale  = 100;    // start brightness Scale @ 100%
int State;     // old encoder
int old_State; // old encoder

/* Button pin*/
int enc_Button_counter = 0;
int encoder_Button = 0; //old encoder button pin

//---------------------------------------------------------------------------------------

/* Screen TFT backlight brightness */
//Note: analogWrite() PWM is not supported in the ESP32 Core
int TFT_backlight_PIN = 4;  //13;

/* Direct MCU connection start-up level. Predefined Brightness Start-UP Level,*/
//Note: analogWrite() PWM is not supported in the ESP32 Core
#ifdef Static_PWM
int TFT_brightness = 130; // 0 - 255
#endif

/* Do not adjust, it will affect the GUI % value */
#ifdef Encoder_PWM
int TFT_brightness = 100;
#endif

/* More Display stuff*/
int displayDraw = 0;
//int displayOverride = 0;

/* Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
boolean bootMode = true;

/* Vars for serial input*/
String inputString = "";
boolean stringComplete = false;

/* No longer used,Inverted timers for display
  long invertDelay = 60000; // move setting to config tab
  long lastInvertTime = 0;
  int  invertedStatus = 1;
*/
//-----------------------------   TFT Colours  ---------------------------------

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

//------------------------------------------------------------------------------------------------------------


void setup() {

  Serial.begin(9600); //  USB Serial Baud Rate
  
  //Serial.begin(115200);
  /* If no name is given, default 'ESP32' is applied */
  /* If you want to give your own name to ESP32 Bluetooth device, then */
  /* specify the name as an argument SerialBT.begin("myESP32Bluetooth"); */
  SerialBT.begin();
  
  inputString.reserve(200);

  /* On the ESP32 these have to be moved into the DisplayStyles
    serialEvent();     // Check for Serial Activity
    #ifdef  enableActivityChecker
    activityChecker(); // Turn off screen when no activity
    #endif
  */

  /* Set up the NeoPixel*/
  pixels.begin();    // This initializes the NeoPixel library.
  pixels.setBrightness(NeoBrightness); // Atmel Global Brightness (does not work for STM32!!!!)
  pixels.show(); // Turn off all Pixels

  /* Setup HID*/
  // Sends a clean report to the host. This is important on any Arduino type.
  // Consumer.begin();

  /* Set up PINs*/
  pinMode (encoderOutA, INPUT);//old encoder
  pinMode (encoderOutB, INPUT);//old encoder
  pinMode(encoder_Button, INPUT_PULLUP);
  pinMode(TFT_backlight_PIN, OUTPUT); // declare backlight pin to be an output:
  pinMode(RX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
  backlightOFF();

  /* TFT SETUP */

  delay(1000); // Give the micro time to initiate the SPi bus
  tft.begin(); //ILI9341

  /* Display screen rotation  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)*/
  int ASPECT = 0; //Do not adjust,

  tft.setRotation(ASPECT);// Rotate the display :  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

  /* stops text wrapping*/
  tft.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters

  /* Clear Screen*/
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);

  //backlightON(); //Moved to splashscreen so it gives the screen time to draw Splashscreen, before being seen
  splashScreen();
  //splashScreenSumo();
}

/* End of Set up */

void loop() {

  /*Serial Activity LED */
  digitalWrite(RX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)

  digitalWrite(TFT_backlight_PIN, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)

  /*Encoder Mode Button, moved to its own tab*/
  encoder_Modes();

#ifdef Encoder_PWM
  PWM_Encoder ();
#endif

}

/* END of Main Loop */

//-------------------------------------------  NeoPixels  -------------------------------------------------------------
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
//-------------------------------------------  Serial Events -------------------------------------------------------------

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/

/* BlueTooth */
void serialBT.Event() {

  while (Serial.available()) {
    //while (Serial.available() > 0) {
    // get the new byte:
    char inChar = (char)Serial.read();
    //Serial.print(inChar); // Debug Incoming Serial

    // add it to the inputString:
    inputString += inChar;
    // if the incoming character has '|' in it, set a flag so the main loop can do something about it:
    if (inChar == '|') {
      stringComplete = true;

      delay(Serial_eventDelay);   //delay screen event to stop screen data corruption

      /* Serial Activity LED */
      digitalWrite(RX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)

    }
  }
}

/* USB Serial */
void serialBT.Event() {
  while (SerialBT.available()) {

    char inChar = (char)SerialBT.read();
    //Serial.print(inChar); // Debug Incoming Serial

    // add it to the inputString:
    inputString += inChar;
    // if the incoming character has '|' in it, set a flag so the main loop can do something about it:
    if (inChar == '|') {
      stringComplete = true;

      delay(Serial_eventDelay);   //delay screen event to stop screen data corruption

      /* Serial Activity LED */
      digitalWrite(RX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)

    }
  }
}

//------------------------------------------- ActivityChecker  -----------------------------------------------------------
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


//-------------------------------------------  TFT Backlight  -------------------------------------------------------------

void backlightON () {
  //analogWrite(TFT_backlight_PIN, TFT_brightness); // TFT turn on backlight
  digitalWrite(TFT_backlight_PIN, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
}

void backlightOFF () {
  digitalWrite(TFT_backlight_PIN, LOW);    // turn the LED off HIGH(OFF) LOW (ON)
}

//--------------------------------------------- Splash Screens --------------------------------------------------------
void splashScreenSumo() {

  /* Initial Boot Screen, */
  allNeoPixelsOff();
  tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

  tft.setFont(&Org_01);

  tft.fillScreen(ILI9341_BLACK);

  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(25, 20, SUMO_BMP, 190, 160, ILI9341_BROWN);
  tft.drawBitmap(25, 20, SUMO_BMP2, 190, 160, ILI9341_YELLOW);

  tft.setTextSize(3);
  tft.setCursor(86, 190);
  tft.setTextColor(ILI9341_SILVER);
  tft.println("PHAT ");
  tft.setTextSize(3);
  tft.setCursor(78, 210);
  tft.println("STATS");

  tft.setTextSize(2);
  tft.setCursor(22, 230);
  tft.setTextColor(ILI9341_SILVER);
  tft.print("PC Hardware Monitor");

  tft.setTextSize(3);
  tft.setCursor(22, 260);
  tft.setTextColor(ILI9341_RED);
  tft.print("tallmanlabs.com");

  /* Set version */
  tft.setFont(); // Set Default Adafruit GRFX Font
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(140, 290);
  tft.print("TFT: v");
  tft.print (CODE_VERS);

  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(); // Set Default Adafruit GRFX Font
  tft.setTextSize(1);
  tft.setCursor(10, 305);
  tft.print("Use HardwareSerialMonitor v1.3 Upward");

  backlightON();

  delay(3000);

  allNeoPixelsRED();
  tft.fillScreen(ILI9341_BLACK);
  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(82, 80, WaitingDataBMP2_90, 76, 154, ILI9341_RED);

  delay(1000);
}

void splashScreen() {

  /* Initial Boot Screen, */
  allNeoPixelsOff();
  tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

  tft.setFont(&Org_01);
  tft.fillScreen(ILI9341_BLACK);

  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(84, 56, JustGnatBMP, 64, 64, ILI9341_YELLOW);

  tft.setTextSize(3);
  tft.setCursor(86, 140);
  tft.setTextColor(ILI9341_SILVER);
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
  tft.setCursor(150, 290);
  tft.print("TFT: v");
  tft.print (CODE_VERS);

  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(); // Set Default Adafruit GRFX Font
  tft.setTextSize(1);
  tft.setCursor(10, 305);
  tft.print("Use HardwareSerialMonitor v1.3 Upward");

  backlightON();

  delay(3000);

  allNeoPixelsRED();
  tft.fillScreen(ILI9341_BLACK);
  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(82, 80, WaitingDataBMP2_90, 76, 154, ILI9341_RED);

  delay(1000);
}

//-------------------------------------------- Anti Screen Burn inverter ------------------------------------------------

/*
  void inverter() {
  if ( invertedStatus == 1 ) {
    invertedStatus = 0;
  } else {
    invertedStatus = 1;
  }
  tft.invertDisplay(invertedStatus);
  }
*/
