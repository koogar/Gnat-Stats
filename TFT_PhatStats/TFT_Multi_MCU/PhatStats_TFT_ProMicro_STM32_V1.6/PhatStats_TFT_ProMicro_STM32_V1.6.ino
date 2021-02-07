/*

    _____             _    _____ _        _         _______ ______ _______
   / ____|           | |  / ____| |      | |       |__   __|  ____|__   __|
  | |  __ _ __   __ _| |_| (___ | |_ __ _| |_ ___     | |  | |__     | |
  | | |_ | '_ \ / _` | __|\___ \| __/ _` | __/ __|    | |  |  __|    | |
  | |__| | | | | (_| | |_ ____) | || (_| | |_\__ \    | |  | |       | |
   \_____|_| |_|\__,_|\__|_____/ \__\__,_|\__|___/    |_|  |_|       |_|

  GNATSTATS PC Performance Monitor - Version 1.x  Rupert Hirst & Colin Conway © 2016
  http://tallmanlabs.com  & http://runawaybrainz.blogspot.com/

  Licence
  -------

  Attribution-NonCommercial-ShareAlike  CC BY-NC-SA

  This license lets others remix, tweak, and build upon your work non-commercially, as long as they credit you and license their new creations under the identical terms.

  https://creativecommons.org/licenses/

  Notes:

  I strongly suggest using this sketch with Atmel 32u4 based boards such as, the Leonardo or ProMicro, due to to its native USB support.

  The Windows application "HardwareSerialMonitor v1"  uses the OpenHardwaremonitor  OpenHardwareMonitorLib.dll to detect the hardware.  http://openhardwaremonitor.org/
  The Windows application "HardwareSerialMonitor v1.1"  uses the LibreHardwareMonitor OpenHardwareMonitorLib.dll to detect the hardware.  https://github.com/LibreHardwareMonitor/LibreHardwareMonitor

  The application will not detect integrated graphics as a GPU!!!
  Presently HardwareSerialMonitor does not like virtual Bluetooth COM ports present on the users PC!!!

  ALWAYS RUN "HARDWARE SERIAL MONITOR" AS ADMIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  "Hardware Serial Monitor" Was inspired by the Visual Studio project kindly shared by psyrax see: https://github.com/psyrax/SerialMonitor


  ProMicro hookup:
  ----------------
  NeoPixel DataIn: P5 with 220r series resistor


    OLED Version 1     : Initial release
    OLED Version 1.1   : Fix intermittent screen flicker when in no activity mode "screen off" (due to inverter function?) fill the screen 128x64 black rectangle during this time.
	  OLED Version 1.2   : Fix Freeze screen issue
    OLED Version 1.2.1 : Top Config option to disable/enable positive/negative screen cycle

    Move HSMonitor(v1.1) to .Net 4.6.2

    OLED Version 1.3   : Option to trigger an event at a given CPU or GPU threshold eg: LED indicator at 100% CPU Load.
                    Top Config option to disable all pre-selected power/gnd pins on Arduino pins D4 and D5 when not powering OLED from ProMicro
                    Top Config option to disable/enable "activitychecker" (Enable blank screen on serial timeout eg: PC powered down,
                    Disable to retain last sampled info eg: PC crash or overclocking diagnostics)

    OLED Version 1.31   : MOVE CONFLICTING!!! NEOPIXEL PIN TO 10

    OLED Version 1.4    : STM32 BluePill Support

                        : Remove PowerPin Support

     TFT Version 1.6    : STM32 BluePill & ProMicro Suppport
                        : 128x160 ST7735 & 240x320 ILI9341 TFT Support
                        : Add PWM Output for Back Light
                        : Seperate "Configuration_Settings.h" to make settings easier
                        : No Blink screen refresh

                         Arduino UNO/NANO/MINI ETC. (Atmel ATMega 328 Chips) are not supported
                         Use Leonardo/ProMicro (Atmel 32u4) or STM32BluePill


  ASCII: http://patorjk.com/software/taag/

   _    ___ ___ ___    _   ___ ___ ___ ___
  | |  |_ _| _ ) _ \  /_\ | _ \_ _| __/ __|
  | |__ | || _ \   / / _ \|   /| || _|\__ \
  |____|___|___/_|_\/_/ \_\_|_\___|___|___/


  ATMEL Libraries
  ---------------

  Adafruit Atmel Neopixel
  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit Neopixel STM32 library
   Note. Library uses SPI1. Connect the WS2812B data input to MOSI (A7) on your board.
  https://github.com/rogerclarkmelbourne/Arduino_STM32/tree/master/STM32F1/libraries/WS2812B

  Adafruit GFX Library Atmel & STM32
  https://github.com/adafruit/Adafruit-GFX-Library

  ILI9341 TFT  Atmel & STM32
  https://github.com/adafruit/Adafruit_ILI9341

  ST7735 TFT  Atmel & STM32
  https://github.com/adafruit/Adafruit-ST7735-Library


  STM32 BluePill Reference Pins
  -----------------------------
  PWM BackLight:  PB0
  SPi(Hardware):  CS:PB11  RST:PB10  DC:PB1  SCLK:PA5  MOSI:PA7

  32u4  ProMicro Reference Pins
  -----------------------------
  PWM BackLight: 3
  Neopixel Pin : 5
  SPi(Hardware):  CS:10   RST:8   DC:9   SCLK:15  MOSI:16

*/

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#define CODE_VERS  "1.6"  // Code version number

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/


#include "Configuration_Settings.h" // load easy settings first
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include "bitmap.h"


/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                 SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
  /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#ifdef STM32_BluePill
/* Sorry no NeoPixels for the STM32 as it uses the SPi MOSI pin !!!*/
/* Screen TFT backlight brightness */
int TFT_backlight_PIN = PB0;
#endif

#ifdef ProMicro
#include <Adafruit_NeoPixel.h>
/* Sorry no NeoPixels for the STM32 as it uses the SPi MOSI pin !!!*/
#define NEOPIN 5   // Digital IO pin connected to the NeoPixels.
#define NUMPIXELS 16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
/* Screen TFT backlight brightness */
int TFT_backlight_PIN = 3;    //Atmel PWM
#endif

//---------------------------------------------------------------------------------------

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

/* Pre-define Hex NeoPixel colours,  eg. pixels.setPixelColor(0, BLUE); https://htmlcolorcodes.com/color-names/ */
#define BLUE       0x0000FF
#define GREEN      0x008000
#define RED        0xFF0000
#define ORANGE     0xFFA500
#define DARKORANGE 0xFF8C00
#define YELLOW     0xFFFF00
//---------------------------------------------------------------------------------------

/* Uncomment below, to take out small degree symbol for better spacing
   when hitting 100% cpu/gpu load the percent symbol can get clipped */
//#define noDegree

/* Inverted timers for display*/
//long invertDelay = 60000; // move setting to config tab
long lastInvertTime = 0;
int  invertedStatus = 1;

/* More Display stuff*/
int displayDraw = 0;
int displayOverride = 0;

/* Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
//#define lastActiveDelay 8000 // move setting to config tab
boolean bootMode = true;

/*vars for serial input*/
String inputString = "";
boolean stringComplete = false;

/* cycle screen DisplayStyles */
int displayChangeMode = 1;
long lastDisplayChange;

//---------------------------------------------------------------------------------------

/*ST7735 TFT setup*/
#ifdef TFT_ST7735
#include <Adafruit_ST7735.h>
#endif

/*ILI9321 TFT setup*/
#ifdef TFT_ILI9341
#include <Adafruit_ILI9341.h>
#endif

//---------------------------------------------------------------------------------------

#ifdef TFT_ST7735

#ifdef STM32_BluePill // STM32 SPi Hardware only for speed
/* SPi Display Pins */
#define TFT_CS     PB11
#define TFT_RST    PB10
#define TFT_DC     PB1
/* These pins do not have to be defined as they are hardware pins */
//Connect TFT_SCLK to pin   PA5
//Connect TFT_MOSI to pin   PA7
#endif

#ifdef ProMicro        // ProMicro SPi= CS:10 RST:0 DC:9 SCLK:15 MOSI:16
/* SPi Display Pins */
#define TFT_DC       9    // 7
#define TFT_CS       10   // 5
#define TFT_RST      0    // 8 // Arduino reset pin(RST)in which case, set this #define pin to 0!
/* These pins do not have to be defined as they are hardware pins */
//Connect TFT_SCLK to pin  15
//Connect TFT_MOSI to pin  16
#endif
Adafruit_ST7735  tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST); // Hardware SPI pins
#endif

//---------------------------------------------------------------------------------------

#ifdef TFT_ILI9341 // STM32 SPi Hardware  ProMicro SPi= CS:10 RST:0 DC:9 SCLK:15 MOSI:16

#ifdef ProMicro
#define TFT_DC       9  // 7
#define TFT_CS       10 // 5
#define TFT_RST      0  // 8 Arduino reset pin (RST) in which case, set this #define pin to 0!
/* These pins do not have to be defined as they are hardware pins */
//Connect TFT_SCLK to pin  15
//Connect TFT_MOSI to pin  16
#endif

#ifdef STM32_BluePill // STM32 SPi Hardware only for speed // STM32 SPi= CS:PB11 RST:PB10 DC:PB1 SCLK:PA5 MOSI:PA7
#define TFT_CS     PB11
#define TFT_RST    PB10 // you can also connect this to the STM32 reset leave it undefined
#define TFT_DC     PB1
/* These pins do not have to be defined as they are hardware pins */
//Connect TFT_SCLK to pin   PA5
//Connect TFT_MOSI to pin   PA7

#endif
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); // Use hardware SPI

#endif

//---------------------------------------------------------------------------------------

/* ___ ___ _____ _   _ ___
  / __| __|_   _| | | | _ \
  \__ \ _|  | | | |_| |  _/
  |___/___| |_|  \___/|_|*/

void setup() {

  /* Serial setup, start serial port at 9600 bps and wait for port to open:*/
  Serial.begin(9600); // 32u4 USB Serial Baud Rate
  inputString.reserve(200);

  //---------------------------------------------------------------------------------------

  /* ST7735 SETUP */
#ifdef TFT_ST7735
  delay(200); // Give the micro time to initiate the SPi bus
  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  //tft.initR(INITR_GREENTAB);   // initialize a ST7735S chip, green tab
  tft.setRotation(ASPECT);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  tft.fillScreen(ST7735_BLACK);
#endif

  //---------------------------------------------------------------------------------------

  /* ILI9341 SETUP */
#ifdef TFT_ILI9341
  delay(200); // Give the micro time to initiate the SPi bus
  tft.begin();   
  tft.setRotation(ASPECT);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  tft.fillScreen(ILI9341_BLACK);
#endif

  //---------------------------------------------------------------------------------------

  /* stops text wrapping*/
  tft.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters

  /*Initial Load screen*/
  splashScreen();

  /*TFT Backlight Setup*/
  pinMode(TFT_backlight_PIN, OUTPUT); //turn off back light// declare backlight pin to be an output:

  /*STM32 Serial Activity LED*/
#ifdef STM32_BluePill
  pinMode(PC13, OUTPUT); // STM32 BluePill Builtin LED /  HIGH(OFF) LOW (ON)
#endif

  /*ProMicro  Serial Activity LED*/
#ifdef ProMicro
  pinMode(13, OUTPUT); // STM32 BluePill Builtin LED /  HIGH(OFF) LOW (ON)
#endif

#ifdef ProMicro
  pixels.begin();// Sets up the SPI
  pixels.show();// Clears the strip, as by default the strip data is set to all LED's off.
  pixels.setBrightness(NeoBrightness); // this only works on the ProMicro
#endif
}

//END of Setup

/* __  __   _   ___ _  _   _    ___   ___  ___
  |  \/  | /_\ |_ _| \| | | |  / _ \ / _ \| _ \
  | |\/| |/ _ \ | || .` | | |_| (_) | (_) |  _/
  |_|  |_/_/ \_\___|_|\_| |____\___/ \___/|_|*/

void loop() {

  /*Serial stuff*/
  serialEvent();

  /*STM32 Serial Activity LED*/
#ifdef STM32_BluePill
  digitalWrite(PC13, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
#endif
  /*ProMicro Serial Activity LED*/
#ifdef ProMicro
  digitalWrite(13, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
#endif

#ifdef enableActivityChecker
  activityChecker();
#endif

  /*change display screen*/
  if ((millis() - lastDisplayChange) > displayChangeDelay)
  {
    if (displayChangeMode == 1) {
      displayChangeMode = 2;
    }
    if (displayChangeMode == 2) {
      displayChangeMode = 1;
    }

    lastDisplayChange = millis();
  }

  /* DISPLAY DRAW STATS */
  if (stringComplete) {

    if (bootMode) {


#ifdef TFT_ST7735
      tft.fillScreen(ST7735_BLACK);
#endif

#ifdef TFT_ILI9341
      tft.fillScreen(ILI9341_BLACK);
#endif
      bootMode = false;
    }

    lastActiveConn = millis();

    backlightON();


    if (displayChangeMode == 1) {

#ifdef TFT_ST7735
      DisplayStyleTFT_ST7735();   //ST7735 128x160
#endif

#ifdef TFT_ILI9341
      DisplayStyleTFT_ILI9341(); // ILI9341 240x320
#endif

    }
    if (displayChangeMode == 2) {

#ifdef TFT_ST7735
      DisplayStyleTFT_ST7735();   //ST7735 128x160
#endif

#ifdef TFT_ILI9341
      DisplayStyleTFT_ILI9341(); // ILI9341 240x320
#endif

    }

    inputString = "";
    stringComplete = false;


    /* Keep running anti screen burn, whilst serial is active */
    if ((millis() - lastInvertTime) > invertDelay && displayDraw == 1) {
      lastInvertTime = millis();

#ifdef enableInvertscreen
      inverter();
#endif
    }
  }
}

//END of Main Loop


/*
    __ _   _ _  _  ___ _____ ___ ___  _  _ ___
  | __| | | | \| |/ __|_   _|_ _/ _ \| \| / __|
  | _|| |_| | .` | (__  | |  | | (_) | .` \__ \
  |_|  \___/|_|\_|\___| |_| |___\___/|_|\_|___/

*/
#ifdef ProMicro

void allNeoPixelsOff() {
  for ( int i = 0; i < NUMPIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 0 );
  }
  pixels.show();
}

#endif
//-------------------------------------------  TFT Backlight  -------------------------------------------------------------

void backlightON () {
  analogWrite(TFT_backlight_PIN, TFT_brightness); // TFT turn on backlight
}

void backlightOFF () {
  analogWrite(TFT_backlight_PIN, 0);       // TFT turn off backlight
}

//-------------------------------------------  Serial Events -------------------------------------------------------------

void serialEvent() {

  while (Serial.available()) {          //  32u4 USB Serial Available?
    char inChar = (char)Serial.read();  // Read 32u4 USB Serial
    //Serial.print(inChar); // !!!!Debug Incoming Serial, if this is left running a buffer overflow will occur!!!!

    inputString += inChar;
    if (inChar == '|') {
      stringComplete = true;

      /*STM32 Serial Activity LED*/
#ifdef STM32_BluePill
      digitalWrite(PC13, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
      delay(5);
#endif
      /*ProMicro Serial Activity LED*/
#ifdef ProMicro
      digitalWrite(13, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
      delay(5);
#endif

    }
  }
}

//------------------------------------------- activityChecker  -----------------------------------------------------------
void activityChecker() {
  if (millis() - lastActiveConn > lastActiveDelay)

    activeConn = false;
  else
    activeConn = true;
  if (!activeConn) {

    /* Turn off display when there is no activity, */
    backlightOFF ();

    if (invertedStatus)

      //Turn off display when there is no activity
      tft.invertDisplay(0);

    displayDraw = 0;

#ifdef TFT_ST7735
    tft.fillScreen(ST7735_BLACK);
#endif

#ifdef TFT_ILI9341
    tft.fillScreen(ILI9341_BLACK);
#endif

#ifdef ProMicro
    allNeoPixelsOff();
#endif

    // turn off backlight
    backlightOFF ();
  }
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

//--------------------------------------------- Splash Screens --------------------------------------------------------
void splashScreen() {

  // turn on backlight
  backlightON();

#ifdef ProMicro
  allNeoPixelsOff();
#endif

#ifdef TFT_ST7735 // USB Serial Screen
  tft.fillScreen(ST7735_BLACK);
  tft.drawBitmap(0, 36, JustGnatBMP, 64, 64, YELLOW);
  tft.setTextSize(3);
  tft.setCursor(58, 49);
  tft.println("PHAT ");
  tft.setTextSize(2);
  tft.setCursor(64, 74);
  tft.println("STATS");

  //Set version to USB Serial
  tft.setTextSize(1);
  tft.setCursor(64, 99);
  tft.print("TFT:v");
  tft.print (CODE_VERS);

  tft.setCursor(52, 110); tft.setTextColor(ST7735_RED);
  tft.print("TallMan Labs");

  delay(3000);

  tft.fillScreen(ST7735_BLACK);
  tft.drawBitmap(26, 2, WaitingDataBMP2_90, 76, 154, RED);

  delay(1000);
    /* Clear Screen*/
  tft.fillScreen(ST7735_BLACK);
#endif

#ifdef TFT_ILI9341 // USB Serial Screen

  tft.fillScreen(ILI9341_BLACK);

  tft.drawBitmap(84, 70, JustGnatBMP, 64, 64, YELLOW);
  tft.setTextSize(3);
  tft.setCursor(86, 142);
  tft.println("PHAT ");
  tft.setTextSize(3);
  tft.setCursor(78, 170);
  tft.println("STATS");

  //Set version to USB Serial
  tft.setTextSize(1);
  tft.setCursor(96, 204);
  tft.print("TFT:v");
  tft.print (CODE_VERS);

  tft.setTextSize(1);
  tft.setCursor(78, 219); tft.setTextColor(ILI9341_RED);
  tft.print("tallmanlabs.com");

  delay(3000);

  /* Clear Screen*/
  tft.fillScreen(ILI9341_BLACK);
  tft.drawBitmap(82, 80, WaitingDataBMP2_90, 76, 154, WHITE);

  delay(1000);
  /* Clear Screen*/
  tft.fillScreen(ILI9341_BLACK);
#endif

}
