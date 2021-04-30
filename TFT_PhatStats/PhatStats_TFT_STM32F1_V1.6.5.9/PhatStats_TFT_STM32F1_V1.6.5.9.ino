#define CODE_VERS  "V1.6.5.9"  // Code version number

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

  Board Core
  ------------
  Link Below for the STM32 Bootloader and Arduino Core
  (you may have to install the Arduino Due core also for the compiler.)

  https://github.com/rogerclarkmelbourne/Arduino_STM32/wiki/Installation

  https://github.com/rogerclarkmelbourne/Arduino_STM32

  Bootloader:
  https://github.com/rogerclarkmelbourne/STM32duino-bootloader/tree/master/binaries

  BluePill_generic_boot20_pc13.bin  (On the "Bluepill" bootloader "_pc13" refers to the LED pin. )

  Important Upload Note:
  ----------------------- 
  
  If your "upload method" is STLink you will loose the ability to upload using the "STMduino Bootloader".
  To use the STMduino Bootloader again, you will need to reflash the bootloader using a UART adaptor. 


  USB Issues:
  https://www.onetransistor.eu/2017/11/stm32-bluepill-arduino-ide.html

  Libraries
  ---------
  Adafruit Neopixel:
  Not Supported On STM32

  Adafruit GFX Library:
  NOTE: Adafruit_GFX Version 1.8.0 and higher doesn't compile for ESP8266 & STM32 Boards -
  Downgrade to Adafruit_GFX Version 1.7.5 in the library manager.Libraries

  https://github.com/adafruit/Adafruit-GFX-Library

  Adafruit ILI9341
  https://github.com/adafruit/Adafruit_ILI9341

  https://runawaybrainz.blogspot.com/2021/03/phat-stats-ili9341-tft-display-hook-up.html

  Cagan Celik's great guide to installing Phat-Stats on the STM32 BluePill
  https://www.technopat.net/2021/04/04/harici-sicaklik-gostergesi-yapimi/

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
               SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/


#include <Wire.h>
#include <SPI.h>

/*Adafruit_GFX Version 1.8.0 and higher doesn't compile for ESP8266 & STM32 Boards
  Downgrade to Adafruit_GFX Version 1.7.5 in the library manager.*/

#include <Adafruit_GFX.h>
#include <Fonts/Org_01.h>
#include "Configuration_Settings.h" // load settings
#include "bitmap.h"

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
  EncoderA = PB8
  EncoderB = PB9

  Button   = PB5
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
#define encoderOutA PB8 // CLK
#define encoderOutB PB9 // DT

int State;
int old_State;
int PWM_Percent_Scale  = 100;    // start brightness Scale @ 100%

/* Button pin*/
int encoder_Button = PB5;  //old encoder button pin
int enc_Button_counter = 0;  //old encoder button counter
//---------------------------------------------------------------------------------------

/* Screen TFT backlight brightness */
int TFT_backlight_PIN = PB0;

/* Direct MCU connection start-up level. Predefined Brightness Start-UP Level,*/
#ifdef Static_PWM
int TFT_brightness = 130; // 0 - 255
#endif

/* Do not adjust, it will affect the GUI % value */
#ifdef Encoder_PWM
int TFT_brightness = 100;
#endif


/* Display screen rotation  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)*/
int ASPECT = 0; //Do not adjust,

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

  Serial.begin(baud); //  USB Serial Baud Rate
  inputString.reserve(200);


  /* Set up PINS*/
  pinMode (encoderOutA, INPUT);
  pinMode (encoderOutB, INPUT);
  pinMode(encoder_Button, INPUT_PULLUP);
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


}

/* End of Set up */



void loop() {

  serialEvent();     // Check for Serial Activity

#ifdef  enableActivityChecker
  activityChecker(); // Turn off screen when no activity
#endif

  /* STM32 Serial Activity LED */
  digitalWrite(RX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)

  /*Encoder Mode Button, moved to its own tab*/
  encoder_Modes();

#ifdef Encoder_PWM
  PWM_Encoder ();
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


void splashScreen() {

  /* Initial Boot Screen, */
  

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
  tft.print("Use HardwareSerialMonitor v1.3 Upward");

  backlightON();

  FeatureSet_Indicator2(); // Display Icons for enabled features

  
  delay(4000);

  tft.fillScreen(ILI9341_BLACK);
  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  //tft.drawBitmap(82, 80, WaitingDataBMP2_90, 76, 154, ILI9341_RED);
  tft.drawBitmap(82, 62, WaitingDataBMP_USB, 76, 190, ILI9341_RED);


  delay(1000);

}
