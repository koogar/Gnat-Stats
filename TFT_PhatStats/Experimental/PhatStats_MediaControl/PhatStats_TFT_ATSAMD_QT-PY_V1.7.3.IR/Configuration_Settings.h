/*
      ____  __  _____  ______   ______________  ___________    __________________
     / __ \/ / / /   |/_  __/  / ___/_  __/   |/_  __/ ___/   /_  __/ ____/_  __/
    / /_/ / /_/ / /| | / /_____\__ \ / / / /| | / /  \__ \     / / / /_    / /
   / ____/ __  / ___ |/ /_____/__/ // / / ___ |/ /  ___/ /    / / / __/   / /
  /_/   /_/ /_/_/  |_/_/     /____//_/ /_/  |_/_/  /____/    /_/ /_/     /_/

  /*


  V1.58:  STM32 ( / ILI9431 TFT (320 x 240) only preview version for the new features in HardwareSerialmonitor v1.3.

          Button to change between portrait and landscape mode.

          Additional GPU Features:
          Fan Speed Load%, Fan Speed RPM, Total Memory, Used Memory, Current Power Consumption in Watts (Nvidia).

          Additional system RAM features:
          Total Memory, Available Memory, Memory Load.

          Config Options:
          Intel/AMD  CPU and GPU Bitmaps.
          Specify CPG/GPU TJMax Warnings.


  V1.58b:
        Config Options:
        Debug Screen CFG Setting.
        PWM Backlight Direct Pin Connection for 3.3v.
        PWM Backlight PNP Transitor Pin Connection for 5v.

  V1.59:
        Rotary Encoder Brightness Control.

  v1.59.6:
        ADD: CPU Turbo & GPU Boost Clock Indicator with Overclock Frequency Gain Display

        Minimise Screen Refresh Blinking using "tft.setTextColor(Text, Background);"
        and "Magic Digit Eraser" Function for digits that gain in length.
        (the above only works for the default font!!! (This is a limitation of the GRFX library)

  v1.6.1 :

        ADD: ATSAMD21 Support
        ADD: Show Overclock/Turbo/Boost values as a percentage over stock CPU/GPU values

  v1.6.2 :
        Optimised (Non Blinking) and character erase. Thanks to contributor "(MaD)erer"

  v1.6.3 :
       Optimised (Non Blinking) and character erase for CPU/GPU Frequency if Speedstep is enabled

  v1.6.3.IR :(experimental)
       Add InfraRed Media Control (Only works when Phat-Stats is active)

  v1.6.4.IR:(experimental)
       QT-PY Only: Optimise Pins (changes from previous)
       Remove PWM_Encoder_PNP option
       Move ActivityChecker and Serialevent back to main loop,
       Add option to disable ActivityChecker to retain last info before PC crash ETC

  v1.6.5.IR:(experimental)
       Move encoder modes in its own function tab
       Rename switchpin to encoder_Button
       Clean up old stuff

  v1.6.6.IR:(experimental)
       Add HID Volume control using the rotary encoder (runs all the time and is non-blocking)
       Remove Static_PWM define.

                 If "//Encoder_PWM" is commented(disabled) it will default to a fixed PWM value,
                 and the encoder will act as a volume control.

                 If "Encoder_PWM" is uncommeted(active) the rotary encoder
                 will adjust the backlight PWM

  v1.6.8.IR:(experimental)
      Volume and PWM Brightness now use a non blocking interrupt

  v1.6.9.IR:(experimental)
      Add Feature indicator to display enables features on splash screen

  v1.7.IR:(experimental)
      Reduce the amount of header files.

  Note: Gnat-Stats/Phat-Stats is optimised for desktop CPU's with dedicated graphics cards, such as Nvidia/Radeon.
      You may get weird results on mobile CPUs and integrated GPU's (iGPU's) on laptops.

  --------------------------------------------------------------------------------------
    ___ ___  _  _ ___ ___ ___ _   _ ___    _ _____ ___ ___  _  _
   / __/ _ \| \| | __|_ _/ __| | | | _ \  /_\_   _|_ _/ _ \| \| |
  | (_| (_) | .` | _| | | (_ | |_| |   / / _ \| |  | | (_) | .` |
   \___\___/|_|\_|_| |___\___|\___/|_|_\/_/ \_\_| |___\___/|_|\_|
     ___  ___ _____ ___ ___  _  _ ___
    / _ \| _ \_   _|_ _/ _ \| \| / __|
   | (_) |  _/ | |  | | (_) | .` \__ \
    \___/|_|   |_| |___\___/|_|\_|___/

  --------------------------------------------------------------------------------------
*/

//--------------------------- Micro Controller Selection---------------------------------

/* Uncomment your Micro Processor,*/
#define Adafruit_QTPY
//#define Seeeduino_XIAO

/* Uncomment your CPU,*/
#define AMD_CPU
//#define INTEL_CPU

//--------------------------- CPU/GPU Display Settings -----------------------------------

/* Uncomment your GPU,*/
//#define NVIDIA_GRAPHICS
#define AMD_GRAPHICS

/* Characters to delete from the start of the CPU/GPU name eg: Remove "Intel" or "Nvidia" to save space*/
#define cpuNameStartLength 10
#define gpuNameStartLength 11

/* CPU is overclocked with Turbo boost disabled, to stop "TURBO" indicator,*/
//#define CPU_OverClocked

/* CPU & GPU Thermal Junction Max Temperature before throttling,*/
#define CPU_TJMAX 100  //  TJ Max for the Intel 9900K    = 100c
#define GPU_TJMAX 83   //  TJ Max for the Nvidia GTX1080 = 83c

/* CPU & GPU Turbo/Boost Frequency Values in Mhz */
#define CPU_BOOST 3700  //  Intel Core i9600k = 3700MHz Turbo to 4600MHz
#define GPU_BOOST 1683  //  MSi GamingX 1080 = 1683MHz

/* Remove Specific GPU items Power/Fan RPM/Fan% */
#define enable_gpuPowerStats // Nvidia Specific???
#define enable_gpuFanStats%
#define enable_gpuFanStatsRPM

//---------------------------------------------------------------------------------------
/* Uncomment to show Frequency gain MHz or Percent,*/
#define enable_ShowFrequencyGain

/* Uncomment only one of the below,*/
//#define ShowFrequencyGainMHz    // Show Overlock/Turbo & Boost Clock Frequency Gains in MHZ  eg: "+24MHz"
#define ShowFrequencyGain%       // Show Overlock/Turbo & Boost Clock Frequency Gains in Percent  eg: "+24%"

//---------------------------------------------------------------------------------------

#define enable_ThrottleIndicator // Show TJMax Indicator 
#define enable_BoostIndicator    // Show CPU & GPU Turbo/Boost Indicator

#define noDegree      // lose the "o"
#define smallPercent  // Use small percent symbol

//-------------------------------- Phat-Tacho Gauge -------------------------------------

#define enableNeopixelGauges     // NeoPixel ring bargraph example

int NeoBrightness = 20;         //Global Brightness

//----------------------------- Rotary Encoder Usage ------------------------------------

/* Uncomment only one option, */

/* Use the Rotary Encoder for variable PWM control, connected direct to the MCU PIN*/
//#define Encoder_PWM2 // use rotary encoder for PWM screen brightness control  3.3v 

/* Use the Rotary Encoder for HID Volume Control*/
#define Encoder_HID

//---------------------------- InfraRed Media Control-------------------------------------
/* Option to disable IR*/
#define enableIR

/*Remote code Selection*/
#define IR_BOSE        // Set Bose Remote Codes                  (Sends repeat codes)
//#define IR_AppleWhite  // Set Apple White Plastic Remote Codes  (Does not send repeat codes)
//#define IR_AppleAlu    // Set Apple Aluminium Remote Codes      (Does not send repeat codes)

//-------------------------- Display Activity Shutdown -----------------------------------

/* Uncomment below to turn off the screen on serial timeout, else keep last display info eg: incase of PC Crash*/
#define enableActivityChecker

/* How long the display takes to timeout due to inactive serial data from the windows application */
#define lastActiveDelay 8000

//-------------------------------- Misco Setting -----------------------------------------

/* Debounce Rotary Encoder Button,Sometimes it gets caught during a screen refresh and doesnt change*/
int debounceEncButton = 150; //  Use a 0.1uf/100nf/(104) ceramic capacitor from button Pin to GND and set at "0"

/* Delay screen event, to stop screen data corruption ESP8622 use 25, most others 5 will do*/
int Serial_eventDelay = 0; //

//----------------------------- Debug Screen Erasers ---------------------------------------

/* Debug Screen, Update Erasers, */
//#define Debug
