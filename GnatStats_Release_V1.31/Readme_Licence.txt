
    ____             _             ____  _        _
   / ___|_ __   __ _| |_          / ___|| |_ __ _| |_ ___
  | |  _| '_ \ / _` | __|  _____  \___ \| __/ _` | __/ __|
  | |_| | | | | (_| | |_  |_____|  ___) | || (_| | |_\__ \
   \____|_| |_|\__,_|\__|         |____/ \__\__,_|\__|___/


  GNATSTATS OLED PC Performance Monitor / HardwareSerialMonitor -  Rupert Hirst & Colin Conway © 2016-2018
  http://tallmanlabs.com  & http://runawaybrainz.blogspot.com/

  Licence
  -------

  Attribution-NonCommercial-ShareAlike  CC BY-NC-SA

  This license lets others remix, tweak, and build upon your work non-commercially, as long as they credit you and license their new creations under the identical terms.

  https://creativecommons.org/licenses/



  Notes:

  I strongly suggest using this sketch with Atmel 32u4 based boards such as, the Leonardo or ProMicro, due to to its native USB support.

  The Windows application "HardwareSerialMonitor v1"  uses the OpenHardwaremonitor  OpenHardwareMonitorLib.dll to detect the hardware.  http://openhardwaremonitor.org/
  The Windows application "HardwareSerialMonitor v2" (.Net 4.6.2) uses the LibreHardwareMonitor OpenHardwareMonitorLib.dll to detect the hardware.  https://github.com/LibreHardwareMonitor/LibreHardwareMonitor

  The application will not detect integrated graphics as a GPU!!!
  Presently HardwareSerialMonitor does not like virtual Bluetooth COM ports present on the users PC!!!

  "Hardware Serial Monitor" Was inspired by the Visual Studio project kindly shared by psyrax see: https://github.com/psyrax/SerialMonitor


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


         ToDo:
         Windows custom GnatStats device icon
         Auto or button screen change option,
         PC Diagnostic switch / mode eg: Min / Max readings,
         Analogue Panel Meter Readings output



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