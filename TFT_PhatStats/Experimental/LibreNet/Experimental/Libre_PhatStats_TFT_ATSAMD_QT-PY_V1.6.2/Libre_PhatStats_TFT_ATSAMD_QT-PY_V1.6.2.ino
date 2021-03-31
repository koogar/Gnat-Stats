/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
#define CODE_VERS  "1.6.2net"  // Code version number
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

/*
  GNAT-STATS & PHAT-STATS PC Performance Monitor - Version 1.x  Rupert Hirst & Colin Conway © 2016
  http://tallmanlabs.com  & http://runawaybrainz.blogspot.com/
  This Sketch Requires HardwareSerialMonitor v1.3 or higher
  UNO/NANO/MINI are not supported!!! use this sketch with STM32/ESP8622/ATSAMD21 based boards , due to larger memory.
  https://learn.adafruit.com/adafruit-feather-m0-express-designed-for-circuit-python-circuitpython/adafruit2-pinouts
  Board Manager
  -------------
  Install Arduino ATSAMD then ADD
  https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
  Search: Adafruit SAMD Boards

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

/*
  eBay Special Red PCB pinouots VCC(3.3v), GND, CS, RST, D/C, MOSI, SCK, BL, (MISO, T_CLK, T_CS, T_DIN, T_DO, T_IRQ)

  Adafruit QT-PY
  ---------------------
  ATSAMD21G18 @ 48MHz with 3.3V logic/power
  256KB of FLASH + 32KB of RAM
  ---------------------
  (TFT)
  CS     =  6    (GND,1,2,3,4,5,6,7)  (or to GND to save a pin)
  RST    =  9    (0  ,1,2,3,4,5,6,7,9(MI))
  DC     =  7    (0  ,1,2,3,4,5,6,7,9(MI))
  SCLK   =  8
  MOSI   =  10
  MISO   =  9   (*Not Required for Reference only!!!)

  B.LIGHT =  5
  ---------------------

  Rotary Encoder
  ---------------------
  EncoderA = 4
  EncoderB = 3
  EncButton= 2

  ---------------------
  i2c
  ---------------------
  SCL = 5  (*Not Required for Reference only!!!)
  SDA = 4  (*Not Required for Reference only!!!)
  ---------------------

  Neopixel / LED's
  ---------------------
  Built in LED     =  None on the QT-PY
  NeoPixel         =  1     (1,2,3,4,5,6)
  Built in Neopixel = 11 or (12 to turn it off)
  ==========================================================================================================
*/

#include <Adafruit_NeoPixel.h>
#define NEOPIN      1
#define NUM_PIXELS 16

/*onboard QT-PY NeoPixel for RX*/
#ifdef enableQTPYneopixel
#define RX_NeoPin 11  //Built in NeoPixel, on the QT-PY
#else
#define RX_NeoPin 12  // Disable QT-PY built in Neopixel if you have a XIAO
#endif

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
Adafruit_NeoPixel RX_pixel(1, RX_NeoPin, NEO_GRB + NEO_KHZ800);
//---------------------------------------------------------------------------------------

/* ILI9321 TFT setup */
#include <Adafruit_ILI9341.h>  // v1.5.6 Adafruit Standard

/* ATSAMD21 SPi Hardware only for speed*/
#define TFT_CS     6
#define TFT_DC     7
#define TFT_RST    9

/* These pins do not have to be defined as they are hardware pins */
//Connect TFT_SCLK to pin   8
//Connect TFT_MOSI to pin   10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); // Use hardware SPI

//---------------------------------------------------------------------------------------

/* Rotary Encoder*/
#define encoderOutA 4 // CLK
#define encoderOutB 3 // DT

int State;
int old_State;
int PWM_Percent_Scale  = 100;    // start brightness Scale @ 100%

/* Button pin*/
int counter = 0;
int switchPin = 2; //0
//---------------------------------------------------------------------------------------

/* Screen TFT backlight brightness */
int TFT_backlight_PIN = 5;
/* More Display stuff*/
int displayDraw = 0;
int displayOverride = 0;

/* Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
boolean bootMode = true;

/* Vars for serial input*/
String inputString = "";
boolean stringComplete = false;

/* No longer used,Inverted timers for display*/
//long invertDelay = 60000; // move setting to config tab
long lastInvertTime = 0;
int  invertedStatus = 1;

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
  inputString.reserve(200);

  /* Set up the NeoPixel*/
  pixels.begin();    // This initializes the NeoPixel library.
  RX_pixel.begin();  // This initializes the NeoPixel library.
  pixels.setBrightness(NeoBrightness); // Atmel Global Brightness (does not work for STM32!!!!)
  pixels.show(); // Turn off all Pixels

  /* Setup HID*/
  // Sends a clean report to the host. This is important on any Arduino type.
  // Consumer.begin();

  /* Set up PINs*/
  pinMode (encoderOutA, INPUT);
  pinMode (encoderOutB, INPUT);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(TFT_backlight_PIN, OUTPUT); // declare backlight pin to be an output:
  //pinMode(RX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
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

  //backlightON(); //Moved to splashscreen so it gives the screen time to draw Splashscreen, before being seen
  splashScreen();
  //splashScreenSumo();
}

/* End of Set up */

void loop() {

  /*Serial Activity LED */
  //digitalWrite(RX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
  /* Serial Activity NeoPixel */
  RX_pixel.setPixelColor(0, 0, 0, 0 ); // turn built in NeoPixel Off
  RX_pixel.show();


  /*Encoder Mode Button*/
  int switchVal = digitalRead(switchPin);
  if (switchVal == LOW)

  {
    //Consumer.write(MEDIA_VOLUME_MUTE);
    delay(debounceEncButton); // Debounce Button
    counter ++;

    /* Clear Screen*/
    tft.fillScreen(ILI9341_BLACK);

    /* Reset count if over max mode number, */
    if (counter == 4) // Number of screens available when button pressed
    {
      counter = 0;
    }
  }

  else

    /* Change Mode */
    switch (counter) {


      case 0: // 1st SCREEN
        //tft.setTextSize(3); tft.setCursor(0, 0); tft.println("SCREEN 1 C0");
        //DisplayStyle_Portrait_NoBlink();
        DisplayStyle_Portrait_LibreNet ();

        break;

      case 1: // 2nd SCREEN
        //tft.setTextSize(3); tft.setCursor(0, 0); tft.println("SCREEN 2 C1");
        //DisplayStyle_LibreNetKey();
        //DisplayStyle_LibreNet();
        //DisplayStyle_Landscape_NoBlink ();
        DisplayStyle_LibreNet_Landscape ();
        break;

      case 2: // 3rd SCREEN
        //tft.setTextSize(3); tft.setCursor(0, 0); tft.println("SCREEN 3 C2");
        DisplayStyle_Portrait_NoBlink();

        break;

      case 3: // 4th SCREEN
        //tft.setTextSize(3); tft.setCursor(0, 0); tft.println("SCREEN 4 C3");
        DisplayStyle_Landscape_NoBlink();

        break;

    }

#ifdef Encoder_PWM
  PWM_Encoder ();
#endif

#ifdef Encoder_PWM_PNP
  PWM_Encoder_PNP ();
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
void serialEvent() {
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
      //digitalWrite(RX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
      /* Serial Activity NeoPixel */
      RX_pixel.setPixelColor(0, 10, 0, 0 ); // turn built in NeoPixel on
      RX_pixel.show();

    }
  }
}

String getValue(String key)
{
  String searchKey =  key + ':';
  int keyIndex = inputString.indexOf(searchKey);
  if (keyIndex > -1)
  {
    int valIndex = inputString.indexOf("#", keyIndex);
    return inputString.substring(keyIndex + searchKey.length(), valIndex);
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

    if (invertedStatus)

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
    tft.invertDisplay(0);
    displayDraw = 0;

    /* Clear Screen & Turn Off Backlight, */
    tft.fillScreen(ILI9341_BLACK);
    backlightOFF ();
    displayDraw = 0;
  }
}


//-------------------------------------------  TFT Backlight  -------------------------------------------------------------

void backlightON () {
  analogWrite(TFT_backlight_PIN, TFT_brightness); // TFT turn on backlight
}

void backlightOFF () {

#ifdef Encoder_PWM_PNP
  analogWrite(TFT_backlight_PIN, 255);       // TFT turn off backlight  PWM 3906 Transitor 5v ,
#else
  analogWrite(TFT_backlight_PIN, 0);        // TFT turn off backlight fixed / no transistor 3.3v PWM ,
  //digitalWrite(TFT_backlight_PIN, LOW);       // turn the Backlight LOW to stop PWM idle flicker on ATSAMD

#endif

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


void inverter() {
  if ( invertedStatus == 1 ) {
    invertedStatus = 0;
  } else {
    invertedStatus = 1;
  };
  tft.invertDisplay(invertedStatus);
}
