/*
   _____ __  __ _         _            ___           _   ___ _        _
  |_   _|  \/  | |   __ _| |__ ______ / __|_ _  __ _| |_/ __| |_ __ _| |_ ___
    | | | |\/| | |__/ _` | '_ (_-<___| (_ | ' \/ _` |  _\__ \  _/ _` |  _(_-<
    |_| |_|  |_|____\__,_|_.__/__/    \___|_||_\__,_|\__|___/\__\__,_|\__/__/

  GNATSTATS PC Performance Monitor - Version 1.x  Rupert Hirst & Colin Conway © 2016
  http://tallmanlabs.com  & http://runawaybrainz.blogspot.com/

  Licence
  -------

  Attribution-NonCommercial-ShareAlike  CC BY-NC-SA

  This license lets others remix, tweak, and build upon your work non-commercially, as long as they credit you and license their new creations under the identical terms.

  https://creativecommons.org/licenses/



  Notes:

  UNO/NANO are not supported!!! use this sketch with Atmel 32u4 based boards such as, the Leonardo or ProMicro, due to to its native USB support.

  The Windows application "HardwareSerialMonitor v1.1"  uses the OpenHardwaremonitor  OpenHardwareMonitorLib.dll to detect the hardware.  http://openhardwaremonitor.org/

  The application will not detect integrated graphics as a GPU!!!
  Presently HardwareSerialMonitor does not like virtual Bluetooth COM ports present on the users PC!!!

  "Hardware Serial Monitor" Was inspired by the Visual Studio project kindly shared by psyrax see: https://github.com/psyrax/SerialMonitor
  ALWAYS RUN "HARDWARE SERIAL MONITOR" AS ADMIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  ProMicro hookup:
  ----------------
  NeoPixel DataIn: D15 with 220r series resistor

  SSD1306 OLED Hookup:

  18.6mA on a fully lit 0.96" i2C OLED display, pull pin D5 High(5v) and D4 Low(to ground) on the ProMicro to providing the necessary  VCC / GND for the display.
  18mA is within the Atmel 32u4 maximum pin current limit of 20mA. This allows the display to be simply soldered straight to the header of the ProMicro.
  With different screens sizes and chipsets your mileage will vary, do your own tests!
  The 1.3" i2c OLED uses upward of 34mA, which is too much a I/O pin alone !!!

  Warning!!!! Please check you have the correct polarity for the selected OLED screen
    -------------------------------------------------------------
    0.96" i2C OLED:    VCC         GND          SCL        SDA

    ProMicro Pins:     D5(HIGH)    D4(LOW)      D3         D2
    -------------------------------------------------------------

    Version 1     : Initial release
    Version 1.1   : Fix intermittent screen flicker when in no activity mode "screen off" (due to inverter function?) fill the screen 128x64 black rectangle during this time.
	  Version 1.2   : Fix Freeze screen issue
    Version 1.2.1 : Top Config option to disable/enable positive/negative screen cycle

    Move HSMonitor(v1.1) to .Net 4.6.2
    Version 1.3   : Option to trigger an event at a given CPU or GPU threshold eg: LED indicator at 100% CPU Load.
                    Top Config option to disable all pre-selected power/gnd pins on Arduino pins D4 and D5 when not powering OLED from ProMicro
                    Top Config option to disable/enable "activitychecker" (Enable blank screen on serial timeout eg: PC powered down,
                    Disable to retain last sampled info eg: PC crash or overclocking diagnostics)

    Version 1.31   : MOVE CONFLICTING!!! NEOPIXEL PIN TO 10

    Version 1.32 : Add screen height/width definitions for updated Adafruit SSD1306 library
                   Clean up some code for clearing boxes not needed for OLED

    ---------------------------------------------------------------

    Arduino UNO/NANO/MINI ETC. (Atmel ATMega 328 Chips) are not supported, Please don't ask!!!

         ToDo:
         Windows custom GnatStats device icon
         Auto or button screen change option,
         PC Diagnostic switch / mode eg: Min / Max readings,
         Analogue Panel Meter Readings output



  ASCII: http://patorjk.com/software/taag/

   _    ___ ___ ___    _   ___ ___ ___ ___
  | |  |_ _| _ ) _ \  /_\ | _ \_ _| __/ __|
  | |__ | || _ \   / / _ \|   /| || _|\__ \
  |____|___|___/_|_\/_/ \_\_|_\___|___|___/

  Adafruit Neopixel
  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit SSD1306 library
  https://github.com/adafruit/Adafruit_SSD1306

  Adafruit library ported to the SH1106
  https://github.com/badzz/Adafruit_SH1106      Currently used library in this sketch!!!

  https://github.com/wonho-maker/Adafruit_SH1106
  https://github.com/shondll/Adafruit_SSD1306

  Adafruit GFX Library
  https://github.com/adafruit/Adafruit-GFX-Library


*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include "bitmap.h"



/*--------------------------------------------------------------------------------------
    ___ ___  _  _ ___ ___ ___ _   _ ___    _ _____ ___ ___  _  _
   / __/ _ \| \| | __|_ _/ __| | | | _ \  /_\_   _|_ _/ _ \| \| |
  | (_| (_) | .` | _| | | (_ | |_| |   / / _ \| |  | | (_) | .` |
   \___\___/|_|\_|_| |___\___|\___/|_|_\/_/ \_\_| |___\___/|_|\_|
     ___  ___ _____ ___ ___  _  _ ___
    / _ \| _ \_   _|_ _/ _ \| \| / __|
   | (_) |  _/ | |  | | (_) | .` \__ \
    \___/|_|   |_| |___\___/|_|\_|___/

*/

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define CODE_VERS  "1.32"  // Code version number 
//Arduino UNO/NANO/MINI ETC. (Atmel ATMega 328 Chips) are not supported, Please don't ask!!!
//Use Leonardo/ProMicro (Atmel 32u4)


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/*Define correct OLED display type!!!*/
/*Warning!!!! Please check you have the correct polarity for the selected OLED screen*/

#define OLED_SSD1306
//#define OLED_SH1106

/* comment out below, to disable all pre-selected power/gnd pins on Arduino pins D4 and D5 when not powering OLED from ProMicro*/
//#define enablepowerPins

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/*Uncomment below, to use arduino pins to power the screen*/

//#define powerPins  //(VCC, GND, SCL, SDA)   eg: Typically SSD1306 OLED displays
/*Warning!!!! Please check you have the correct polarity for the selected OLED screen*/

/*Make power rails on the header for the OLED, Check your PCB polarity
  -------------------------------------------------------------
   0.96" i2C OLED:    VCC         GND          SCL        SDA

   ProMicro Pins:     D5(HIGH)    D4(LOW)      D3         D2
   -------------------------------------------------------------*/

//#define powerPins2 //(GND, VCC , SCL, SDA) eg: eBay SH1106 OLED displays are opposite polarity to SSD1306!!!
/*Warning!!!! Please check you have the correct polarity for the selected OLED screen*/

/*Make power rails on the header for the OLED, Check your PCB polarity
  -------------------------------------------------------------
   0.96" i2C O        GND         VCC           SCL        SDA

   ProMicro Pins:     D5(LOW)     D4(HIGH)      D3         D2
   -------------------------------------------------------------*/

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/* Uncomment below, to take out small degree symbol for better spacing
   when hitting 100% cpu/gpu load the percent symbol gets clipped */
//#define noDegree

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/* Uncomment below, to enable custom threshold event triggers*/

//#define uVol_enableThesholdtriggers
//#define enableCustomThesholdtriggers
#define enableNeopixelGauges // NeoPixel ring bargraph example

/* comment out, to disable blank screen on serial timeout to retain info eg: PC crash fault diagnostics  */
#define enableActivityChecker

/* Uncomment below, to enable positive and negative screen cycler */
//#define enableInvertscreen

/* Time between "DisplayStyle" changes */
#define displayChangeDelay 18000

/* Neo Pixel Setup */
#define NEOPIN         10
#define NUMPIXELS      16

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


/*SH1106 OLED setup*/
#ifdef OLED_SH1106

#include <Adafruit_SH1106.h> // i2C not SPI
#define SH1106_128_64
#define OLED_RESET 4  //  "OLED_RESET" IS IS NOT A PHYSICAL PIN DO NOT CONNECT!!!
Adafruit_SH1106 display(OLED_RESET);

#endif


/*SSD1306 OLED setup*/
#ifdef OLED_SSD1306

#include <Adafruit_SSD1306.h> // i2C not SPI
#define SSD1306_128_64
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4     // "OLED_RESET" IS IS NOT A PHYSICAL PIN DO NOT CONNECT!!!

//Adafruit_SSD1306 display(OLED_RESET);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

/* More OLED stuff*/
int oledDraw = 0;
int oledOverride = 0;

/* Debounce timers for buttons  /// lastDebounceTime = millis();*/
long lastDebounceTime = 0;
long debounceDelay = 3000;

/* Inverted timers for oled*/
long invertDelay = 60000; // 60 sec  delay
long lastInvertTime = 0;
int invertedStatus = 1;

/* Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
#define lastActiveDelay 30000
boolean bootMode = true;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

/*vars for serial input*/
String inputString = "";
boolean stringComplete = false;

/* cycle screen DisplayStyles */
int displayChangeMode = 2;
long lastDisplayChange;


/*
   ___ ___ _____ _   _ ___
  / __| __|_   _| | | | _ \
  \__ \ _|  | | | |_| |  _/
  |___/___| |_|  \___/|_|

*/

void setup() {

#ifdef enablepowerPins
#ifdef powerPins          // (VCC, GND, SCL, SDA)
  /*Make power rails on the header for the OLED*/
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(4, LOW);   // GND
  digitalWrite(5, HIGH);  // VCC (20mA Max) Check your OLED PCB polarity!!!
#endif

#ifdef powerPins2         //(GND, VCC, SCL, SDA) eBay SH1106 OLED opposite polarity!!! 
  /*Make power rails on the header for the OLED*/
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(4, HIGH);  // VCC (20mA Max) Check your OLED PCB polarity!!!
  digitalWrite(5, LOW);   // GND
#endif

#endif


  /* OLED SETUP */
#ifdef OLED_SH1106

  display.begin(SH1106_SWITCHCAPVCC, 0x3c);    // initialize with the I2C addr 0x3D (for the 128x64)

#endif

#ifdef OLED_SSD1306

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); // initialize with the I2C addr 0x3D (for the 128x64)

#endif

  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  display.clearDisplay();

  /* stops text wrapping*/
  display.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters


  /* Serial setup, start serial port at 9600 bps and wait for port to open:*/
  Serial.begin(9600); // 32u4 USB Serial Baud Rate
  inputString.reserve(200);

  /* Set up the NeoPixel*/
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(120); // Global Brightness
  pixels.show(); // Turn off all Pixels

  /*Initial Load screen*/

  splashScreen();


}

//END of Setup


/*
   __  __   _   ___ _  _   _    ___   ___  ___
  |  \/  | /_\ |_ _| \| | | |  / _ \ / _ \| _ \
  | |\/| |/ _ \ | || .` | | |_| (_) | (_) |  _/
  |_|  |_/_/ \_\___|_|\_| |____\___/ \___/|_|

*/

void loop() {

  /*Serial stuff*/
  serialEvent();

#ifdef enableActivityChecker
  activityChecker();
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

      splashScreen2();
      display.clearDisplay();
      display.display();

      bootMode = false;
    }

    lastActiveConn = millis();


    /*NeoPixel Idle colour*/
    //pixels.setPixelColor(0, BLUE);
    //pixels.show(); // This sends the updated pixel color to the hardware


    if (displayChangeMode == 1) {
      DisplayStyle1();
    }
    else if (displayChangeMode == 2) {
      DisplayStyle2 ();
    }
    else if (displayChangeMode == 3) {
      DisplayStyle3 ();
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


/*
    __ _   _ _  _  ___ _____ ___ ___  _  _ ___
  | __| | | | \| |/ __|_   _|_ _/ _ \| \| / __|
  | _|| |_| | .` | (__  | |  | | (_) | .` \__ \
  |_|  \___/|_|\_|\___| |_| |___\___/|_|\_|___/

*/

//-------------------------------------------  NeoPixel Reset -------------------------------------------------------------

void allNeoPixelsOff() {
  for ( int i = 0; i < NUMPIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 0 );
  }
  //pixels.show();
}

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
    //pixels.setPixelColor(0, BLACK);
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

  display.drawBitmap(0, 0, JustGnatBMP, 64, 64, WHITE);
  display.setTextSize(3);
  display.setCursor(58, 5);
  display.println("GNAT-");
  display.setTextSize(2);
  display.setCursor(64, 30);
  display.println("STATS");

  //Set version to USB Serial
  display.setTextSize(1);
  display.setCursor(68, 55);
  display.print("USB:v");
  display.print (CODE_VERS);

  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();

  //inverter(); // inverted splashscreen image


  // USB Serial Screen

  display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, WHITE);
  display.display();

  //pixels.setPixelColor(0, RED);
  //pixels.show(); // This sends the updated pixel color to the hardware

}


void splashScreen2() {
  display.drawBitmap(0, 0, WaitingDataBMP, 128, 64, WHITE);
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
}
