
#define CODE_VERS  "1.71.Robo"  // Code version number

/*

   uVolume, GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
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

  RoboEyes Library
  ---------------
  https://github.com/FluxGarage/RoboEyes


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
  SEE SETUP TAB FIRST, FOR QUICK SETTINGS!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "bitmap.h"
#include "Setup.h"




/* Declare Prototype voids to the compiler*/
void DisplayStyle1_NC ();
void DisplayStyle2_NC ();
void DisplayStyle3_NC ();
void autoMode ();
void buttonMode ();
void inverter();
void serialEvent();
void activityChecker();
void splashScreen();
void antiBurn();

//>>>>>>>>>>>>>>>>>>>>>>>>>>>
//--------------------- Set i2c OLED address  --------------------------
/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's


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
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#endif

#include <FluxGarage_RoboEyes.h>
roboEyes roboEyes; // create RoboEyes instance

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* More OLED stuff*/
int oledDraw = 0;
int oledOverride = 0;

/* Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
//#define lastActiveDelay 30000
boolean bootMode = true;

/*vars for serial input*/
String inputString = "";
boolean stringComplete = false;


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Inverted timers for oled*/
long invertDelay    = 10000;
long lastInvertTime = 0;
int invertedStatus  = 0;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>

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

#endif
#endif


  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setRotation(rotateScreen);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  display.clearDisplay();

  /* stops text wrapping*/
  display.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters

  /* Serial setup, start serial port at 9600 bps and wait for port to open:*/
  Serial.begin(9600); // 32u4 USB Serial Baud Rate
  inputString.reserve(200);


  /*Initial Load screen*/
  splashScreen();

  //>>>>>>>>>>>>>>>>>>>>>>>>>>
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



}


//>>>>>>>>>>>>>>>>>>>>>>>>>>> END of Setup >>>>>>>>>>>>>>>>>>>>>>>>>

void loop() {

  /*Serial stuff*/
  serialEvent();
  activityChecker();

  //>>>>>>>>>>>>>>>>>>>>>>>>>>

  /* OLED DRAW STATS */
  if (stringComplete) {

    if (bootMode) {

      //splashScreen2();
      display.clearDisplay();
      display.display();

      bootMode = false;
    }

    lastActiveConn = millis();

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /* DRAW STATS Function */
    DisplayStyle1_NC ();
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    inputString = "";
    stringComplete = false;

#ifdef enableInvertscreen
    /* Keep running anti screen burn, whilst serial is active */
    if ((millis() - lastInvertTime) > invertDelay && oledDraw == 1) {
      lastInvertTime = millis();


      /* Anti Screen Burn */
      inverter();

#else

    if (oledDraw == 1 && !serialEvent) {
      // Keep running function continuously

#endif

    }
  }
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>END of Main Loop>>>>>>>>>>>>>>>>>>>>>>>>>


/*
    __ _   _ _  _  ___ _____ ___ ___  _  _ ___
  | __| | | | \| |/ __|_   _|_ _/ _ \| \| / __|
  | _|| |_| | .` | (__  | |  | | (_) | .` \__ \
  |_|  \___/|_|\_|\___| |_| |___\___/|_|\_|___/

*/


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
#ifdef enableInvertscreen
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
  display.print (baud); display.println(".bit/s");

  //Set version to USB Serial
  display.setTextSize(1);
  display.setCursor(66, 56);
  display.print("V:");
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
