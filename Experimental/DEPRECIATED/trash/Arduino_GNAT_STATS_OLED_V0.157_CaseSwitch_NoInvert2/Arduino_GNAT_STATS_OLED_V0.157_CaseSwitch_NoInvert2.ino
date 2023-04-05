
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
#include "bitmap.h"


/* OLED setup*/
#define SSD1306_128_64
#define OLED_RESET -1 //4


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* More OLED stuff*/
int oledDraw = 0;
int oledOverride = 0;


/* Timer for active connection to host*/
#define lastActiveDelay 8000
boolean activeConn = false;
long    lastActiveConn = 0;
boolean bootMode = true;

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


// Button pin
int counter   = 0;
int switchPin = 1;

/*vars for serial input*/
String inputString = "";
boolean stringComplete = false;

//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

void setup() {
  /* Serial setup, start serial port at 9600 bps and wait for port to open:*/
  Serial.begin(9600);
  inputString.reserve(200);


  /* OLED SETUP */
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  display.clearDisplay();

  /* stops text wrapping*/
  display.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters

  pinMode(switchPin, INPUT_PULLUP);

  /*Initial Load screen*/
  splashScreenA();   //Uses more memory
  //splashScreenB();  //Uses less memory
  //splashScreenC();    //Uses less memory
  //splashScreenD();  //Uses least memory

}


//--------------------------------------------------


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
  }

  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  //Handle input
  int switchVal = digitalRead(switchPin);
  if (switchVal == LOW)
  {
    //delay(10);
    counter ++;
    //Reset count if over max mode number
    if (counter == 3)
    {
      counter = 0;
    }
  }

  else
    //Change mode
    switch (counter) {


      case 1:
        DisplayStyle1_NC ();
        //counter = 2;
        break;

      case 2:
        DisplayStyle2_NC ();
        //counter = 3;
        break;

      case 3:
        DisplayStyle3_NC ();
        //counter = 1;
        break;

      default:
        DisplayStyle1_NC ();
        //counter = 1;
        break;

        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


        inputString = "";
        stringComplete = false;

        // Keep running function continuously
        if (oledDraw == 1 && !serialEvent) {


        }
    }
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

    display.clearDisplay();
    display.display();

    //Experimental,  attempt to stop intermittent screen flicker when in no activity mode "screen off" (due to inverter function?) fill the screen 128x64 black rectangle
    display.fillRect(0, 0, 128, 64, BLACK);
    display.display();
    oledDraw = 0;

  }
}
