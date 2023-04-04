/*
   _____ __  __ _         _            ___           _   ___ _        _
  |_   _|  \/  | |   __ _| |__ ______ / __|_ _  __ _| |_/ __| |_ __ _| |_ ___
    | | | |\/| | |__/ _` | '_ (_-<___| (_ | ' \/ _` |  _\__ \  _/ _` |  _(_-<
    |_| |_|  |_|____\__,_|_.__/__/    \___|_||_\__,_|\__|___/\__\__,_|\__/__/

   uVolume, GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
   Rupert Hirst © 2016-2023

   http://tallmanlabs.com  http://runawaybrainz.blogspot.com/
   https://github.com/koogar/Gnat-Stats  https://hackaday.io/project/181320-gnat-stats-tiny-oled-pc-performance-monitor
   

   Licence
   -------
   GPL v3*/

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

/* Anti Screen Burn */
//#define enableInvertscreen 

/* Uncomment below, to take out small degree symbol for better spacing
   when hitting 100% cpu/gpu load the percent symbol gets clipped */
//#define noDegree
