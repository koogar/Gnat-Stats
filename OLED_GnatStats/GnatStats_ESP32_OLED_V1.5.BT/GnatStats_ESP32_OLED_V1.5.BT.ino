

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define device_BT "TallmanLabs_BT"
#define CODE_VERS  "1.5.BT"  // Code version number 
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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

  The application will not detect integrated graphics as a GPU!!!

    Version 1     : Initial release
    Version 1.1   : Fix intermittent screen flicker when in no activity mode "screen off" (due to inverter function?) fill the screen 128x64 black rectangle during this time.
	  Version 1.2   : Fix Freeze screen issue
    Version 1.2.1 : Top Config option to disable/enable positive/negative screen cycle

    Move to HardwareSerialMonitor (1.1) .Net 4.6.2

    Version 1.3   : Option to trigger an event at a given CPU or GPU threshold eg: LED indicator at 100% CPU Load.
                    Top Config option to disable all pre-selected power/gnd pins on Arduino pins D4 and D5 when not powering OLED from ProMicro
                    Top Config option to disable/enable "activitychecker" (Enable blank screen on serial timeout eg: PC powered down,
                    Disable to retain last sampled info eg: PC crash or overclocking diagnostics)

    Version 1.31   : MOVE CONFLICTING!!! NEOPIXEL PIN TO 10 (32u4)

    Version 1.32   : Add screen height/width definitions for updated Adafruit SSD1306 library
                   Clean up some code for clearing boxes not needed for OLED

    Version 1.33  : Add i2c Address change option
                    Add RotateScreen option
                    Add Neopixel Global Brightness

  Move to HardwareSerialMonitor(v1.3)

    Version 1.4   : Add Some HardwareSerialMonitor v1.3 Features

  Move to HardwareSerialMonitor(v1.4) Change Baud rate to 115200

    Version 1.5.BT  : Add Bluetooth serial support (ESP32 Only)
                    : Add option to manually Change the name of 
                      the CPU/GPU + GPU RAM size

                    : Change Baud rate to 115200

    ---------------------------------------------------------------


  ESP32 Core
  ----------------
  https://github.com/espressif/arduino-esp32


  This repo is available as a package usable with Arduino Boards Manager.
  Use this link in the "Additional Boards Managers URLs" field:
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

   _    ___ ___ ___    _   ___ ___ ___ ___
  | |  |_ _| _ ) _ \  /_\ | _ \_ _| __/ __|
  | |__ | || _ \   / / _ \|   /| || _|\__ \
  |____|___|___/_|_\/_/ \_\_|_\___|___|___/

  ESP32 Libraries
  -------------------------

  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit SSD1306 library
  https://github.com/adafruit/Adafruit_SSD1306

  SH1106 library :
  https://github.com/koogar/Adafruit_SH1106_ESP32

  Adafruit GFX Library
  https://github.com/adafruit/Adafruit-GFX-Library

  https://runawaybrainz.blogspot.com/2021/03/phat-stats-ssd1306-oled-hook-up-guide.html
  --------------------------------------------------------------------------------------

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
  ALWAYS RUN "HARDWARE SERIAL MONITOR" AS ADMIN!!!
*/


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include "bitmap.h"
#include "Configuration.h"

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!
#endif

BluetoothSerial SerialBT;    // Bluetooth Classic, not BLE


//------------------ End of User configuration --------------

/* TX LED indicator,*/
#ifdef enableTX_LED
#define TX_LEDPin 5
#endif

/* Neo Pixel Setup */
#define NEOPIN         2
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

//--------------------------------------------------------------

#define OLED_SDA 21   //SH1106
#define OLED_SCL 22   //SH1106

#define OLED_RESET -1 //"OLED_RESET" IS IS NOT A PHYSICAL PIN DO NOT CONNECT!!!

#define SSD1306_128_64
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

/*SSD1306 OLED setup*/
#ifdef OLED_SSD1306
#include <Adafruit_SSD1306.h> // i2C not SPI
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif


/*SH1106 OLED setup*/
#ifdef OLED_SH1106
#include <Adafruit_SH1106_ESP32.h> // i2C not SPI
Adafruit_SH1106_ESP32 display(OLED_SDA, OLED_SCL);
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
//int Serial_eventDelay = 15;
//int baud = 115200; //serial do not adjust

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

  // Start I2C Communication SDA = x and SCL = x on Wemos Lolin32 ESP32 with built-in SSD1306 OLED
  //Wire.begin(OLED_SDA, OLED_SCL); //SDD1306

#ifdef enable_BT
  SerialBT.begin(device_BT); //Bluetooth device name
#else //USB
  Serial.begin(baud);  //  USB Serial Baud Rate
#endif

#ifdef enable_DualSerialEvent
  SerialBT.begin(device_BT); //Bluetooth device name
#endif

  inputString.reserve(200);

  /* Set up PINs*/
#ifdef enableTX_LED
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif

  /* OLED SETUP */
#ifdef OLED_SSD1306
  display.begin(SSD1306_SWITCHCAPVCC, i2c_Address); // initialize with the I2C addr 0x3D (for the 128x64
  //display.begin(SSD1306_SWITCHCAPVCC, i2c_Address, false, false);
  //display.begin(SSD1306_SWITCHCAPVCC, i2c_Address, true, true);
#endif

#ifdef OLED_SH1106
  display.begin(SH1106_SWITCHCAPVCC, i2c_Address);  // initialize with the I2C addr 0x3D (for the 128x64)
#endif

  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setRotation(rotateScreen);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  display.clearDisplay();

  /* stops text wrapping*/
  display.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters

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

#ifdef enable_DualSerialEvent
  serialBTEvent();
#endif

  /*Serial stuff*/
#ifdef enable_BT
  serialBTEvent();
#else
  serialEvent();
#endif

#ifdef enableActivityChecker
  activityChecker();
#endif


#ifdef enableTX_LED
  /*Serial Activity LED */
  digitalWrite(TX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
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


//-------------------  Serial Events -----------------------

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

#ifdef enableTX_LED
      /*Serial Activity LED */
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif

    }
  }
}

//---------------------

void serialBTEvent() {

  while (SerialBT.available()) {          //  32u4 USB Serial Available?
    char inChar = (char)SerialBT.read();  // Read 32u4 USB Serial
    //Serial.print(inChar); // Debug Incoming Serial

    inputString += inChar;
    if (inChar == '|') {
      stringComplete = true;

      delay(Serial_eventDelay);   //delay screen event to stop screen data corruption

      //display.drawRect(82, 0, 44, 10, WHITE); // Position Test
      display.fillRect(115, 0, 42, 10, BLACK); // Flash top right corner when updating
      display.display();

#ifdef enableTX_LED
      /*Serial Activity LED */
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif

    }
  }
}

//-----------------------------------------------------

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

//------------ Anti Screen Burn inverter ---------------

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
  }
  display.invertDisplay(invertedStatus);
  display.display();
}

//----------------- Splash Screens -------------------
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
  display.setCursor(66, 55);
  display.print("Ver:");
  display.print (CODE_VERS);

  display.display();

#ifdef enableNeopixelGauges
#ifdef enable_BT
  allNeoPixelsBLUE();
#else
  allNeoPixelsRED();
#endif
#endif

#ifdef enable_DualSerialEvent
  allNeoPixelsGREEN();
#endif

  delay(3000);
  display.clearDisplay();
  display.display();
  allNeoPixelsOff();

  // USB Serial Screen
  //display.startscrollleft(0x00, 0x0F);

#ifdef enable_BT
  display.drawBitmap(0, 0, BT_WaitingDataBMP, 128, 64, WHITE);
#else
  display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, WHITE);
#endif

#ifdef enable_DualSerialEvent
  //display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, WHITE
#endif

  display.display();
}

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
