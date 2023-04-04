
#define CODE_VERS  "1.7.Base"  // Code version number


#include <Wire.h>
#include <Adafruit_GFX.h>
#include "bitmap.h"
#include "Setup.h"

//--------------------- OLED Setup --------------------------

/*Uncomment the correct OLED display type, uncomment only one display!!!*/

/* SSD1306 Compatability -->> QT PY ATSAMD21(YES), XIAO ATSAMD21(YES), XIAO RP2040 (YES), XIAO NRF52840 (YES), XIAO ESP32C3 (YES)*/
/* SH1106  Compatability -->> QT PY ATSAMD21(YES), XIAO ATSAMD21(YES), XIAO RP2040 (YES), XIAO NRF52840 (YES), XIAO ESP32C3 (YES)*/

/*Flip the display:  0 or 2  (0, 180 degrees)*/
#define rotateScreen 0

/*---------------- SSD1306 -------------*/
#define OLED_SSD1306
//#define dim_Display // dim display SD1306 Only!!!

/*---------------- SH1106 --------------*/
//#define OLED_SH1106


//--------------- Manual CPU/GPU Display Name Entry -------------------------

/* Requires DisplayStyles ending in "_NC" (NameChange),*/
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
//------------------------------------------------------------------------------

//>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Delay screen event, to help stop screen data corruption ESP8622 use 25, most others 5 will do*/
int Serial_eventDelay = 15;
int baud = 9600; //serial do not adjust

/* Timer for active connection to host*/
#define lastActiveDelay 6000


/* Uncomment below, to take out small degree symbol for better spacing
   when hitting 100% cpu/gpu load the percent symbol gets clipped */
//#define noDegree

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


//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* OLED Screen */
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

    // Keep running function continuously
    if (oledDraw == 1 && !serialEvent) {


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

    display.clearDisplay();
    display.display();

    //Experimental,  attempt to stop intermittent screen flicker when in no activity mode "screen off" (due to inverter function?) fill the screen 128x64 black rectangle
    display.fillRect(0, 0, 128, 64, BLACK);
    display.display();

    oledDraw = 0;

  }
}


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
