
#define CODE_VERS  "1.6.4.But"  // Code version number 


/* uVolume, GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
  Rupert Hirst & Colin Conway © 2016-2023

  http://tallmanlabs.com  http://runawaybrainz.blogspot.com/
  https://github.com/koogar/Gnat-Stats  https://hackaday.io/project/181320-gnat-stats-tiny-oled-pc-performance-monitor


  Libraries
  -------- -
  Adafruit Neopixel
  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit SSD1306 library
  https://github.com/adafruit/Adafruit_SSD1306

  SH1106 Library
  https://github.com/adafruit/Adafruit_SH110x

  Adafruit GFX Library
  https://github.com/adafruit/Adafruit-GFX-Library // latest version is required for SH1106 Support
  https://github.com/adafruit/Adafruit_BusIO       // latest version is required for SH1106 Support


  Board Manager QY - PY ATSAMD
  --------------------------
  Click on File > Preference, and fill Additional Boards Manager URLs with the url below:

  Install Arduino ATSAMD then ADD
  https://adafruit.github.io/arduino-board-index/package_adafruit_index.json


  Board Manager XIAO Series
  --------------------------
  https://wiki.seeedstudio.com/Seeeduino-XIAO/


  Click on File > Preference, and fill Additional Boards Manager URLs with the url below:

  XIAO ATSAMD21
  ------------ -
  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

  XIAO NRF52840
  ------------ -
  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

  XIAO RP2040
  ---------- -
  https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

  XIAO ESP32C3
  ------------
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json


  Hookup Guide
  ------------
  https://runawaybrainz.blogspot.com/2021/03/phat-stats-ssd1306-oled-hook-up-guide.html

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include "bitmap.h"
#include "Configuration.h"

//--------------------- OLED Setup --------------------------

/* SSD1306 OLED setup */
#ifdef OLED_SSD1306
#include <Adafruit_SSD1306.h> // i2C not SPI
#define SSD1306_128_64
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // QT-PY / XIAO
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif



//----------------------------------------------------------

/* Neo Pixel Setup */
#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Adafruit_QTPY_ATSAMD) ^ defined(Seeeduino_XIAO_NRF52840)
#define NEOPIN      6
#endif

#if defined(Seeeduino_XIAO_RP2040) ^ defined(Seeeduino_XIAO_ESP32C3)
#define NEOPIN     D6
#endif

#define NUMPIXELS      4
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

/* Pre-define NeoPixel colours,  eg. pixels.setPixelColor(0, BLUE);*/
#define BLUE      0x0000FF
#define GREEN     0x008000
#define RED       0xFF0000
#define BLACK     0x000000 // OFF


/* More OLED stuff*/
int oledDraw = 0;
int oledOverride = 0;

/* Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
boolean bootMode = true;

//----------------------
/* Time between "DisplayStyle" changes */

int displayChangeMode = 1;
long lastDisplayChange;
//----------------------


// Button pin
int counter   = 0;
int switchPin = 1; // MCU_PIN ____[--0--]___ GND // uVolume D7


/*vars for serial input*/
String inputString = "";
boolean stringComplete = false;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Anti Screen Burn */
//#define enableInvertscreen // Currently only works in autoMode

/* Inverted timers for oled*/
long invertDelay    = 1000;
long lastInvertTime = 0;
int  invertedStatus = 0;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* Declare Prototype voids to the compiler*/
void DisplayStyle1 ();
void DisplayStyle2 ();
void DisplayStyle3 ();
void autoMode ();
void buttonMode ();
void inverter();
void serialEvent();
void activityChecker();
void splashScreen();
void antiBurn();

//>>>>>>>>     Start of Setup     <<<<<<<<<<<<<

void setup() {

  /* Serial setup, start serial port at 9600 bps and wait for port to open:*/
  Serial.begin(baudRate);
  inputString.reserve(200);

  pinMode(switchPin, INPUT_PULLUP);


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

#ifdef OLED_SH1106
  display.setTextColor(SH110X_WHITE);
#else
  display.setTextColor(WHITE);
#endif

  display.setRotation(rotateScreen);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  display.clearDisplay();

  /* stops text wrapping*/
  display.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters


  /* Set up the NeoPixel*/
  //pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(neoBrightness); // Global Brightness
  pixels.show();    // Turn off all Pixels


  /*Initial Load screen*/
  splashScreen();

}
//>>>>>>>>     End of Setup     <<<<<<<<<<<<<


//>>>>>>>>  Start of Main Loop  <<<<<<<<<<<<<

void loop() {

  /* Serial stuff*/
  serialEvent();
  /* Check for Serial Activity*/
  activityChecker();

#ifdef enable_buttonMode
  buttonMode ();
#else
  autoMode ();
#endif

}

//>>>>>>>>  END of Main Loop  <<<<<<<<<<<<<


//>>>>>>>>    Functions    <<<<<<<<<<<<<

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
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

#ifdef enableInvertscreen
    if (invertedStatus)
      display.invertDisplay(0);
#endif

    display.clearDisplay();
    display.display();

  }
}

//-------------------------------------------- Anti Screen Burn inverter ------------------------------------------------
#ifdef enableInvertscreen
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
#endif

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
  display.print (baudRate); display.println(".bit/s");

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
