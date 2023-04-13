
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

#define CODE_VERS  "1.6.4.But"  // Code version number 
#include <Wire.h>
#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include "bitmap.h"

//--------------------- OLED Setup --------------------------

/*---------------- SSD1306 -------------*/
#define OLED_SSD1306
//#define dim_Display // dim display SD1306 Only!!!

/*---------------- SH1106 --------------*/
//#define OLED_SH1106

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
#define OLED_RESET    -1 //-1   //   QT-PY / XIAO
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

#ifdef OLED_SH1106
#include <Adafruit_SH110X.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 //-1   //   QT-PY / XIAO

#ifdef Seeeduino_XIAO_NRF52840
#define OLED_RESET    4   //   QT-PY / XIAO
#endif

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#endif

/* Neo Pixel Setup */
#define NEOPIN         6//5//6// uVolume D5
#define NUMPIXELS      4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

/* Pre-define NeoPixel colours,  eg. pixels.setPixelColor(0, BLUE);*/
#define BLUE      0x0000FF
#define GREEN     0x008000
#define RED       0xFF0000
#define BLACK     0x000000 // OFF

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

/* More OLED stuff*/
int oledDraw = 0;
int oledOverride = 0;


/* Timer for active connection to host*/
#define lastActiveDelay 6000

boolean activeConn = false;
long lastActiveConn = 0;
boolean bootMode = true;

//----------------------
/* Time between "DisplayStyle" changes */
#define displayChangeDelay 18000

/* Start DisplayStyle */
int displayChangeMode = 1; 
long lastDisplayChange;
//----------------------

/* Enable button to change screens else use auto timer change*/
#define enable_buttonMode
int deBounce = 350;
// Button pin
int counter   = 0;
int switchPin = 1; // MCU_PIN ____[--0--]___ GND // uVolume D7


/*vars for serial input*/
int baud = 9600;
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


//>>>>>>>>     Start of Setup     <<<<<<<<<<<<<

void setup() {
  /* Serial setup, start serial port at 9600 bps and wait for port to open:*/
  Serial.begin(9600);
  inputString.reserve(200);

  pinMode(switchPin, INPUT_PULLUP);

  //pinMode(switchPin, INPUT);
  //digitalWrite(switchPin, HIGH);


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
