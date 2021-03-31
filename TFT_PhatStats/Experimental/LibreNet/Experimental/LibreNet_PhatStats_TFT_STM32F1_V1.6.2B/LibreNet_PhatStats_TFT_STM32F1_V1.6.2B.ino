
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#define CODE_VERS  "1.6.2B"  // Code version number

/*
  GNAT-STATS & PHAT-STATS PC Performance Monitor - Version 1.x  Rupert Hirst & Colin Conway © 2016
  http://tallmanlabs.com  & http://runawaybrainz.blogspot.com/

  This Sketch Requires HardwareSerialMonitor v1.3 or higher

  UNO/NANO/MINI are not supported!!! use this sketch with STM32/ESP8622/ATSAMD21 based boards , due to larger memory.

  Link Below for the STM32 Bootloader and Arduino Core (you may have to install the Arduino Due core also for the compiler.)

  https://github.com/rogerclarkmelbourne/Arduino_STM32

  https://github.com/rogerclarkmelbourne/STM32duino-bootloader/tree/master/binaries

  BluePill_generic_boot20_pc13.bin  (On the "Bluepill" bootloader "_pc13" refers to the LED pin. )

  https://github.com/rogerclarkmelbourne/Arduino_STM32/wiki/Installation

  USB Issues:
  https://www.onetransistor.eu/2017/11/stm32-bluepill-arduino-ide.html

  Adafruit_GFX Version 1.8.0 and higher doesn't compile for ESP8266 & STM32 Boards -
  Downgrade to Adafruit_GFX Version 1.7.5 in the library manager.

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
               SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
               SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
               SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

*/
#include <Wire.h>
#include <SPI.h>

/*Adafruit_GFX Version 1.8.0 and higher doesn't compile for ESP8266 & STM32 Boards (STM32Duino.com) -
  Downgrade to Adafruit_GFX Version 1.7.5 in the library manager.*/
#include <Adafruit_GFX.h> // V1.4.7 / v1.7.0 / v1.7.5 Work  https://github.com/adafruit/Adafruit-GFX-Library
#include <Fonts/Org_01.h>

#include "Configuration_Settings.h" // load settings
#include "bitmap.h"
#include "bitmap_STM32.h"
#include "Sumo_Bitmap.h"

/*
  eBay Special Red PCB pinouots VCC(3.3v), GND, CS, RST, D/C, MOSI, SCK, BL, (MISO, T_CLK, T_CS, T_DIN, T_DO, T_IRQ)

  ILI9341 320x240 PINOUT
  --------------
  (TFT)
  CS     = PB11
  RST    = PB10
  DC     = PB1
  SCLK   = PA5
  MOSI   = PA7
  BLIGHT = PB0

  Rotary Encoder
  ---------------
  EncoderA = PA3
  EncoderB = PA2

  Button   = PA4
  ---------------
  /*

  /* ILI9321 TFT setup */
#include <Adafruit_ILI9341.h>  // v1.5.6 Adafruit Standard

/* STM32 SPi Hardware only for speed // STM32 SPi= CS:PB11 RST:PB10 DC:PB1 SCLK:PA5 MOSI:PA7*/
#define TFT_CS     PB11
#define TFT_DC     PB1
#define TFT_RST    PB10 // you can also connect this to the STM32 reset leave it undefined

/* These pins do not have to be defined as they are hardware pins */
//Connect TFT_SCLK to pin   PA5
//Connect TFT_MOSI to pin   PA7

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); // Use hardware SPI

//---------------------------------------------------------------------------------------

/* Standard onboard LED for RX*/
#define RX_LEDPin PC13

/* Rotary Encoder*/
#define encoderOutA PA3 //PB8 // CLK
#define encoderOutB PA2 //PB9 // DT

int State;
int old_State;
int PWM_Percent_Scale  = 100;    // start brightness Scale @ 100%

/* Button pin*/
int counter = 0;
int switchPin = PA4; //PA1;//PB5;
//---------------------------------------------------------------------------------------

/* Screen TFT backlight brightness */
int TFT_backlight_PIN = PB0;

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

  Serial.begin(9600); // 32u4 USB Serial Baud Rate
  inputString.reserve(200);


  /* Set up PINS*/
  pinMode (encoderOutA, INPUT);
  pinMode (encoderOutB, INPUT);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(TFT_backlight_PIN, OUTPUT); // declare backlight pin to be an output:
  pinMode(RX_LEDPin, OUTPUT); // STM32 BluePill Builtin LED /  HIGH(OFF) LOW (ON)
  backlightOFF();

  /* TFT SETUP */

  //delay(2000); // Give the micro time to initiate the SPi bus
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


  /* STM32 Serial Activity LED */
  digitalWrite(RX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)

  /*Encoder Mode Button*/
  int switchVal = digitalRead(switchPin);
  if (switchVal == LOW)
  {
    delay(debounceEncButton); // Debounce Button
    counter ++;

    /* Clear Screen*/
    tft.fillScreen(ILI9341_BLACK);

    /* Reset count if over max mode number, */
    if (counter == 2) // Number of screens available when button pressed
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
        //DisplayStyle_Portrait_LibreNet();
        DisplayStyle_LibreNet_Landscape ();
        break;

      case 1: // 2nd SCREEN
        //tft.setTextSize(3); tft.setCursor(0, 0); tft.println("SCREEN 2 C1");
        //DisplayStyle_Landscape_NoBlink ();
        //DisplayStyle_LibreNet ();
        DisplayStyle_Portrait_LibreNet();
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

//-------------------------------------------  Serial Events -------------------------------------------------------------
void serialEvent() {
  while (Serial.available()) {
    //Serial.flush(); // flush serial to stop screen garbage on esp8266, clears the serial data stream and kind of refresh it and also makes you ready to send next data.

    // get the new byte:
    char inChar = (char)Serial.read();
    //Serial.print(inChar); // Debug Incoming Serial

    // add it to the inputString:
    inputString += inChar;
    // if the incoming character has '|' in it, set a flag so the main loop can do something about it:
    if (inChar == '|') {
      stringComplete = true;

      delay(Serial_eventDelay);   //delay screen event to stop screen data corruption

      /* STM32 Serial Activity LED */
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

    if (invertedStatus)

      /* Set Default Adafruit GRFX Font*/
      tft.setFont();

    tft.fillScreen(ILI9341_BLACK);
    tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
    tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
    tft.setTextColor(ILI9341_RED);
    tft.drawBitmap(82, 80, WaitingDataBMP2_90, 76, 154, ILI9341_RED);
    tft.setTextSize(2); tft.setCursor(40, 40); tft.println("NO COM DATA!!!");
    delay(2000);

    displayDraw = 0;

    /* Clear Screen & Turn Off Backlight, */
    tft.fillScreen(ILI9341_BLACK);
    backlightOFF ();

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
#endif

}

//--------------------------------------------- Splash Screens --------------------------------------------------------
void splashScreenSumo() {

  /* Initial Boot Screen, */

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


  tft.fillScreen(ILI9341_BLACK);
  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(82, 80, WaitingDataBMP2_90, 76, 154, ILI9341_RED);

  delay(1000);

}


void splashScreen() {

  /* Initial Boot Screen, */
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

  tft.fillScreen(ILI9341_BLACK);
  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(82, 80, WaitingDataBMP2_90, 76, 154, ILI9341_RED);

  delay(1000);

}
