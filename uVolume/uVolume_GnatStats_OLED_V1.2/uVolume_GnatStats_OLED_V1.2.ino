
/*
      __      __   _
      \ \    / /  | |                               ____             _             ____  _        _
   _   \ \  / /__ | |_   _ _ __ ___   ___   ____   / ___|_ __   __ _| |_          / ___|| |_ __ _| |_ ___
  | | | \ \/ / _ \| | | | | '_ ` _ \ / _ \  ____  | |  _| '_ \ / _` | __|  _____  \___ \| __/ _` | __/ __|
  | |_| |\  / (_) | | |_| | | | | | |  __/        | |_| | | | | (_| | |_  |_____|  ___) | || (_| | |_\__ \
   \__, | \/ \___/|_|\__,_|_| |_| |_|\___|         \____|_| |_|\__,_|\__|         |____/ \__\__,_|\__|___/
      [ ]

  μVolume © - USB Media Control with GnatStats © - Tiny PC Performance Monitor - TallmanLabs.com
  Rupert Hirst & Colin Conway COPYRIGHT 2016

  Encoder     D8,9 (Button) D7
  Neopixel    D5
  IR Reciever D4
  OLED i2c    D2,3

  ASCII TXT:
  http://patorjk.com/software/taag/#p=display&f=Big&t=TallmanLabs

   "Hardware Serial Monitor" PC performance monitor windows application - Version xxx   Colin Conway & Rupert Hirst  2016

  Notes:

  I strongly suggest using this sketch with Atmel 32u4 based boards such as, the Leonardo or ProMicro, due to to its native USB support.

  The Windows "HardwareSerialMonitor" application uses the OpenHardwareMonitorLib.dll to detect the hardware.  http://openhardwaremonitor.org/
  The application will not detect "early" integrated graphics as a GPU!!!
  HardwareSerialMonitor does not like virtual Bluetooth COM ports present on the users PC!!!

  "Hardware Serial Monitor" is based on the Visual Studio project, kindly shared by psyrax see: https://github.com/psyrax/SerialMonitor

*/

/*
   _    ___ ___ ___    _   ___ ___ ___ ___
  | |  |_ _| _ ) _ \  /_\ | _ \_ _| __/ __|
  | |__ | || _ \   / / _ \|   /| || _|\__ \
  |____|___|___/_|_\/_/ \_\_|_\___|___|___/

  Adafruit Neopixel
  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit SSD1306 library
  https://github.com/adafruit/Adafruit_SSD1306

  Adafruit library ported to the SH1106
  https://github.com/badzz/Adafruit_SH1106      Currently used library in this sketch. Thanks Badzz!!!

  Others:
         https://github.com/wonho-maker/Adafruit_SH1106
         https://github.com/shondll/Adafruit_SSD1306

  Adafruit GFX Library
  https://github.com/adafruit/Adafruit-GFX-Library

  HID-Project
  https://github.com/NicoHood/HID/wiki/Consumer-API

  IRremote
  https://github.com/z3t0/Arduino-IRremote

  Rotary Encoder
  https://github.com/brianlow/Rotary
*/


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include "bitmap.h"
#include "HID-Project.h"  //https://github.com/NicoHood/HID/wiki/Consumer-API
#include <IRremote.h>


 /* ___ ___  _  _ ___ ___ ___ _   _ ___    _ _____ ___ ___  _  _
   / __/ _ \| \| | __|_ _/ __| | | | _ \  /_\_   _|_ _/ _ \| \| |
  | (_| (_) | .` | _| | | (_ | |_| |   / / _ \| |  | | (_) | .` |
   \___\___/|_|\_|_| |___\___|\___/|_|_\/_/ \_\_| |___\___/|_|\_|
     ___  ___ _____ ___ ___  _  _ ___
    / _ \| _ \_   _|_ _/ _ \| \| / __|
   | (_) |  _/ | |  | | (_) | .` \__ \
    \___/|_|   |_| |___\___/|_|\_|___/*/

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*Code version number*/
#define CODE_VERS  "1.2" // 
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/*Define correct OLED display type!!!*/
//#define OLED_SSD1306  // D3=SCL  D2=SDA
#define OLED_SH1106  // D3=SCL  D2=SDA

/*Remote code Selection*/
#define IR_BOSE        // Set Bose Remote Codes
//#define IR_AppleAlu    // Set Apple Aluminium Remote Codes
//#define IR_AppleWhite  // Set Apple White Remote Codes

/*Uncomment below, to use arduino pins to power the screen*/
//#define powerGND  // PULL D11 on the uVol PCB LOW

/* Disable Auto hardware ID to allow  manual CPU & GPU Naming*/
// change to prefered naming in DiplayStyles

//#define manual_CPUID
//#define manual_GPUID

/* Take out small degree symbol, for better spacing
   When hitting 100% CPU/GPU load the percent symbol gets clipped */
//#define noDegree

/* Option to disable IR to save Memory*/
//#define enableIR

/* Enable positive / negative  screens for anti screen burn*/
//#define screenSaverOn //

/* when enabled, auto extinguish's the neopixels with serial activity checker routine*/
#define enableAutoNeo

/* Uncomment below, to enable custom threshold event triggers*/
#define uVol_enableThesholdtriggers

/* Neo Pixel Setup */
int NeoBrightness = 50; // Atmel Global Brightness (does not work for STM32!!!!)

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


/*SH1106 OLED setup*/
#ifdef OLED_SH1106

#include <Adafruit_SH1106.h>
#define SH1106_128_64
#define OLED_RESET 12
Adafruit_SH1106 display(OLED_RESET);

#endif

/*SSD1306 OLED setup*/
#ifdef OLED_SSD1306

#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SSD1306_128_64
#define OLED_RESET 12
//Adafruit_SSD1306 display(OLED_RESET);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#endif

/*include Defined Remote Codes*/
#ifdef IR_AppleAlu
#include "AppleIRcodes.h"         // this is not a library its a local header Files (TAB)
#endif

#ifdef IR_AppleWhite
#include "AppleWhiteIRcodes.h"    // this is not a library its a local header Files (TAB)
#endif

#ifdef IR_BOSE
#include "BoseSoundDock1.h"       // this is not a library its a local header Files (TAB)
#endif


/*Rotary Encoder Setup
  It's also possible to use 'half-step' mode. This just emits an event at both the 0-0 and 1-1 positions.
  This might be useful for some encoders where you want to detect all positions.
  In rotary.h, uncomment  `#define HALF_STEP` to enable half-step mode.it codes twice per step. (speeds up Encoder)*/

#include <Rotary.h>       // Interrupt Example
Rotary r = Rotary(8, 9);  //Encoder A, Encoder B,   Encoder C to GND
int encoderSwitchPin = 7; //push button switch
//#define HALF_STEP


/*IR Mute LED */
int state = 0; // Keep track of mute, 0 = LED off while 1 = LED on

/*IR Setup */
int RECEIVE_PIN      = 4;    // InfraRed Signal Pin
IRrecv irrecv(RECEIVE_PIN);
decode_results results;


/*More OLED Stuff*/
int oledDraw = 0;
int oledOverride = 0;

/*Debounce timers for buttons - lastDebounceTime = millis();*/
long lastDebounceTime = 0;
long debounceDelay = 3000;

/*Inverted timers for oled*/
long invertDelay = 10000; // 60 sec  delay
long lastInvertTime = 0;
int invertedStatus = 0;

/*Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
#define lastActiveDelay 20000
boolean bootMode = true;

/*Neo Pixel Setup*/
#define NEOPIN         5  // Which pin is connected to the WS2812B NeoPixel?  uVol PCB use pin 5
#define NUMPIXELS      4
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

/*Predifined NeoPixel colours,  pixels.setPixelColor(0, BLUE);*/
#define BLUE       0x0000FF
#define GREEN      0x008000
#define RED        0xFF0000
#define BLACK      0x000000
#define YELLOW     0xFFFF00
#define DARKORANGE 0xFF8C00

/*vars for serial input*/
String inputString = "";
boolean stringComplete = false;

/*cycle screen DisplayStyles */
int displayChangeMode = 1;
long lastDisplayChange;
#define displayChangeDelay 18000  // Time between "DisplayStyle" changes

 /*___ ___ _____ _   _ ___
  / __| __|_   _| | | | _ \
  \__ \ _|  | | | |_| |  _/
  |___/___| |_|  \___/|_|*/

void setup() {

  /* PULL D11 on the uVol PCB LOW for OLED GND*/
#ifdef powerGND
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);   // GND
#endif

  Consumer.begin(); // Sends a clean report to the host. This is important on any Arduino type.
  //Keyboard.begin(); // Sends a clean report to the host. This is important on any Arduino type.

  r.begin(); // Start Rotary encoder

  pinMode(encoderSwitchPin, INPUT); // Encoder Button set as Input
  digitalWrite(encoderSwitchPin, HIGH); //Encoder Button, turn pullup resistor on


  /* OLED SETUP */
#ifdef OLED_SH1106
  display.begin(SH1106_SWITCHCAPVCC, 0x3c);    // initialize with the I2C addr 0x3D (for the 128x64)
#endif

#ifdef OLED_SSD1306
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); // initialize with the I2C addr 0x3D (for the 128x64)
#endif

  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setRotation(2);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  display.clearDisplay();

  /*Stops Text Wrapping*/
  display.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters


  /* Serial setup */
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  inputString.reserve(200);

  /* Set up the NeoPixel*/

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(NeoBrightness); // Global Brightness
  pixels.show(); // Turn off all Pixels


  pinMode(encoderSwitchPin, INPUT); // Encoder Button set as Input
  digitalWrite(encoderSwitchPin, HIGH); //Encoder Button, turn pullup resistor on
  irrecv.enableIRIn(); // Enable Infra Red

  /* Rotary Encoder Interrupt Stuff

    These registers support interrupts on Pro Micro
    pins 8, 9, 10 or 11.*/

  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT4) | (1 << PCINT5);
  sei();

  /*Initial Load screen*/
#ifdef enableIR
  splashScreenA();  //Uses Less RAM
#else
  splashScreenB();  //Uses more RAM
#endif

}
//END of Setup

/* __  __   _   ___ _  _   _    ___   ___  ___
  |  \/  | /_\ |_ _| \| | | |  / _ \ / _ \| _ \
  | |\/| |/ _ \ | || .` | | |_| (_) | (_) |  _/
  |_|  |_/_/ \_\___|_|\_| |____\___/ \___/|_|*/

void loop() {

  encoderbutton();
  //rotaryEncoder();  // Moved to end

#ifdef enableIR
  infraRed ();
#endif

  serialEvent();
  activityChecker();


  /*change display screen*/
  if ((millis() - lastDisplayChange) > displayChangeDelay)
  {
    if (displayChangeMode == 1) {
      displayChangeMode = 2;
      display.fillRect(0, 0, 128 , 64, BLACK);
    }
    else if (displayChangeMode == 2) {
      displayChangeMode = 1;
      display.fillRect(0, 0, 128 , 64, BLACK);
    }
    lastDisplayChange = millis();
  }

  /* OLED DRAW STATS */
  if (stringComplete) {

    if (bootMode) {
      //splashScreen2();
      //splashScreenA();

      display.invertDisplay(0);
      display.clearDisplay();
      display.display();

      bootMode = false;
    }
    //oledDrawBackground();
    lastActiveConn = millis();

    //............................................................................................................
    /*NeoPixel Idle colour*/
    neoBLUE();

    //............................................................................................................

    if (displayChangeMode == 1) {
      DisplayStyle1B();     
    }
    else if (displayChangeMode == 2) {
      DisplayStyle3 ();     
    }

    inputString = "";
    stringComplete = false;
  }
  //............................................................................................................

  /* Keep running anti screen burn, even if serial stops */
  if ((millis() - lastInvertTime) > invertDelay && oledDraw == 1) {
    lastInvertTime = millis();

#ifdef screenSaverOn
    inverter();
#endif

    rotaryEncoder();
  }
}

//END of Main Loop

/*
    __ _   _ _  _  ___ _____ ___ ___  _  _ ___
  | __| | | | \| |/ __|_   _|_ _/ _ \| \| / __|
  | _|| |_| | .` | (__  | |  | | (_) | .` \__ \
  |_|  \___/|_|\_|\___| |_| |___\___/|_|\_|___/

*/

//-------------------------------------------  Serial Events -------------------------------------------------------------

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();

    inputString += inChar;
    if (inChar == '|') {
      stringComplete = true;
          
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
    if (invertedStatus)

      //Turn off display when there is no activity
      display.invertDisplay(0);
    display.clearDisplay();
    display.display();

    display.fillRect(0, 0, 128, 64, BLACK);
    display.display();
    oledDraw = 0;
#ifdef enableAutoNeo
    //Turn off NeoPixel when there is no activity
    allNeoPixelsOff();
#endif
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

//--------------------------------------------- NeoPixel Colours --------------------------------------------------------
void allNeoPixelsOff() {
  for ( int i = 0; i < NUMPIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 0 );
  }
  pixels.show();
}

void neoRED() {

  pixels.setPixelColor(0, RED);
  pixels.setPixelColor(1, RED);
  pixels.setPixelColor(2, RED);
  pixels.setPixelColor(3, RED);
  pixels.show(); // This sends the updated pixel color to the hardware.

}

void neoBLUE() {

  pixels.setPixelColor(0, BLUE);
  pixels.setPixelColor(1, BLUE);
  pixels.setPixelColor(2, BLUE);
  pixels.setPixelColor(3, BLUE);
  pixels.show(); // This sends the updated pixel color to the hardware.

}


//--------------------------------------------- Splash Screens --------------------------------------------------------
void splashScreenB() {

  display.drawBitmap(0, 0, uVol2BMP, 64, 64, WHITE);
  display.setTextSize(1);
  display.setCursor(76, 5);
  display.println("uVolume");
  display.setTextSize(1);
  display.setCursor(72, 26);
  display.println("GnatStats");

  display.setTextSize(1);
  display.setCursor(72, 36);
  display.println("TMLabs");

  display.setTextSize(1);
  display.setCursor(72, 52);
  display.print("Ver:");
  display.print (CODE_VERS);

  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();

  display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, WHITE);
  display.display();
  display.clearDisplay();

  neoRED();
}


void splashScreenA () {
  display.drawBitmap(0, 0, uVolBMP, 64, 64, WHITE);
  display.setTextSize(1);
  display.setCursor(76, 5);
  display.println("uVolume");
  display.setTextSize(1);
  display.setCursor(72, 16);
  display.println("GnatStats");

  display.setTextSize(1);
  display.setCursor(72, 38);
  display.println("R.Hirst");

  display.setTextSize(1);
  display.setCursor(72, 52);
  display.print("Ver:");
  display.print (CODE_VERS);

  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();


  display.setTextSize(3); //set background txt font size
  display.setCursor(1, 1);
  display.println(">");
  display.display();
  display.setTextSize(2);
  display.setCursor(20, 30);
  display.display();
  display.println("0101010..");
  display.display();
  display.setTextSize(1);
  display.setCursor(1, 54);
  display.println("waiting for data.....");
  display.display();
  //delay(5000);
  display.clearDisplay();
  //display.display(); //note... not needed "main loop" will initiate this, when serial coms establish
  neoRED();

}

void splashScreen2() {
  display.drawBitmap(0, 0, uVolBMP, 64, 64, WHITE);
  display.setTextSize(1);
  display.setCursor(76, 5);
  display.println("uVolume");
  display.setTextSize(1);
  display.setCursor(72, 26);
  display.println("GnatStats");

  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
}


//--------------------------------------------------------------------------------------------------------
