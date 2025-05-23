#define CODE_VERS  "1.8.2.ADV"  // Code version number 


/*  uVolume, GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
  Rupert Hirst & Colin Conway © 2016-2023  Licence GPL v3

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

  Library Working Version Checker 18/04/2023
  (some libraries may not be used in this sketch)
  ------------------------------------------------
  Arduino IDE           v1.8.19
  espressif (ESP32)     v2.0.5 (v2.08 = ESP32_AnalogWrite compile error)
  ------------------------------------------------

  Adafruit BusIO           v1.14.0 (Current 04/2023
  Adafruit_GFX             v1.11.5 (Current 04/2023)
  Adafruit_NeoPixel        v1.11.0 (Current 04/2023)
  Adafruit_SSD1306         v2.5.7  (Current 04/2023)
  Adafruit_SH1106_BADZZ    v1.1.0  (32u4 only)(Current 04/2023)
  Adafruit SH110x          v2.1.8  (ATSAMD Only Current 04/2023)
  HID-Project              v2.8.2  (Current 04/2023)
  IRremote                 v2.7.0  (DO NOT USE IRremote LIBRARY HIGHER THAN v2.7.0 it breaks stats update)
  TML_ErriezRotaryFullStep v???    (Current 04/2023)

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  --------------------------------------------------------------------------------------

  ----------------------------------
  Pins Reference
  ----------------------------------

  QT-PY        : SDA: D4, SCL: D5
  OLED_RESET   : -1     Reference only!!
  NeoPixel     : 1
  Built in NeoPixel: 11 Reference only!!
  Button       : 0
  ---------------------
  XIAO Series  : SDA: D4, SCL: D5
  OLED_RESET   : -1  Reference only!!
  NeoPixel     : 1
  Built in LED : Board Specific!!
  Button       : 0
  ----------------------------------
  ESP32 LOLIN32: SDA: 21, SCL: 22
  OLED_RESET   : -1  Reference only!!
  NeoPixel     : 2 or 19
  Built in LED : 5   Reference only!!
  Button       : 0
  ----------------------------------
  uVolume      : SDA: D2, SCL: D3
  OLED_RESET   : 4  Reference only!!
  NeoPixel     : 5
  Button       : 7
  ----------------------------------
  ProMicro/Leo : SDA: D2, SCL: D3
  OLED_RESET   : 4  Reference only!!
  NeoPixel     : 10
  Button       : 7
  ----------------------------------
  STM32 BluePill: SDA: PB7, SCL: PB6
  OLED_RESET    : -1  Reference only!!
  NeoPixel      : PA7 (MOSI)
  Button        :
  ----------------------------------

  Onboard LED's
  -------------
  XIAO  (NRF52840) Built in LED      =  11     (*Not Required for Reference only!!!)
  XIAO  (RP2040)   Built in LED      =  25     (*Not Required for Reference only!!!)
  XIAO  (ATSAMD21) Built in LED      =  13     (*Not Required for Reference only!!!)
  QT-PY (ATSAMD21)(   None on the QT-PY   )

  QT-PY (ATSAMD21) Built in Neopixel =  11 or (12 to turn it off) (*Not Required for Reference only!!!)

  ALWAYS RUN "HARDWARE SERIAL MONITOR" AS ADMIN!!!*/
//--------------------------------------------------------------------------------------

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include "bitmap.h"
#include "Configuration.h"

/* Declare Prototype voids to the compiler */
void DisplayStyle1_OLED ();
void DisplayStyle2_OLED ();
void DisplayStyle3_OLED ();

void auto_Mode ();
void button_Mode ();

void serialEvent();
void activityChecker();

void splashScreen();
void inverter();
void antiBurn();

void refreshNeopixels ();
void allNeoPixelsRED  ();
void allNeoPixelsGREEN();
void allNeoPixelsBLUE ();
void allNeoPixelsOFF  ();

void CustomTriggerCPU_load(int cpuUsage );
void CustomTriggerCPU_temp(int cpuDegree);
void CustomTriggerGPU_load(int gpuUsage );
void CustomTriggerGPU_temp(int gpuDegree);

void CPU_loadGauge(int cpuUsage );
void CPU_tempGauge(int cpuDegree);
void GPU_loadGauge(int gpuUsage );
void GPU_tempGauge(int gpuDegree);

//--------------------------------------------------------------------------------------

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


#ifdef Seeeduino_XIAO_NRF52840
/*onboard XIAO BUILD in LED for TX*/
#define TX_LEDPin   11
#endif

#endif

/* Neo Pixel Setup */

#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Adafruit_QTPY_ATSAMD) ^ defined(Seeeduino_XIAO_NRF52840)
#define NEOPIN      6
#endif

#if defined(Seeeduino_XIAO_RP2040) ^ defined(Seeeduino_XIAO_ESP32C3)
#define NEOPIN     D6
#endif

#define NUMPIXELS  16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

#ifdef enableTX_LED
#ifdef Adafruit_QTPY_ATSAMD
Adafruit_NeoPixel TX_pixel(1, TX_NeoPin, NEO_GRB + NEO_KHZ800);
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

#ifdef OLED_SH110X

#include <Adafruit_SH110X.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//#define OLED_RESET   -1   //   QT-PY / XIAO

#ifdef Seeeduino_XIAO_NRF52840
#define OLED_RESET    4   //   QT-PY / XIAO
#else
#define OLED_RESET   -1   //   QT-PY / XIAO
#endif
/* Convert SSD1306 to SH1106  OLED Text/Fill/Draw Colours */
#define WHITE SH110X_WHITE
#define BLACK SH110X_BLACK
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#endif

#ifdef Robot_Eyes
#include <FluxGarage_RoboEyes.h>
roboEyes roboEyes; // create RoboEyes instance

#endif
//--------------------------------------------------------------------------------------

//----------------------
/* More OLED stuff*/
int oledDraw = 0;
int oledOverride = 0;
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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Inverted timers for oled*/
long lastInvertTime = 0;
int  invertedStatus = 0;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//--------------------------------------------------------------------------------------

// Button pin
int counter   = 0;

#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Adafruit_QTPY_ATSAMD) ^ defined(Seeeduino_XIAO_NRF52840)
int switchPin =  1; // MCU_PIN ____[--0--]___ GND
#endif

#if defined(Seeeduino_XIAO_RP2040) ^ defined(Seeeduino_XIAO_ESP32C3)
int switchPin = D1; // MCU_PIN ____[--0--]___ GND
#endif
//--------------------------------------------------------------------------------------


/* ___ ___ _____ _   _ ___
  / __| __|_   _| | | | _ \
  \__ \ _|  | | | |_| |  _/
  |___/___| |_|  \___/|_|*/


void setup() {

  pinMode(switchPin, INPUT_PULLUP);

  /* OLED SETUP */
#ifdef OLED_SSD1306
  display.begin(SSD1306_SWITCHCAPVCC, i2c_Address); // initialize with the I2C addr 0x3D (for the 128x64

#ifdef dim_Display
  display.dim (true);
#endif
#endif

#ifdef OLED_SH110X
  display.begin(i2c_Address, true); // Address 0x3C default
#endif

  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setRotation(flipScreen);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  display.clearDisplay();

  /* stops text wrapping*/
  display.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters

  /* Serial setup, start serial port at 9600 bps and wait for port to open:*/
  Serial.begin(baud); // 32u4 USB Serial Baud Rate
  inputString.reserve(200);

  /* Set up the NeoPixel*/
  pixels.begin(); // This initializes the NeoPixel library.

  /* Set up PINs*/
#ifdef enableTX_LED

#ifdef Seeeduino_XIAO_ATSAMD
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif

#ifdef Adafruit_QTPY_ATSAMD
  TX_pixel.begin();  // This initializes the library for the Built in NeoPixel.
#endif

#ifdef Seeeduino_XIAO_RP2040
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif

#ifdef Seeeduino_XIAO_NRF52840
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif

#endif




  //>>>>>>>>>>>>>>>>>>>>>>>>>>

#ifdef Robot_Eyes
  // Startup robo eyes
  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100); // screen-width, screen-height, max framerate

  // Define some automated eyes behaviour
  roboEyes.setAutoblinker(ON, 3, 2); // Start auto blinker animation cycle -> bool active, int interval, int variation -> turn on/off, set interval between each blink in full seconds, set range for random interval variation in full seconds
  roboEyes.setIdleMode(ON, 2, 2); // Start idle animation cycle (eyes looking in random directions) -> turn on/off, set interval between each eye repositioning in full seconds, set range for random time interval variation in full seconds
  //display.invertDisplay(true); // show inverted display colors (black eyes on bright background)
  // Define eye shapes, all values in pixels
  //roboEyes.setWidth(36, 36); // byte leftEye, byte rightEye
  //roboEyes.setHeight(36, 36); // byte leftEye, byte rightEye
  //roboEyes.setBorderradius(8, 8); // byte leftEye, byte rightEye
  //roboEyes.setSpacebetween(10); // int space -> can also be negative

  // Cyclops mode
  //roboEyes.setCyclops(ON); // bool on/off -> if turned on, robot has only on eye

  // Define mood, curiosity and position
  roboEyes.setMood(DEFAULT); // mood expressions, can be TIRED, ANGRY, HAPPY, DEFAULT
  //roboEyes.setPosition(DEFAULT); // cardinal directions, can be N, NE, E, SE, S, SW, W, NW, DEFAULT (default = horizontally and vertically centered)
  roboEyes.setCuriosity(ON); // bool on/off -> when turned on, height of the outer eyes increases when moving to the very left or very right

  // Set horizontal or vertical flickering
  //roboEyes.setHFlicker(ON, 2); // bool on/off, byte amplitude -> horizontal flicker: alternately displacing the eyes in the defined amplitude in pixels
  //roboEyes.setVFlicker(ON, 2); // bool on/off, byte amplitude -> vertical flicker: alternately displacing the eyes in the defined amplitude in pixels

  // Play prebuilt oneshot animations
  //roboEyes.anim_confused(); // confused - eyes shaking left and right
  //roboEyes.anim_laugh(); // laughing - eyes shaking up and down
  //>>>>>>>>>>>>>>>>>>>>>>>>>>
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

#ifdef enable_ActivityChecker
  /* Check for Serial Activity*/
  activityChecker();
#endif


#ifdef enable_buttonMode
  button_Mode();
#else
  auto_Mode();
#endif

  //=============================================================================

#ifdef enableTX_LED

#ifdef Seeeduino_XIAO_ATSAMD
  /*Serial Activity LED */
  digitalWrite(TX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
#endif

#ifdef Seeeduino_XIAO_RP2040
  /*Serial Activity LED */
  digitalWrite(TX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
#endif

#ifdef Adafruit_QTPY_ATSAMD
  /* Serial Activity NeoPixel */
  TX_pixel.setPixelColor(0, 0, 0, 0 ); // turn built in NeoPixel Off
  TX_pixel.show();
#endif

#ifdef Seeeduino_XIAO_NRF52840
  /*Serial Activity LED */
  pinMode(TX_LEDPin, HIGH); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif
#endif

  //=============================================================================
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

void allNeoPixelsOFF() {
  for ( int i = 0; i < NUMPIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 0 );
  }

  //pixels.show();
  pixels.clear();
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
      //display.fillCircle(115, 4, 4,WHITE); // Flash top right corner when updating

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
#ifdef Adafruit_QTPY_ATSAMD
      TX_pixel.setPixelColor(0, 10, 0, 0 ); // turn built in NeoPixel on
      TX_pixel.show();
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
    //!!!!!Careful of extra auto insertion "}" above here compile will fail!!!!!
#ifdef enable_Invertscreen

    if (invertedStatus)
      display.invertDisplay(0);
#endif

#ifdef display_Standby
    //Turn off display when there is no activity
    display.clearDisplay();
    display.display();

    //Experimental,  attempt to stop intermittent screen flicker when in no activity mode "screen off" (due to inverter function ? ) fill the screen 128x64 black rectangle
    display.fillRect(0, 0, 128, 64, BLACK);
    display.display();
    oledDraw = 0;
#endif

#ifdef Robot_Eyes
    roboEyes.update(); // update eyes drawings
#endif

    //Turn off NeoPixel when there is no activity
    allNeoPixelsOff();
    pixels.show();
  }
}

//-------------------------------------------- Anti Screen Burn inverter ------------------------------------------------

#ifdef enable_Invertscreen
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

  display.setTextColor(WHITE);

  display.drawBitmap(0, 0, JustGnatBMP, 64, 64, WHITE);

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

  display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, WHITE);

  display.display();
}
