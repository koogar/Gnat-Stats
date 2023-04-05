

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

/* Time between "DisplayStyle" changes */
#define displayChangeDelay 18000
/* Start DisplayStyle */
int displayChangeMode = 1;
long lastDisplayChange;

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

  display.setRotation(2);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  display.clearDisplay();

  /* stops text wrapping*/
  display.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters

  pinMode(switchPin, INPUT_PULLUP);

  /*Initial Load screen*/
  splashScreen();

}


//--------------------------------------------------


void loop() {

  serialEvent();
  activityChecker();

  //auto_DisplayStyle();
  ButtonMode();

#ifdef ButtonMode
  ButtonMode();
#endif

#ifdef AutoMode();
  auto_DisplayStyle();
#endif


}

//END of Main Loop



//--------------------------------------------------------------------------------------------------------

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

    display.clearDisplay();
    display.display();

    //Experimental,  attempt to stop intermittent screen flicker when in no activity mode "screen off" (due to inverter function?) fill the screen 128x64 black rectangle
    display.fillRect(0, 0, 128, 64, BLACK);
    display.display();
    oledDraw = 0;

  }
}


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
  display.print ("9600"); display.println(".bit/s");

  //Set version to USB Serial
  display.setTextSize(1);
  display.setCursor(66, 56);
  display.print("V:");
  display.print ("CODE_VERS");

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
