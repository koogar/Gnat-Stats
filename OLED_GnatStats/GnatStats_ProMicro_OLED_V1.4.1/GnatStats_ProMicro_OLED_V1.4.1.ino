/*
   _____ __  __ _         _            ___           _   ___ _        _
  |_   _|  \/  | |   __ _| |__ ______ / __|_ _  __ _| |_/ __| |_ __ _| |_ ___
    | | | |\/| | |__/ _` | '_ (_-<___| (_ | ' \/ _` |  _\__ \  _/ _` |  _(_-<
    |_| |_|  |_|____\__,_|_.__/__/    \___|_||_\__,_|\__|___/\__\__,_|\__/__/

   GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
   Rupert Hirst & Colin Conway © 2016-2018

   http://tallmanlabs.com
   http://runawaybrainz.blogspot.com/
   https://hackaday.io/project/19018-gnat-stats-tiny-oled-pc-performance-monitor

   Licence
   -------
   GPL v2

  Notes:
  UNO/NANO are not supported!!! use this sketch with Atmel 32u4 based boards such as, the Leonardo or ProMicro, due to to its native USB support.
  The Windows application "HardwareSerialMonitor v1.1 & V1.3"  uses the OpenHardwaremonitor  OpenHardwareMonitorLib.dll to detect the hardware.  http://openhardwaremonitor.org/
  The application will not detect integrated graphics as a GPU!!!

    Version 1     : Initial release
    Version 1.1   : Fix intermittent screen flicker when in no activity mode "screen off" (due to inverter function?) fill the screen 128x64 black rectangle during this time.
	  Version 1.2   : Fix Freeze screen issue
    Version 1.2.1 : Top Config option to disable/enable positive/negative screen cycle

    Move HSMonitor(v1.1) to .Net 4.6.2

    Version 1.3   : Option to trigger an event at a given CPU or GPU threshold eg: LED indicator at 100% CPU Load.
                    Top Config option to disable all pre-selected power/gnd pins on Arduino pins D4 and D5 when not powering OLED from ProMicro
                    Top Config option to disable/enable "activitychecker" (Enable blank screen on serial timeout eg: PC powered down,
                    Disable to retain last sampled info eg: PC crash or overclocking diagnostics)

    Version 1.31   : MOVE CONFLICTING!!! NEOPIXEL PIN TO 10

    Version 1.32   : Add screen height/width definitions for updated Adafruit SSD1306 library
                   Clean up some code for clearing boxes not needed for OLED

    Version 1.33  : Add i2c Address change option
                    Add RotateScreen option
                    Add Neopixel Global Brightness
  Move HSMonitor(v1.3)

    Version 1.4  :  Add Some HardwareSerialMonitor v1.3 Features

  Move HSMonitor(v1.4) Change Baud rate to 115200

  Version 1.4.1  :  Change Baud rate to 115200

    ---------------------------------------------------------------
  ASCII: http://patorjk.com/software/taag/
    Arduino UNO/NANO/MINI ETC. (Atmel ATMega 328 Chips) are not supported, Please don't ask!!!

   _    ___ ___ ___    _   ___ ___ ___ ___
  | |  |_ _| _ ) _ \  /_\ | _ \_ _| __/ __|
  | |__ | || _ \   / / _ \|   /| || _|\__ \
  |____|___|___/_|_\/_/ \_\_|_\___|___|___/

  Adafruit Neopixel
  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit SSD1306 library
  https://github.com/adafruit/Adafruit_SSD1306

  Adafruit library ported to the SH1106
  https://github.com/badzz/Adafruit_SH1106      Currently used library in this sketch!!!

  Adafruit GFX Library
  https://github.com/adafruit/Adafruit-GFX-Library

  https://runawaybrainz.blogspot.com/2021/03/phat-stats-ssd1306-oled-hook-up-guide.html

*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include "bitmap.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define CODE_VERS  "1.4.1"  // Code version number 
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*--------------------------------------------------------------------------------------
    ___ ___  _  _ ___ ___ ___ _   _ ___    _ _____ ___ ___  _  _
   / __/ _ \| \| | __|_ _/ __| | | | _ \  /_\_   _|_ _/ _ \| \| |
  | (_| (_) | .` | _| | | (_ | |_| |   / / _ \| |  | | (_) | .` |
   \___\___/|_|\_|_| |___\___|\___/|_|_\/_/ \_\_| |___\___/|_|\_|
     ___  ___ _____ ___ ___  _  _ ___
    / _ \| _ \_   _|_ _/ _ \| \| / __|
   | (_) |  _/ | |  | | (_) | .` \__ \
    \___/|_|   |_| |___\___/|_|\_|___/

----------------------------------
    Pins Reference
  ----------------------------------
  ProMicro  : SDA: D2, SCL: D3
  Leonardo  : SDA: D2, SCL: D3
  NeoPixel  : D10
  OLED_RESET: 4   Reference only!!
  ----------------------------------
  QT-PY        : SDA: D4, SCL: D5
  NeoPixel     : A3
  Built in NeoPixel: 11 Reference only!!
  OLED_RESET   : -1     Reference only!!
  ---------------------
  XIAO         : SDA: D4, SCL: D5
  NeoPixel     : A1
  Built in LED : 13  Reference only!!
  OLED_RESET   : -1  Reference only!!
  ----------------------------------
  ESP32 LOLIN32: SDA: 21, SCL: 22
  NeoPixel     : 2 or 19
  Built in LED : 5   Reference only!!
  OLED_RESET   : -1  Reference only!!
  ----------------------------------
  STM32 BluePill: SDA: PB7, SCL: PB6
  NeoPixel      : PA7 (MOSI)
  OLED_RESET    : -1   Reference only!!
  ----------------------------------
  uVolume   :  SDA: D2, SCL: D3
  NeoPixel  :  D5
  OLED_RESET:  4  Reference only!!
  ----------------------------------
  */

//----------------------------------- OLED Setup ----------------------------------------

/*Uncomment the correct OLED display type, uncomment only one!!!*/
#define OLED_SSD1306
//#define OLED_SH1106

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

/*Rotate the display at the start:  0 or 2  (0, 180 degrees)*/
#define rotateScreen 2

/* Uncomment below, to enable positive and negative screen cycler */
//#define enableInvertscreen

/* Uncomment below, to take out small degree symbol for better spacing
   when hitting 100% cpu/gpu load the percent symbol gets clipped */
//#define noDegree

//--------------------------------- Threshold Triggers ---------------------------------------
/* Uncomment below, to enable custom threshold event triggers*/

/* User Custom  Triggers,*/
//#define enableCustomThesholdtriggers

/* Gnat-Tacho, NeoPixel ring bargraph example,*/
//#define enableNeopixelGauges //

/* uVolume only,*/
//#define uVol_enableThesholdtriggers

//------------------------------------- Other Stuff --------------------------------------------
/* Global NeoPixel Brightness,*/
#define neoBrightness 60

/* comment out, to disable blank screen on serial timeout to retain info eg: PC crash fault diagnostics  */
#define enableActivityChecker

/* Time between "DisplayStyle" changes */
#define displayChangeDelay 18000

/* Timer for active connection to host*/
#define lastActiveDelay 10000

//------------------------------------ End of User configuration ---------------------------------

/* Neo Pixel Setup */
#define NEOPIN         10
//#define NEOPIN         5 // uVolume

#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

/* Pre-define Hex NeoPixel colours,  eg. pixels.setPixelColor(0, BLUE); https://htmlcolorcodes.com/color-names/ */
#define BLUE       0x0000FF
#define GREEN      0x008000
#define RED        0xFF0000
#define ORANGE     0xFFA500
#define DARKORANGE 0xFF8C00
#define YELLOW     0xFFFF00
#define WHITE      0xFFFFFF
#define BLACK      0x000000 // OFF

//--------------------------------------------------------------------------------------

/*SH1106 OLED setup*/
#ifdef OLED_SH1106
#include <Adafruit_SH1106.h> // i2C not SPI
#define SH1106_128_64
#define OLED_RESET 4  //  "OLED_RESET" IS IS NOT A PHYSICAL PIN DO NOT CONNECT!!!
Adafruit_SH1106 display(OLED_RESET);
#endif

//-----------------------
/*SSD1306 OLED setup*/
#ifdef OLED_SSD1306
#include <Adafruit_SSD1306.h> // i2C not SPI
#define SSD1306_128_64
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4     // "OLED_RESET" IS IS NOT A PHYSICAL PIN DO NOT CONNECT!!!
//#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

//----------------------
/* More OLED stuff*/
int oledDraw = 0;
int oledOverride = 0;
//----------------------
/* Inverted timers for oled*/
long invertDelay = 60000; // 60 sec  delay
long lastInvertTime = 0;
int invertedStatus = 1;
//----------------------
/* Debounce timers for buttons  /// lastDebounceTime = millis();*/
long lastDebounceTime = 0;
long debounceDelay = 3000;
//----------------------

/* Delay screen event, to help stop screen data corruption ESP8622 use 25, most others 5 will do*/
int Serial_eventDelay = 0;
int baud = 115200; //serial do not adjust

/* Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
boolean bootMode = true;

/*vars for serial input*/
String inputString = "";
boolean stringComplete = false;
//----------------------
/* Start DisplayStyle */
int displayChangeMode = 1;
long lastDisplayChange;
//----------------------

/* ___ ___ _____ _   _ ___
  / __| __|_   _| | | | _ \
  \__ \ _|  | | | |_| |  _/
  |___/___| |_|  \___/|_|*/


void setup() {

  /* OLED SETUP */
#ifdef OLED_SH1106
  display.begin(SH1106_SWITCHCAPVCC, i2c_Address);    // initialize with the I2C addr 0x3D (for the 128x64)
#endif

#ifdef OLED_SSD1306
  display.begin(SSD1306_SWITCHCAPVCC, i2c_Address); // initialize with the I2C addr 0x3D (for the 128x64
#endif

  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setRotation(rotateScreen);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  display.clearDisplay();

  /* stops text wrapping*/
  display.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters

  /* Serial setup, start serial port at 9600 bps and wait for port to open:*/
  Serial.begin(baud);  //  USB Serial Baud Rate
  inputString.reserve(200);

  /* Set up the NeoPixel*/
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(neoBrightness); // Global Brightness
  pixels.show(); // Turn off all Pixels

  /*Initial Load screen*/
  splashScreen();

}

//END of Setup

/* __  __   _   ___ _  _   _    ___   ___  ___
  |  \/  | /_\ |_ _| \| | | |  / _ \ / _ \| _ \
  | |\/| |/ _ \ | || .` | | |_| (_) | (_) |  _/
  |_|  |_/_/ \_\___|_|\_| |____\___/ \___/|_|*/


void loop() {

  /*Serial stuff*/
  serialEvent();

#ifdef enableActivityChecker
  activityChecker();
#endif

  /*change display screen*/
  if ((millis() - lastDisplayChange) > displayChangeDelay)
  {
    if (displayChangeMode == 1) {
      displayChangeMode = 2;
      display.fillRect(0, 0, 128 , 64, BLACK);
    }
    else if (displayChangeMode == 2) {
      displayChangeMode = 3;
      display.fillRect(0, 0, 128 , 64, BLACK);
    }
    else if (displayChangeMode == 3) {
      displayChangeMode = 1;
      display.fillRect(0, 0, 128 , 64, BLACK);
    }

    lastDisplayChange = millis();
  }

  /* OLED DRAW STATS */
  if (stringComplete) {

    if (bootMode) {
      display.clearDisplay();
      display.display();
      //display.stopscroll();
      bootMode = false;
    }

    lastActiveConn = millis();

    if (displayChangeMode == 1) {
      DisplayStyle1B();
    }
    else if (displayChangeMode == 2) {
      DisplayStyle2 ();
    }
    else if (displayChangeMode == 3) {
      DisplayStyle3B ();
    }

    inputString = "";
    stringComplete = false;


    /* Keep running anti screen burn, whilst serial is active */
    if ((millis() - lastInvertTime) > invertDelay && oledDraw == 1) {
      lastInvertTime = millis();

#ifdef enableInvertscreen
      inverter();
#endif
    }
  }
}

//END of Main Loop


/*  __ _   _ _  _  ___ _____ ___ ___  _  _ ___
  | __| | | | \| |/ __|_   _|_ _/ _ \| \| / __|
  | _|| |_| | .` | (__  | |  | | (_) | .` \__ \
  |_|  \___/|_|\_|\___| |_| |___\___/|_|\_|___/*/

//-------------------------------------------  NeoPixel Reset -------------------------------------------------------------

void allNeoPixelsOff() {
  for ( int i = 0; i < NUMPIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 0 );
  }
  //pixels.show();
}

//-------------------------------------------  Serial Events -------------------------------------------------------------

void serialEvent() {

  while (Serial.available()) {          //  32u4 USB Serial Available?
    char inChar = (char)Serial.read();  // Read 32u4 USB Serial
    //Serial.print(inChar); // Debug Incoming Serial

    inputString += inChar;
    if (inChar == '|') {
      stringComplete = true;

      delay(Serial_eventDelay);   //delay screen event to stop screen data corruption

      //display.drawRect(82, 0, 44, 10, WHITE); // Position Test
      display.fillRect(115, 0, 42, 10, BLACK); // Flash top right corner when updating
      display.display();

    }
  }
}

void activityChecker() {
  if (millis() - lastActiveConn > lastActiveDelay)
    activeConn = false;
  else
    activeConn = true;
  if (!activeConn) {
    if (invertedStatus)

      //Turn off display when there is no activity
      display.invertDisplay(0);
    display.clearDisplay();
    display.display();

    //Experimental,  attempt to stop intermittent screen flicker when in no activity mode "screen off" (due to inverter function?) fill the screen 128x64 black rectangle
    display.fillRect(0, 0, 128, 64, BLACK);
    display.display();
    oledDraw = 0;

    //Turn off NeoPixel when there is no activity
    allNeoPixelsOff();
    pixels.show();
  }
}

//-------------------------------------------- Anti Screen Burn inverter ------------------------------------------------

void antiBurn() {
  display.invertDisplay(0);
  display.fillRect(0, 0, 128, 64, BLACK);
  display.display();
  oledDraw = 0;
}

void inverter() {
  if ( invertedStatus == 1 ) {
    invertedStatus = 0;
  } else {
    invertedStatus = 1;
  };
  display.invertDisplay(invertedStatus);
  display.display();
}

//--------------------------------------------- Splash Screens --------------------------------------------------------
void splashScreen() {

  display.drawBitmap(0, 0, JustGnatBMP, 64, 64, WHITE);
  display.setTextSize(3);
  display.setCursor(58, 5);
  display.println("GNAT-");
  display.setTextSize(2);
  display.setCursor(64, 30);
  display.println("STATS");

  //Set version to USB Serial
  display.setTextSize(1);
  display.setCursor(68, 55);
  display.print("USB:v");
  display.print (CODE_VERS);

  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();

  display.setTextSize(3); //set background txt font size
  display.setCursor(1, 1);
  display.println(">");
  display.display();
  display.setTextSize(2);
  display.setCursor(20, 30);
  display.display();
  display.println("0101010..");
  display.display();
  display.setTextSize(1);
  display.setCursor(1, 54);
  display.println("waiting for data.....");
  display.display();
  //delay(5000);
  display.clearDisplay();
  //display.display(); //note... not needed "main loop" will initiate this, when serial coms establish
}
