
#define CODE_VERS  "1.6.4.But"  // Code version number

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
#include <Adafruit_NeoPixel.h>
#include "bitmap.h"
#include "Configuration.h"

//--------------------- OLED Setup --------------------------
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
#define OLED_RESET     4   //   QT-PY / XIAO
#endif

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#endif

//-------------------------------------------------------------------

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
//-------------------------------------------------------------------
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

/* Pre-define Hex NeoPixel colours,  eg. pixels.setPixelColor(0, BLUE); https://htmlcolorcodes.com/color-names/ */
#define BLUE       0x0000FF
#define GREEN      0x008000
#define RED        0xFF0000
#define ORANGE     0xFFA500
#define DARKORANGE 0xFF8C00
#define YELLOW     0xFFFF00
#define WHITE      0xFFFFFF
#define BLACK      0x000000 // OFF


/* Declare Prototype voids to the compiler*/
void DisplayStyle1_OLED();
void DisplayStyle2_OLED();
void DisplayStyle3_OLED();
void auto_Mode();
void button_Modes();
void inverter();
void serialEvent();
void activityChecker();
void splashScreen();
void antiBurn();

//--------------------
/* More OLED stuff*/
int oledDraw = 0;
int oledOverride = 0;

/* Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
boolean bootMode = true;

//----------------------
/* auto_Mode "DisplayStyle" changes */
int displayChangeMode = 1;
long lastDisplayChange;
//----------------------

// button_Modes
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



//>>>>>>>>     Start of Setup     <<<<<<<<<<<<<

void setup() {
  /* Serial setup, start serial port at 9600 bps and wait for port to open:*/
  Serial.begin(baud);
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


  pixels.setBrightness(neoBrightness); // Global Brightness
  pixels.show(); // Turn off all Pixels



  /*Initial Load screen*/
  splashScreen();

}
//>>>>>>>>     End of Setup     <<<<<<<<<<<<<


//>>>>>>>>  Start of Main Loop  <<<<<<<<<<<<<

void loop() {

  /* Serial stuff*/
  serialEvent();

#ifdef enableActivityChecker
  /* Check for Serial Activity*/
  activityChecker();
#endif


#ifdef enable_buttonMode
  button_Modes ();
#else
  auto_Mode ();
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
