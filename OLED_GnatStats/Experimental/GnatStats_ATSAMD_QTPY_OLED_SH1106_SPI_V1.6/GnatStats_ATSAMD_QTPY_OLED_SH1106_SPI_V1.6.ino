#define CODE_VERS  "1.6"  // Code version number 

/*
   _____ __  __ _         _            ___           _   ___ _        _
  |_   _|  \/  | |   __ _| |__ ______ / __|_ _  __ _| |_/ __| |_ __ _| |_ ___
    | | | |\/| | |__/ _` | '_ (_-<___| (_ | ' \/ _` |  _\__ \  _/ _` |  _(_-<
    |_| |_|  |_|____\__,_|_.__/__/    \___|_||_\__,_|\__|___/\__\__,_|\__/__/

   uVolume, GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
   Rupert Hirst & Colin Conway © 2016-2018

   http://tallmanlabs.com
   http://runawaybrainz.blogspot.com/

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

    Version 1.31   : MOVE CONFLICTING!!! NEOPIXEL PIN TO 10 (32u4)

    Version 1.32   : Add screen height/width definitions for updated Adafruit SSD1306 library
                   Clean up some code for clearing boxes not needed for OLED

    Version 1.33  : Add i2c Address change option.
                    Add RotateScreen option.
                    Add Neopixel Global Brightness.

  Move HSMonitor(v1.3)

    Version 1.4   : Add Some HardwareSerialMonitor v1.3 Features

  Move HSMonitor(v1.4) Change Baud rate to 115200.


    Version 1.5      : Add option to manually Change the name of the CPU/GPU + GPU RAM size.
                     : Add option to change CPU/GPU name length eg: for newer Nvidia drivers
                     : Change Baud rate to 115200
                     : Fix Seeeduino board file link
    Version 1.6
                     : ATSAMD21 SH1106 Support experimental

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


  SH1106 Library
  https://github.com/adafruit/Adafruit_SH110x

  Adafruit GFX Library
  https://github.com/adafruit/Adafruit-GFX-Library // latest version is required for SH1106 Support
  https://github.com/adafruit/Adafruit_BusIO       // latest version is required for SH1106 Support

  Board Manager QY-PY
  -------------------
  Click on File > Preference, and fill Additional Boards Manager URLs with the url below:

  Install Arduino ATSAMD then ADD
  https://adafruit.github.io/arduino-board-index/package_adafruit_index.json

  Drivers
  ------------
  https://github.com/adafruit/Adafruit_Windows_Drivers/releases/tag/2.5.0.0

  Board Manager XIAO
  -------------------
  https://wiki.seeedstudio.com/Seeeduino-XIAO/

  Click on File > Preference, and fill Additional Boards Manager URLs with the url below:
  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

  https://runawaybrainz.blogspot.com/2021/03/phat-stats-ssd1306-oled-hook-up-guide.html
*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include "bitmap.h"
#include "Configuration.h"

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



//------------------------------------ End of User configuration ---------------------------------
/* Seeeduino XIAO TX LED indicator,*/
#ifdef XIAO
#define TX_LEDPin 13
#endif

/*onboard QT-PY NeoPixel for TX*/
#ifdef QTPY
#define TX_NeoPin 11  //Built in NeoPixel, on the QT-PY
#else
#define TX_NeoPin 12  // Disable QT-PY built in Neopixel if you have a XIAO
#endif

/* Neo Pixel Setup */
#define NEOPIN         1
#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel TX_pixel(1, TX_NeoPin, NEO_GRB + NEO_KHZ800);

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

/*SSD1306 OLED setup*/
#ifdef OLED_SSD1306
#include <Adafruit_SSD1306.h> // i2C not SPI
#define SSD1306_128_64
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

#ifdef OLED_SH1106
#include <Adafruit_SH110X.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

#ifdef OLED_SH1106_SPI // Experimental
//https://learn.adafruit.com/adafruit-macropad-rp2040/arduino
#include <Adafruit_SH110X.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

/* ATSAMD21 SPi Hardware only for speed*/

#define OLED_MOSI     10
#define OLED_CLK      8
#define OLED_DC       7
#define OLED_CS       5
#define OLED_RST      9

#define SPi_bitrate 8000000

/* ATSAMD21 Bit Bang*/
// Create the OLED display
//Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &SPI1, OLED_DC, OLED_RST, OLED_CS);

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST , OLED_CS );
//Adafruit_SH1106G display (SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET , OLED_CS );

/* ATSAMD21 7 pin SPi Hardware for speed*/
//xx Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT,&SPI  ,OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET , OLED_CS, SPi_bitrate);
//xx Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI1 ,OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET , OLED_CS, SPi_bitrate);
//xx Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &SPI1, OLED_DC, OLED_RESET , OLED_CS);


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

  /* Set up PINs*/
#ifdef XIAO
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif

  /* OLED SETUP */
#ifdef OLED_SSD1306
  display.begin(SSD1306_SWITCHCAPVCC, i2c_Address); // initialize with the I2C addr 0x3D (for the 128x64
#endif

#ifdef OLED_SH1106
  display.begin(i2c_Address, true); // Address 0x3C default
#endif

#ifdef OLED_SH1106_SPi // Experimental
  // Start OLED
  display.begin(0, true); // we dont use the i2c address but we will reset!
  display.display();
#endif

  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setRotation(rotateScreen);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  display.clearDisplay();

  /* stops text wrapping*/
  display.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters

  /* Serial setup, start serial port at 9600 bps and wait for port to open:*/
  Serial.begin(baud); // 32u4 USB Serial Baud Rate
  inputString.reserve(200);

  /* Set up the NeoPixel*/
  pixels.begin(); // This initializes the NeoPixel library.

#ifdef QTPY
  TX_pixel.begin();  // This initializes the NeoPixel library.
#endif

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


#ifdef XIAO
  /*XIAO Serial Activity LED */
  digitalWrite(TX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
#endif

#ifdef QTPY
  /* QY-PY Serial Activity NeoPixel */
  TX_pixel.setPixelColor(0, 0, 0, 0 ); // turn built in NeoPixel Off
  TX_pixel.show();
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
      DisplayStyle1_NC();
    }
    else if (displayChangeMode == 2) {
      DisplayStyle2_NC ();
    }
    else if (displayChangeMode == 3) {
      DisplayStyle3_NC ();
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

//----------------  NeoPixel Reset ------------------

void allNeoPixelsOff() {
  for ( int i = 0; i < NUMPIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 0 );
  }
  //pixels.show();
}

//----------------  NeoPixels RGB  -------------------

void allNeoPixelsRED() {
  for ( int i = 0; i < NUMPIXELS; i++ ) {
    pixels.setPixelColor(i, 255, 0, 0 );
  }
  pixels.show();
}

void allNeoPixelsGREEN() {
  for ( int i = 0; i < NUMPIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 255, 0 );
  }
  pixels.show();
}

void allNeoPixelsBLUE() {
  for ( int i = 0; i < NUMPIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 255 );
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

      delay(Serial_eventDelay);   //delay screen event to stop screen data corruption

      //display.drawRect(82, 0, 44, 10, WHITE); // Position Test
      display.fillRect(115, 0, 42, 10, BLACK); // Flash top right corner when updating
      display.display();

#ifdef XIAO
      /* XIAO Serial Activity LED */
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif


#ifdef QTPY
      /* QT-PY Serial Activity NeoPixel */
      TX_pixel.setPixelColor(0, 0, 0, 10 ); // turn built in NeoPixel on
      TX_pixel.show();
#endif

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

#ifdef OLED_SH1106
  display.setTextColor(SH110X_WHITE);
#endif

#ifdef OLED_SH1106_SPI
  display.setTextColor(SH110X_WHITE);
#endif

#ifdef OLED_SH1106
  display.drawBitmap(0, 0, JustGnatBMP, 64, 64, SH110X_WHITE);
#else
  display.drawBitmap(0, 0, JustGnatBMP, 64, 64, WHITE);

#endif

#ifdef OLED_SH1106_SPI
  display.drawBitmap(0, 0, JustGnatBMP, 64, 64, SH110X_WHITE);
#else
  display.drawBitmap(0, 0, JustGnatBMP, 64, 64, WHITE);

#endif

  display.setTextSize(3);
  display.setCursor(58, 5);
  display.println("GNAT-");
  display.setTextSize(2);
  display.setCursor(64, 30);
  display.println("STATS");

  //Set version to USB Serial
  display.setTextSize(1);
  display.setCursor(66, 55);
  display.print("Ver: ");
  display.print (CODE_VERS);

  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();

  // USB Serial Screen

#ifdef OLED_SH1106
  display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, SH110X_WHITE);
#else
  display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, WHITE);
#endif

#ifdef OLED_SH1106_SPI
  display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, SH110X_WHITE);
#else
  display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, WHITE);
#endif

  display.display();
}
