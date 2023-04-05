
/*
    ____             _             ____  _        _
   / ___|_ __   __ _| |_          / ___|| |_ __ _| |_ ___
  | |  _| '_ \ / _` | __|  _____  \___ \| __/ _` | __/ __|
  | |_| | | | | (_| | |_  |_____|  ___) | || (_| | |_\__ \
   \____|_| |_|\__,_|\__|         |____/ \__\__,_|\__|___/


  GNAT STATS PC performance monitor - Version xxx   Rupert Hirst & Colin Conway 2016

  Bitmap conversion code http://javl.github.io/image2cpp/

  Notes:
  I strongly suggest using this sketch with Atmel 32u4 based boards such as, the Leonardo or ProMicro.
  The serialmonitor windows application will not detect "early" integrated graphics as a GPU!

  Visual Studio project source code, kindly shared by psyrax see: https://github.com/psyrax/SerialMonitor

  ProMicro hookup:

  NeoPixel DataIn: D15 with 220r series resistor

  Adafruit library ported to the SH1106
  https://github.com/wonho-maker/Adafruit_SH1106
  https://github.com/shondll/Adafruit_SSD1306

*/


#include <Wire.h>
#include <Adafruit_GFX.h>


#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include "bitmap.h"


/* OLED setup*/
#define SSD1306_128_64
#define OLED_RESET -1


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
/* More OLED stuff*/
int oledDraw = 0;
int oledOverride = 0;


/* Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
#define lastActiveDelay 20000
boolean bootMode = true;

//----------------------
/* Time between "DisplayStyle" changes */
#define displayChangeDelay 18000

/* Start DisplayStyle */
int displayChangeMode = 1;
long lastDisplayChange;
//----------------------


/* Neo Pixel Setup */
#define NEOPIN         6
#define NUMPIXELS      4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

/* Pre-define NeoPixel colours,  eg. pixels.setPixelColor(0, BLUE);*/
#define BLUE      0x0000FF
#define GREEN     0x008000
#define RED       0xFF0000
#define BLACK     0x000000 // OFF

// Button pin
int counter = 0;
int switchPin = 1;

/*vars for serial input*/
String inputString = "";
boolean stringComplete = false;


//--------------- Manual CPU/GPU Display Name Entry -------------------------

/* Characters to delete from the start of the auto detected CPU/GPU name eg: Remove "Intel" or "Nvidia" to save space*/

#define cpuNameStartLength 10
#define gpuNameStartLength 18

/* Manually set the CPU, GPU details*/

//#define Manual_cpuName
String set_CPUname = "xxxxxxx";

//#define Manual_gpuName
String set_GPUname = "xxxxxxx";

//#define Manual_gpuRam size in GB
String set_GPUram = "xx";

//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

void setup() {
  /* Serial setup, start serial port at 9600 bps and wait for port to open:*/
  Serial.begin(9600);
  inputString.reserve(200);

  pinMode(switchPin, INPUT_PULLUP);


  /* OLED SETUP */
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setRotation(2);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  display.clearDisplay();

  /* stops text wrapping*/
  display.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters




  /* Set up the NeoPixel*/
  //pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(100); // Global Brightness
  pixels.show(); // Turn off all Pixels

  /* Set up the NeoPixel Strip* /
    strip.begin();
    strip.setBrightness(25); // Global Brightness
    strip.show(); // Initialize all pixels to 'off'


    /*Initial Load screen*/
  //splashScreenA();   //Uses more memory
  //splashScreenB();  //Uses less memory
  //splashScreenC();    //Uses less memory
  splashScreenD();  //Uses least memory

}


//--------------------------------------------------


void loop() {

  buttonMode ();
  //autoMode ();
}

//END of Main Loop



//--------------------------------------------------------------------------------------------------------

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '|') {
      stringComplete = true;

      //display.drawRect(68, 54, 58, 10, WHITE); // Flash bottom right corner when updating
      display.fillRect(68, 54, 58, 10, BLACK); // Flash bottom right corner when updating
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
    //if (invertedStatus)
    // display.invertDisplay(0);
    display.clearDisplay();
    display.display();

  }
}
