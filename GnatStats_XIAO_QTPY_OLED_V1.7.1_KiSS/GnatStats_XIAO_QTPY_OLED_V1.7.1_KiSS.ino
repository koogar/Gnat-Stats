#define CODE_VERS  "1.7.1.KiSS"  // Code version number 

/*
  uVolume, GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
   Rupert Hirst © 2016-2023

   http://tallmanlabs.com  http://runawaybrainz.blogspot.com/
   https://github.com/koogar/Gnat-Stats  https://hackaday.io/project/181320-gnat-stats-tiny-oled-pc-performance-monitor


  Libraries
  ---------
  Adafruit Neopixel
  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit SSD1306 library
  https://github.com/adafruit/Adafruit_SSD1306

  SH1106 Library
  https://github.com/adafruit/Adafruit_SH110x

  Adafruit GFX Library
  https://github.com/adafruit/Adafruit-GFX-Library // latest version is required for SH1106 Support
  https://github.com/adafruit/Adafruit_BusIO       // latest version is required for SH1106 Support



  Board Manager QY-PY ATSAMD
  --------------------------
  Click on File > Preference, and fill Additional Boards Manager URLs with the url below:

  Install Arduino ATSAMD then ADD
  https://adafruit.github.io/arduino-board-index/package_adafruit_index.json



  Board Manager XIAO Series
  --------------------------
  https://wiki.seeedstudio.com/Seeeduino-XIAO/


  Click on File > Preference, and fill Additional Boards Manager URLs with the url below:

  XIAO ATSAMD21
  -------------
  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

  XIAO NRF52840
  -------------
  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

  XIAO RP2040
  -----------
  https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

  XIAO ESP32C3
  ------------
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json



  Hookup Guide
  ------------
  https://runawaybrainz.blogspot.com/2021/03/phat-stats-ssd1306-oled-hook-up-guide.html

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
               SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

*/
#include <SPI.h>
#include <Wire.h>

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
  NeoPixel     : D1
  Built in NeoPixel: 11 Reference only!!
  OLED_RESET   : -1     Reference only!!
  ---------------------
  XIAO Series  : SDA: D4, SCL: D5
  NeoPixel     : D1
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


  Onboard LED's
  -------------
  XIAO  (NRF52840) Built in LED      =  11     (*Not Required for Reference only!!!)
  XIAO  (RP2040)   Built in LED      =  25     (*Not Required for Reference only!!!)
  XIAO  (ATSAMD21) Built in LED      =  13     (*Not Required for Reference only!!!)
  QT-PY (ATSAMD21) Built in LED      =         (None on the QT-PY)

  QT-PY (ATSAMD21) Built in Neopixel =  11 or (12 to turn it off) (*Not Required for Reference only!!!)

*/



/* Seeeduino XIAO TX LED indicator,*/
#ifdef enableTX_LED

#ifdef Seeeduino_XIAO_ATSAMD
#define TX_LEDPin 13
#endif

/*onboard QT-PY NeoPixel for TX*/
#ifdef Adafruit_QTPY_ATSAMD
#define TX_NeoPin 11  //Built in NeoPixel, on the QT-PY
#else
#define TX_NeoPin 12  // Disable QT-PY built in Neopixel if you have a XIAO
#endif

#ifdef Seeeduino_XIAO_RP2040
/*onboard XIAO BUILD in LED for TX*/
#define TX_LEDPin   25
#endif

#ifdef Adafruit_QTPY_ATSAMD
/*onboard QT-PY NeoPixel for TX*/
#define TX_NeoPin   11  //
#endif

#ifdef Seeeduino_XIAO_NRF52840
/*onboard XIAO BUILD in LED for TX*/
#define TX_LEDPin   11
#endif

#endif



//--------------------------------------------------------------------------------------

/*SSD1306 OLED setup*/
#ifdef OLED_SSD1306
#include <Adafruit_SSD1306.h> // i2C not SPI
#define SSD1306_128_64
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1   //   QT-PY / XIAO
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

#ifdef OLED_SH1106
#include <Adafruit_SH110X.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1   //   QT-PY / XIAO

#ifdef Seeeduino_XIAO_NRF52840
#define OLED_RESET    4   //   QT-PY / XIAO
#endif

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>> Moved from Config settings >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* Uncomment below, to enable positive and negative screen cycler */
//#define enableInvertscreen

/* Uncomment below, to take out small degree symbol for better spacing
   when hitting 100% cpu/gpu load the percent symbol gets clipped */
//#define noDegree


/* Time between "DisplayStyle" changes */
#define displayChangeDelay 18000

/* Enable the built in LED blinking when transmitting data,*/
#define enableTX_LED
int TX_LED_Delay = 100; // TX blink delay


/* Timer for active connection to host*/
#define lastActiveDelay 6000

/* comment out, to disable blank screen on serial timeout to retain info eg: PC crash fault diagnostics  */
#define enableActivityChecker

/* Delay screen event, to help stop screen data corruption ESP8622 use 25, most others 5 will do*/

int Serial_eventDelay = 15;
int baud = 9600; //serial do not adjust

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

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




  /* OLED SETUP */
#ifdef OLED_SSD1306
  display.begin(SSD1306_SWITCHCAPVCC, i2c_Address); // initialize with the I2C addr 0x3D (for the 128x64

#ifdef dim_Display
  display.dim (true);
#endif
#endif

#ifdef OLED_SH1106
  display.begin(i2c_Address, true); // Address 0x3C default
#ifdef dim_Display
  //display.dim (true);
#endif
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



  /* Set up PINs*/
#ifdef enableTX_LED

#ifdef Seeeduino_XIAO_ATSAMD
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif


#ifdef Seeeduino_XIAO_RP2040
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif

#ifdef Seeeduino_XIAO_NRF52840
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif

#endif

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

#ifdef enableTX_LED

#ifdef Seeeduino_XIAO_ATSAMD
  /*Serial Activity LED */
  digitalWrite(TX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
#endif

#ifdef Seeeduino_XIAO_RP2040
  /*Serial Activity LED */
  digitalWrite(TX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
#endif


#ifdef Seeeduino_XIAO_NRF52840
  /*Serial Activity LED */
  pinMode(TX_LEDPin, HIGH); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif
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

#ifdef enableTX_LED

      /* Serial Activity LED */
#ifdef Seeeduino_XIAO_ATSAMD
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif
#endif

#ifdef Seeeduino_XIAO_RP2040
#ifdef enableTX_LED
      //USER LED GREEN
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif
#endif



#ifdef enableTX_LED
      /* Serial Activity LED */
#ifdef Seeeduino_XIAO_NRF52840
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif
#endif

      delay(TX_LED_Delay); // TX blink delay

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


#ifdef OLED_SH1106
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
  display.setCursor(66, 47);
  //display.print("Baud: ");
  display.print (baud); display.println(".bit/s");

  //Set version to USB Serial
  display.setTextSize(1);
  display.setCursor(66, 56);
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

  display.display();
}
