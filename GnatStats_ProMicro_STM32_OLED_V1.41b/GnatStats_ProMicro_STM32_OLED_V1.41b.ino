/*
  ------------------------------------------------------------------------------------------
    _____             _    _____ _        _          ____  _      ______ _____
   / ____|           | |  / ____| |      | |        / __ \| |    |  ____|  __ \
  | |  __ _ __   __ _| |_| (___ | |_ __ _| |_ ___  | |  | | |    | |__  | |  | |
  | | |_ | '_ \ / _` | __|\___ \| __/ _` | __/ __| | |  | | |    |  __| | |  | |
  | |__| | | | | (_| | |_ ____) | || (_| | |_\__ \ | |__| | |____| |____| |__| |
   \_____|_| |_|\__,_|\__|_____/ \__\__,_|\__|___/  \____/|______|______|_____/

  ------------------------------------------------------------------------------------------

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
  
  The application will not detect integrated graphics as a GPU!!!
  Presently HardwareSerialMonitor does not like virtual Bluetooth COM ports present on the users PC!!!

  ALWAYS RUN "HARDWARE SERIAL MONITOR" AS ADMIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  "Hardware Serial Monitor" Was inspired by the Visual Studio project kindly shared by psyrax see: https://github.com/psyrax/SerialMonitor


  ProMicro hookup:
  ----------------
  NeoPixel DataIn: D4 with 220r series resistor


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

    Version 1.4    : STM32 BluePill Support
                   : Remove PowerPin Support

    Version 1.41   : Add Configuration_Settings.h tab

    Version 1.41b  : Add screen height/width definitions for updated Adafruit SSD1306 library & General clean up

    Arduino UNO/NANO/MINI ETC. with Atmel ATMega 328 Chips are not supported, Please don't ask!!!


         ToDo:
         Windows custom GnatStats device icon
         Auto or button screen change option,
         PC Diagnostic switch / mode eg: Min / Max readings,
         Analogue Panel Meter Readings output



  ASCII: http://patorjk.com/software/taag/
  ------------------------------------------------------------------------------------------
   _    ___ ___ ___    _   ___ ___ ___ ___
  | |  |_ _| _ ) _ \  /_\ | _ \_ _| __/ __|
  | |__ | || _ \   / / _ \|   /| || _|\__ \
  |____|___|___/_|_\/_/ \_\_|_\___|___|___/

  ------------------------------------------------------------------------------------------
  ATMEL Libraries
  ---------------

  Adafruit Neopixel:
  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit SSD1306 library:
  https://github.com/adafruit/Adafruit_SSD1306

  Adafruit library ported to the SH1106:
  https://github.com/badzz/Adafruit_SH1106      Currently used library in this sketch!!!

  Alternative SSD1306 Library:
  https://github.com/wonho-maker/Adafruit_SH1106
  https://github.com/shondll/Adafruit_SSD1306

  Adafruit GFX Library:
  https://github.com/adafruit/Adafruit-GFX-Library

  --------------------------------------------------------------------------------------------------------------

  STM32 BluePill Libraries
  -------------------------
  STM32duino:
  https://github.com/rogerclarkmelbourne/Arduino_STM32
  
  Adafruit GFX Library
  https://github.com/adafruit/Adafruit-GFX-Library

  Adafruit Neopixel STM32 library:
  
   Note. Library uses hardware SPI1
   Connect the WS2812B data input to MOSI (PA7) on your board.
  https://github.com/rogerclarkmelbourne/Arduino_STM32/tree/master/STM32F1/libraries/WS2812B


  Adafruit SSD1306 STM32 library:

  https://github.com/rogerclarkmelbourne/Arduino_STM32/tree/master/STM32F1/libraries/Adafruit_SSD1306


  Adafruit SH1106 STM32 library:
  https://github.com/Tamakichi/Adafruit_SH1106_STM32

*/

#include "Configuration_Settings.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "bitmap.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define CODE_VERS  "1.41"  // Code version number

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


/* Neo Pixel Setup */
//int NeoBrightness = 50; // moved to config tab
#define NUMPIXELS   16
#define NEOPIN      5  // ATMEL PIN //STM32 uses hardware SPi pin (P7)PA7(MOSI) no need to configure it
//---------------------------------------------------------------------------------------


#ifdef ProMicro
 
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
#endif

#ifdef STM32_BluePill
#include <WS2812B.h> // STM32 
WS2812B pixels = WS2812B(NUMPIXELS); //STM32 neopixel library
//STM32 uses hardware SPi pin PA7(MOSI) no need to configure it
#endif

//---------------------------------------------------------------------------------------
/* Pre-define Hex NeoPixel colours,  eg. pixels.setPixelColor(0, BLUE); https://htmlcolorcodes.com/color-names/ */
#define BLUE       0x0000FF
#define GREEN      0x008000
#define RED        0xFF0000
#define ORANGE     0xFFA500
#define DARKORANGE 0xFF8C00
#define YELLOW     0xFFFF00
#define WHITE      0xFFFFFF
#define BLACK      0x000000 // OFF

//---------------------------------------------------------------------------------------
/*SH1106 OLED setup*/

#ifdef OLED_SH1106

#ifdef ProMicro
#include <Adafruit_SH1106.h> // i2C not SPI

#else

#include <Adafruit_SH1106_STM32.h> // i2C not SPI
#endif

#define SH1106_128_64
#define OLED_RESET 4  //  "OLED_RESET" IS IS NOT A PHYSICAL PIN DO NOT CONNECT!!!
Adafruit_SH1106 display(OLED_RESET); 

#endif


//------------------------------------
/*SSD1306 OLED setup*/
#ifdef OLED_SSD1306

#ifdef ProMicro
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#include <Adafruit_SSD1306.h>

#define SSD1306_128_64
#define OLED_RESET 4    //  "OLED_RESET" IS IS NOT A PHYSICAL PIN DO NOT CONNECT!!!
//Adafruit_SSD1306 display(OLED_RESET);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#else

#include <Adafruit_SSD1306_STM32.h>  // i2C not SPI

#define SSD1306_128_64
#define OLED_RESET 4   //  "OLED_RESET" IS IS NOT A PHYSICAL PIN DO NOT CONNECT!!!
Adafruit_SSD1306 display(OLED_RESET);
#endif

#endif

//---------------------------------------------------------------------------------------
/* Uncomment below, to take out small degree symbol for better spacing
   when hitting 100% cpu/gpu load the percent symbol gets clipped */
//#define noDegree

//---------------------------------------------------------------------------------------
/* Inverted timers for oled*/
//long invertDelay = 60000; // moved to config tab
long lastInvertTime = 0;
int  invertedStatus = 1;

/* More OLED stuff*/
int displayDraw = 0;
int displayOverride = 0;

/* Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
//#define lastActiveDelay 8000 // moved to config tab
boolean bootMode = true;

/*vars for serial input*/
String inputString = "";
boolean stringComplete = false;

/* cycle screen DisplayStyles */
int displayChangeMode = 2;
long lastDisplayChange;

/*
  ------------------------------------------------------------------------------------------
   ___ ___ _____ _   _ ___
  / __| __|_   _| | | | _ \
  \__ \ _|  | | | |_| |  _/
  |___/___| |_|  \___/|_|
  ------------------------------------------------------------------------------------------
*/

void setup() {

  /*STM32 Serial Activity LED Setup*/
#ifdef STM32_BluePill
  pinMode(PC13, OUTPUT); // STM32 BluePill Builtin LED
#endif

  /* OLED SETUP */

#ifdef OLED_SH1106
  display.begin(SH1106_SWITCHCAPVCC, 0x3c);    // initialize with the I2C addr 0x3D (for the 128x64)
#endif

#ifdef OLED_SSD1306
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); // initialize with the I2C addr 0x3D (for the 128x64)
#endif


  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setRotation(ASPECT);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  display.clearDisplay();

  /* stops text wrapping*/
  display.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters


  /* Serial setup, start serial port at 9600 bps and wait for port to open:*/
  Serial.begin(9600); // 32u4 USB Serial Baud Rate
  inputString.reserve(200);

  /* Set up the NeoPixel*/
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(NeoBrightness); // Atmel Global Brightness (does not work for STM32!!!!)
  pixels.show(); // Turn off all Pixels

  /*Initial Load screen*/

  splashScreen();

}

//END of Setup


/*
  ------------------------------------------------------------------------------------------
   __  __   _   ___ _  _   _    ___   ___  ___
  |  \/  | /_\ |_ _| \| | | |  / _ \ / _ \| _ \
  | |\/| |/ _ \ | || .` | | |_| (_) | (_) |  _/
  |_|  |_/_/ \_\___|_|\_| |____\___/ \___/|_|
  ------------------------------------------------------------------------------------------
*/

void loop() {


  /*Serial stuff*/
  serialEvent();

  /*STM32 Serial Activity LED*/
#ifdef STM32_BluePill
  digitalWrite(PC13, LOW);    // turn the LED off HIGH(OFF) LOW (ON)
#endif

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

      splashScreen2();
      display.clearDisplay();
      display.display();

      bootMode = false;
    }

    lastActiveConn = millis();

    if (displayChangeMode == 1) {
      DisplayStyle1();

    }
    else if (displayChangeMode == 2) {
      DisplayStyle2 ();
    }
    else if (displayChangeMode == 3) {
      DisplayStyle3 ();
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
  ------------------------------------------------------------------------------------------
    __ _   _ _  _  ___ _____ ___ ___  _  _ ___
  | __| | | | \| |/ __|_   _|_ _/ _ \| \| / __|
  | _|| |_| | .` | (__  | |  | | (_) | .` \__ \
  |_|  \___/|_|\_|\___| |_| |___\___/|_|\_|___/
  ------------------------------------------------------------------------------------------
*/

//-------------------------------------------  NeoPixel Reset -------------------------------------------------------------

void allNeoPixelsOff() {
  for ( int i = 0; i < NUMPIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 0 );
  }
  pixels.show();
}


//-------------------------------------------  Serial Events -------------------------------------------------------------

void serialEvent() {

  while (Serial.available()) {          //  32u4 USB Serial Available?
    char inChar = (char)Serial.read();  // Read 32u4 USB Serial
    //Serial.print(inChar); // Debug Incoming Serial

    inputString += inChar;
    if (inChar == '|') {
      stringComplete = true;

      //display.drawRect(82, 0, 44, 10, WHITE); // Position Test
      display.fillRect(115, 0, 42, 10, BLACK); // Flash top right corner when updating
      display.display();

      /*STM32 Serial Activity LED*/
#ifdef STM32_BluePill
      digitalWrite(PC13, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
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
    if (invertedStatus)

      //Turn off display when there is no activity
      display.invertDisplay(0);
    display.clearDisplay();
    display.display();

    //Experimental,  attempt to stop intermittent screen flicker when in no activity mode "screen off" (due to inverter function?) fill the screen 128x64 black rectangle
    display.fillRect(0, 0, 128, 64, BLACK);
    display.display();
    displayDraw = 0;

    //Turn off NeoPixel when there is no activity
    allNeoPixelsOff();

  }
}

//-------------------------------------------- Anti Screen Burn inverter ------------------------------------------------


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

  allNeoPixelsOff();
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

  //inverter(); // inverted splashscreen image

  // USB Serial Screen

  display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, WHITE);
  display.display();
  allNeoPixelsOff();

}

//---------------------------------------------------------------------------------------------------------------------


void splashScreen2() {

  allNeoPixelsOff();
  display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, WHITE);
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
}
