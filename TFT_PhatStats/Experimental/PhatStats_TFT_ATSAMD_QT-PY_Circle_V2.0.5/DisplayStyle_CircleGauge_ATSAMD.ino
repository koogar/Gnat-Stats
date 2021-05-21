
void DisplayStyle_CircleGauge_ATSAMD () {


 
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

  /*Optimised for 1.3" SPI Colour Round LCD ST7789V (240x240),
    Same ST7789 library as the square version*/

  /*ST7789 240x240 Portrait & Landscape offsets,*/
  //#define X_Offset  40 // - Portrait
  //#define Y_Offset  0  // + Portrait

  /*ILI9341 240x320 Portrait offsets(centre),*/
  //#define X_Offset  40 // - Portrait
  //#define Y_Offset  40 // + Portrait

  /*ILI9341 240x320 Landscape offsets(centre),*/
  //#define X_Offset  0 // - Landscape
  //#define Y_Offset  0 // + Landscape

  /*ILI9341 240x320 Portrait offsets(Middle of PCB 86mm),*/
  //#define X_Offset 40 // - Portrait
  //#define Y_Offset 63 // + Portrait

  /*ILI9341 240x320 Landscape offsets(Middle of PCB 86mm),*/
#define X_Offset 0// - Landscape
#define Y_Offset 0 // + Landscape

  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


  /* TFT DRAW STATS */
  if (stringComplete) {

    if (bootMode) {

      tft.fillScreen(ILI9341_BLACK);

      tft.setFont(); // set to default Adafruit library font

      //tft.fillCircle(136 - X_Offset, 120 + Y_Offset, 112, ILI9341_RED); // landscape circle 119 for radius -1 for line thickness
      tft.fillCircle  (136 - X_Offset, 120 + Y_Offset, 112, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness

      //tft.invertDisplay(true);

      bootMode = false;
    }

    lastActiveConn = millis();

    //tft.setTextColor(ILI9341_BLACK, ILI9341_WHITE);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);

#ifdef Debug
    tft.setTextColor(ILI9341_BLACK, ILI9341_RED); // used to stop flickering when updating digits that do not increase in length. CPU/GPU load still need a clear box on the end digits
#endif

    //--------------------------------------- Display Background ----------------------------------------------------
    tft.setRotation(3);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

    backlightON (); //Turn ON display when there is  activity
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


    //>>>>>>>>>>>>>>>>>>>>>>>> Left Side Circle Apperture  >>>>>>>>>>>>>>>>>>>>>>>>>>>>
    tft.fillCircle   (10 - X_Offset,   10, 6, ILI9341_BLUE); // top left corner  LS 0,0
    tft.drawCircle   (10 - X_Offset,   10, 7, ILI9341_WHITE); // top left corner  LS 0,0

    tft.fillCircle   (10 - X_Offset,   228, 6, ILI9341_RED);  // bottom left corner LS
    tft.drawCircle   (10 - X_Offset,   228, 7, ILI9341_WHITE); // bottom left corner LS



    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    //tft.drawFastVLine(160 - X_Offset, 10 + Y_Offset, 220, ILI9341_WHITE);
    tft.drawRect     (26 - X_Offset, 118 + Y_Offset, 220, 4, ILI9341_RED);
    tft.drawFastHLine(26 - X_Offset, 120 + Y_Offset, 220, ILI9341_WHITE);


    //---------------------------------------CPU & GPU Hardware ID---------------------------------------------------------

    /* CPU & GPU Hardware ID */

    if (inputString.indexOf("CPU") > -1)
    {

      String cpuName = "";

      int cpuNameStart = inputString.indexOf("CPU:");
      if (inputString.indexOf("Intel", cpuNameStart) > -1) {
        cpuNameStart = cpuNameStart + cpuNameStartLength;
      }
      else {
        cpuNameStart = cpuNameStart + 8;
      }
      if (inputString.indexOf("GPU") > -1)
      {
        cpuName = inputString.substring(cpuNameStart, inputString.indexOf("GPU:"));
      }
      else
        cpuName = inputString.substring(cpuNameStart);

      tft.setTextSize(1);
      tft.setCursor(98 - X_Offset, 19 + Y_Offset); // (Left/Right, UP/Down)

      /* CPU Manual Name*/
#ifdef Manual_cpuName
      tft.println(set_CPUname);
#else
      /* CPU Auto Detect Name*/
      tft.println(cpuName);
#endif

    }
    if (inputString.indexOf("GPU") > -1)
    {

      int gpuNameStart = inputString.indexOf("GPU:");
      if (inputString.indexOf("NVIDIA", gpuNameStart) > -1) {
        gpuNameStart = gpuNameStart + gpuNameStartLength;
      }
      else {
        gpuNameStart = gpuNameStart + 8;
      }

      int gpuNameEnd = inputString.indexOf("|", gpuNameStart);

      /* GPU Manual Name*/
#ifdef Manual_gpuName
      String gpuName = set_GPUname; // Name spacing test
#else
      /* GPU Auto Detect Name*/
      String gpuName = inputString.substring(gpuNameStart, gpuNameEnd);
#endif

      tft.setTextSize(1);
      tft.setCursor(51 - X_Offset, 130 + Y_Offset); // Position GPU Name
      tft.println(gpuName);
    }

    //------------------------------------------------------RX indicator---------------------------------------------------

#ifdef enable_BT

    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 111, ILI9341_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 112, ILI9341_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 113, ILI9341_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 114, ILI9341_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 115, ILI9341_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 116, ILI9341_WHITE); // landscape circle 119 for radius -1 for line tickness
#else

    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 111, ILI9341_RED); // // flash circle surround
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 112, ILI9341_RED); // // flash circle surround
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 113, ILI9341_RED); // // flash circle surround
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 114, ILI9341_RED); // // flash circle surround
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 115, ILI9341_RED); // // flash circle surround
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 116, ILI9341_WHITE); // // flash circle surround
#endif

    //--------------------------------------------DATA CLEARING BOXES------------------------------------------------------

    /* New Update Clearing Boxes see: tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);*/
#ifdef Debug

    tft.setTextColor(ILI9341_WHITE, ILI9341_RED);

#define ILI9341_updateBox ILI9341_GREY  // Fill boxes grey for text alignment 

#else

#define ILI9341_updateBox  ILI9341_BLACK // Default for normal running

#endif

    //------------------------------------------ CPU Load/Temp -------------------------------------------------

    /* CPU Display String */
    int cpuStringStart = inputString.indexOf("C");
    int cpuDegree = inputString.indexOf("c");
    int cpuStringLimit = inputString.indexOf("|");
    String cpuString1 = inputString.substring(cpuStringStart + 1, cpuDegree);
    String cpuString2 = inputString.substring(cpuDegree + 1, cpuStringLimit - 1);

    //Char erase and spacing adjust, MaDerer
    /* CPU TEMP,*/
    if (cpuString1.length() == 1) cpuString1 = " "  + cpuString1;


    /* CPU LOAD,*/
    if (cpuString2.length() == 3) cpuString2 = " "  + cpuString2;
    if (cpuString2.length() == 2) cpuString2 = "  " + cpuString2;

    /* CPU TEMPERATURE */
    tft.setTextSize(3);
    tft.setCursor(64 - X_Offset, 72 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(cpuString1);  // CPU TEMP


    tft.setTextSize(1);
#ifdef noDegree
    tft.print("C");       // Centigrade Symbol
#else
    tft.print((char)247); //Degrees Symbol
    tft.print("C");       // Centigrade Symbol
#endif

    /* CPU LOAD, ALL CORES */
    tft.setTextSize(3);
    tft.setCursor(122 - X_Offset, 72 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(cpuString2);  // CPU Load

#ifdef  smallPercent
    tft.setTextSize(2);
    tft.print("%");
#else
    tft.setTextSize(3);
    tft.print("%");
#endif

    //------------------------------------------ CPU Freq -------------------------------------------------

    /* CPU Freq Display String*/
    int cpuCoreClockStart = inputString.indexOf("CHC") + 3;
    int cpuCoreClockEnd = inputString.indexOf("|", cpuCoreClockStart);
    String cpuClockString = inputString.substring(cpuCoreClockStart, cpuCoreClockEnd);

    //Char erase and spacing adjust, MaDerer
    while (cpuClockString.length() < 4) cpuClockString = " " + cpuClockString;

    /* CPU OVERCLOCK Freq Gain */
    double cpuOverclockGain = atof(cpuClockString.c_str());
    double  cpuOverclockSum = cpuOverclockGain - CPU_BOOST; //values in Mhz

    /* CPU OVERCLOCK Freq Gain in Percent, eg: 3700MHz/100 = 37MHz(1%)  , (OC Gain)895MHz / 37MHz(1%) = 24.19%,*/

    double cpuOverclockGainPercentSum = cpuOverclockSum / (CPU_BOOST / 100); // % of gain over Stock CPU

    /* CPU  Freq Display */
    tft.setTextSize(4);
    tft.setCursor(90 - X_Offset, 35 + Y_Offset ); // (Left/Right, UP/Down)
    tft.print(cpuClockString);
    tft.setTextSize(1);
    tft.print("MHz");


#ifdef  enable_ShowFrequencyGain

    /* CPU OVERCLOCK Display Freq Gain in MHz */
    tft.setCursor(182 - X_Offset, 47 + Y_Offset);// (Left/Right, UP/Down)
    tft.fillRect (184 - X_Offset, 47 + Y_Offset , 37, 10, ILI9341_BLACK);

#ifdef ShowFrequencyGainMHz
    tft.setTextSize(1);
    tft.print (" +");
    //tft.print ("  ");
    tft.print(cpuOverclockSum, 0);            // Show Value in MHz
    //tft.setTextSize(1);
    //tft.println ("MHz");
#endif
#ifdef ShowFrequencyGain%
    tft.setTextSize(1);
    //tft.print ("  +");
    tft.print ("   ");
    tft.print(cpuOverclockGainPercentSum, 0); // Show Value in %
    tft.println ("%");
#endif
#endif

    //------------------------------------------ GPU Load/Temp -------------------------------------------------

    /* GPU Display String */
    int gpuStringStart = inputString.indexOf("G", cpuStringLimit);
    int gpuDegree = inputString.indexOf("c", gpuStringStart);
    int gpuStringLimit = inputString.indexOf("|", gpuStringStart);
    String gpuString1 = inputString.substring(gpuStringStart + 1, gpuDegree);
    String gpuString2 = inputString.substring(gpuDegree + 1, gpuStringLimit - 1);

    //Char erase and spacing adjust, MaDerer
    /* GPU TEMP,*/
    if (gpuString1.length() == 1) gpuString1 = " "  + cpuString1;
    /* GPU LOAD,*/
    if (gpuString2.length() == 3) gpuString2 = " "  + gpuString2;
    if (gpuString2.length() == 2) gpuString2 = "  " + gpuString2;

    /* GPU TEMPERATURE */
    tft.setTextSize(3);
    tft.setCursor(64 - X_Offset, 144 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(gpuString1);
    tft.setTextSize(1);

#ifdef noDegree
    tft.print("C");       // Centigrade Symbol
#else
    tft.print((char)247); //Degrees Symbol
    tft.print("C");       // Centigrade Symbol
#endif

    /* GPU LOAD */
    tft.setTextSize(3);
    tft.setCursor(112 - X_Offset, 144 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(gpuString2);

#ifdef  smallPercent
    tft.setTextSize(2);
    tft.print("%");
#else
    tft.setTextSize(3);
    tft.print("%");
#endif


    //------------------------------------------ GPU Freq/Temp -------------------------------------------------

    /* GPU temp V's GPU freq to check for throttling and max 'GPU Boost' */

    /* GPU Core Freq, */
    int gpuCoreClockStart = inputString.indexOf("GCC") + 3;
    int gpuCoreClockEnd = inputString.indexOf("|", gpuCoreClockStart);
    String gpuCoreClockString = inputString.substring(gpuCoreClockStart, gpuCoreClockEnd);

    //Char erase and spacing adjust, MaDerer
    while (gpuCoreClockString.length() < 4) gpuCoreClockString = " " + gpuCoreClockString;

    /* GPU OVERCLOCK Freq Gain in MHz, */
    double gpuOverclockGain = atof(gpuCoreClockString.c_str());
    double  gpuOverclockSum = gpuOverclockGain - GPU_BOOST; //values in Mhz

    /* GPU OVERCLOCK Freq Gain in Percent, eg: 1683MHz/100 = 16.83MHz(1%) , (OC Gain)254MHz / 16.83MHz(1%) = 15.09%,*/
    double gpuOverclockGainPercentSum = gpuOverclockSum / (GPU_BOOST / 100); // % of gain over Stock GPU


#ifdef  enable_ShowFrequencyGain
    /* GPU OVERCLOCK Display Freq Gain, */
    //tft.setCursor(225, 56);// (Left/Right, UP/Down)
    tft.setCursor(182 - X_Offset, 180 + Y_Offset);
    tft.fillRect (182 - X_Offset, 179 + Y_Offset , 40, 10, ILI9341_BLACK);

#ifdef ShowFrequencyGainMHz
    tft.setTextSize(1);
    tft.print (" +");
    tft.print(gpuOverclockSum, 0);            // Show Value in MHz
    //tft.setTextSize(1);
    //tft.println ("MHz");
#endif
#ifdef ShowFrequencyGain%
    tft.setTextSize(1);
    //tft.print ("  +");
    tft.print ("   ");
    tft.print(gpuOverclockGainPercentSum, 0); // Show Value in %
    tft.println ("%");
#endif

#endif

    // GPU Frequency
    tft.setTextSize(4);
    tft.setCursor(90 - X_Offset, 170 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(gpuCoreClockString);
    tft.setTextSize(1);
    tft.print("MHz");

    //----------------------------------------------GPU Memory Total----------------------------------------------------------

    int gpuMemoryStart = inputString.indexOf("GMT") + 3;
    int gpuMemoryEnd = inputString.indexOf("|", gpuMemoryStart);
    String gpuMemoryString = inputString.substring(gpuMemoryStart, gpuMemoryEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuMemoryString.length() < 4) gpuMemoryString = " " + gpuMemoryString;

    double totalGPUmem = atof(gpuMemoryString.c_str());
    double totalGPUmemSum = totalGPUmem / 1024;    // divide by 1024 to get the correct value
    float  totalGPUmemSumDP = totalGPUmemSum ;     // float to handle the decimal point when printed (totalGPUmemSumDP, 0)

    tft.setTextSize(1);
    tft.setCursor(201 - X_Offset, 130 + Y_Offset); // Position GPU Total Memory

#ifdef Manual_gpuRam
    tft.print(set_GPUram);
#else
    tft.print(totalGPUmemSumDP, 0); // Show Value in GB
#endif

    tft.setTextSize(1);
    tft.print("GB");
    //----------------------------------------------GPU Memory Used----------------------------------------------------------

    /*GPU Memory Used */
    int gpuMemoryUsedStart = inputString.indexOf("GMU") + 3;
    int gpuMemoryUsedEnd = inputString.indexOf("|", gpuMemoryUsedStart);
    String gpuMemoryUsedString = inputString.substring(gpuMemoryUsedStart, gpuMemoryUsedEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuMemoryUsedString.length() < 4) gpuMemoryUsedString = " " + gpuMemoryUsedString;

    tft.setCursor(103 - X_Offset, 204 + Y_Offset); // (Left/Right, UP/Down)
    tft.setTextSize(3);
    tft.print(gpuMemoryUsedString); //  show values in MB

    tft.setTextSize(1);
    tft.print("MB");



    //------------------------------------------------GPU Power Consumption--------------------------------------------------------
#ifdef enable_gpuPowerStats

    /* GPU Power */  // Nvidia Driver 457.51 works. Broken in Driver Version: 460.79 460.89
    int gpuPowerStart = inputString.indexOf("GPWR") + 4;
    int gpuPowerEnd = inputString.indexOf("|", gpuPowerStart);
    String gpuPowerString = inputString.substring(gpuPowerStart, gpuPowerEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuPowerString.length() < 6) gpuPowerString = " " + gpuPowerString;

    tft.setTextSize(1);
    tft.setCursor(46 - X_Offset, 180 + Y_Offset);   // (Left/Right, UP/Down)
    tft.print(gpuPowerString); //GPU Power Watts
    tft.setTextSize(1);
    tft.print("w");
#endif

    //----------------------------------------SYSTEM RAM USAGE---------------------------------------------------

    /* SYSTEM RAM String */
    int ramStringStart = inputString.indexOf("R", gpuStringLimit);
    int ramStringLimit = inputString.indexOf("|", ramStringStart);
    String ramString   = inputString.substring(ramStringStart + 1 , ramStringLimit - 2);
    //Char erase and spacing adjust, MaDerer
    while (ramString.length() < 4) ramString = " " + ramString;

    /* SYSTEM RAM AVALABLE String */
    int AramStringStart = inputString.indexOf("RA", ramStringLimit);
    int AramStringLimit = inputString.indexOf("|", AramStringStart);
    String AramString = inputString.substring(AramStringStart + 2 , AramStringLimit);
    //Char erase and spacing adjust, MaDerer
    while (AramString.length() < 5) AramString = " " + AramString;

    /* SYSTEM RAM TOTAL String */
    double intRam = atof(ramString.c_str());
    double intAram = atof(AramString.c_str());
    //double  intRamSum = intRam + intAram;
    float  intRamSum = intRam + intAram; //float to handle the decimal point when printed (intRamSum,0)

    /* RAM & TOTAL */

    tft.setCursor(86 - X_Offset, 100 + Y_Offset); // (Left/Right, UP/Down)
    tft.setTextSize(2);
    tft.print(intRamSum, 0) ; tft.setTextSize(0); tft.print("GB"); tft.print(" / ");
    tft.setTextSize(2);
    tft.print(ramString)    ; tft.setTextSize(0); tft.println("GB");

    //------------------------------------------ RX indicator Clear------------------------------------------------

    delay(TX_LED_Delay);

    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 111, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 112, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 113, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 114, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 115, ILI9341_BLACK); // landscape circle 119 for radius -1 for line thickness

    //-------------------------------------------------------------------------------------------------------------

    displayDraw = 1;

    //--------------------------Trigger an event when CPU or GPU threshold is met ---------------------------------

#ifdef enable_BoostIndicator
    CustomTriggerCPU_BOOST_Circle( cpuClockString.toInt     ()); // CPU Frequency
    CustomTriggerGPU_BOOST_Circle( gpuCoreClockString.toInt ()); // GPU Frequency
#endif

#ifdef enable_ThrottleIndicator
    CustomTriggerCPU_ThrottleIndicator_Circle( cpuString1.toInt() ); //  CPU TJMax/Throttle Incicator BMP
    CustomTriggerGPU_ThrottleIndicator_Circle( gpuString1.toInt() ); //  GPU TJMax/Throttle Incicator BMP
#endif


    //--------------------------Trigger an event when CPU or GPU threshold is met ---------------------------------


#ifdef enable_CustomThesholdtriggers

    CustomTriggerCPU_temp( cpuString1.toInt() ); //  CPU  Temperature
    CustomTriggerCPU_load( cpuString2.toInt() ); //  CPU  Load

    CustomTriggerGPU_temp( gpuString1.toInt() ); //  GPU  Temperature
    CustomTriggerGPU_load( gpuString2.toInt() ); //  GPU  Load
#endif

#ifdef enableNeopixelGauges // Uncomment only 2, in any combination

    CPU_loadGauge( cpuString2.toInt() ); // Neopixel Ring Gauge  CPU  Load
    //CPU_tempGauge( cpuString1.toInt() ); // Neopixel Ring Gauge  CPU  Temperature

    GPU_loadGauge( gpuString2.toInt() ); // Neopixel Ring Gauge  GPU  Load
    // GPU_tempGauge( gpuString1.toInt() ); // Neopixel Ring Gauge  GPU  Temperature

#endif

#ifdef enableSideLevelGauges // Phat-Tacho CircleGauge only

    CPU_loadLevelGauge( cpuString2.toInt() ); // Side Level Gauge  CPU  Load
    CPU_tempLevelGauge( cpuString1.toInt() ); // Side Level Gauge  CPU  Temperature

    GPU_loadLevelGauge( gpuString2.toInt() ); // Side Level Gauge  GPU  Load
    GPU_tempLevelGauge( gpuString1.toInt() ); // Side Level Gauge  GPU  Temperature

#endif

    //---------------------------------

    inputString = "";
    stringComplete = false;

  }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// -------------------  CPU Turbo Boost Indicator Event Portrait --------------------

void CustomTriggerCPU_BOOST_Circle(int cpuClockString ) {
  float CPUboostfactor = cpuClockString;


  delay(350); // Small delay so Turbo frequency gains stay on screen longer
  //tft.drawRoundRect  (106, 90, 88, 22, 4, ILI9341_WHITE); //

  if (CPUboostfactor >  CPU_BOOST) {  // i5-9600k boost is 3700Mhz to 4700Mhz
    //Do Something!!!

#ifdef CPU_OverClocked //Do Nothing!!

    //Do Nothing!!!

#else
    /* CPU Turbo Clock, */
    //                 (   X,    Y,   Length, Height, Radius,   Colour    )
    tft.fillRoundRect  (  90 - X_Offset,    35 + Y_Offset,    93,      28,     3,   ILI9341_WHITE); //
    tft.fillRoundRect  (  92 - X_Offset,    37 + Y_Offset,    89,      24,     2,   ILI9341_GREEN); //
    tft.setTextSize(2);
    tft.setCursor(110 - X_Offset, 42 + Y_Offset);
    tft.setTextColor(ILI9341_BLACK);
    tft.println("TURBO");

#endif

  }
}

// -------------------  GPU Boost Clock Indicator Event Portrait --------------------

void CustomTriggerGPU_BOOST_Circle(int gpuCoreClockString ) {
  float GPUboostfactor = gpuCoreClockString ;

  //Do Something!!!

  if (GPUboostfactor >  GPU_BOOST) {  //GTX 1080 boost = 1607Mhz to 1733mhz

    /* GPU Boost Clock, */
    //                 (   X,    Y,   Length, Height, Radius,   Colour    )
    tft.fillRoundRect  (  91 - X_Offset,    170 + Y_Offset,    93,      28,     3,   ILI9341_WHITE); //
    tft.fillRoundRect  (  93 - X_Offset,    172 + Y_Offset,    89,      24,     2,   ILI9341_GREEN); //
    tft.setTextSize(2);
    tft.setCursor(111 - X_Offset, 177 + Y_Offset);
    tft.setTextColor(ILI9341_BLACK);
    tft.println("BOOST"); //

  }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// -------------------  CPU Throttle Indicator Event Portrait --------------------

void CustomTriggerCPU_ThrottleIndicator_Circle(int cpuDegree ) {  // i5-9600k TJMax is 100c
  float CPUtempfactor = cpuDegree ;


  if (CPUtempfactor >= CPU_TJMAX ) {  // TJ Max for the Intel 9900K 100c

    /* CPU Junction Max Throttle Temp, */
    //                 (   X,    Y,   Length, Height, Radius,   Colour    )
    tft.fillRoundRect  (  90 - X_Offset,    35 + Y_Offset,    93,      28,     3,   ILI9341_WHITE); //
    tft.fillRoundRect  (  92 - X_Offset,    37 + Y_Offset,    89,      24,     2,   ILI9341_RED); //
    tft.setTextSize(2);
    tft.setCursor(110 - X_Offset, 42 + Y_Offset);
    tft.setTextColor(ILI9341_WHITE);

    tft.println("TJMax");
  }
}


// -------------------  GPU Throttle Indicator Event Portrait --------------------

void CustomTriggerGPU_ThrottleIndicator_Circle(int gpuDegree ) {
  float GPUtempfactor = gpuDegree ;


  if (GPUtempfactor >= GPU_TJMAX ) {  //GTX 1080 TJMax = 83c

    /* GPU Junction Max Throttle Temp, */

    //                 (   X,    Y,   Length, Height, Radius,   Colour    )
    tft.fillRoundRect  (  91 - X_Offset,    170 + Y_Offset,    93,      28,     3,   ILI9341_WHITE); //
    tft.fillRoundRect  (  93 - X_Offset,    172 + Y_Offset,    89,      24,     2,   ILI9341_RED); //
    tft.setTextSize(2);
    tft.setCursor(111 - X_Offset, 177 + Y_Offset);
    tft.setTextColor(ILI9341_WHITE);

    tft.println("TJMax");
  }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//---------------- Phat-Tacho Side Level Bar Graph Threshold Indicators ------------------------  //#define enableSideLevelGauges

//---------------------- CPU--------------------

//>>>>>>>>>>>> CPU TEMP

void CPU_tempLevelGauge(int cpuDegree ) {

  /*Top CPU Temp Level Clear Box,*/
  tft.fillRoundRect(293 - X_Offset, 0 + Y_Offset,   8, 102 , 1, ILI9341_BLACK);

  float CPUtempfactor = cpuDegree;

  /*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*/
  int CPUtempScalefactor = (CPUtempfactor + 1); // +1 so it always shows something

  if (CPUtempfactor >= 0 ) {
    /*Top CPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset, 1 + Y_Offset,   8, CPUtempScalefactor  , 1, ILI9341_GREEN); // Top CPU Temp Scale
  }

  if (CPUtempfactor >= 45 ) {
    /*Top CPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset, 1 + Y_Offset,   8, CPUtempScalefactor   , 1, ILI9341_GREEN); // Top CPU Temp Scale
  }

  if (CPUtempfactor >= 65 ) {
    /*Top CPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset, 1 + Y_Offset,   8, CPUtempScalefactor   , 1, ILI9341_ORANGE); // Top CPU Temp Scale
  }

  if (CPUtempfactor >= 85 ) {
    /*Top CPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset, 1 + Y_Offset,   8, CPUtempScalefactor  , 1, ILI9341_RED); // Top CPU Temp Scale
  }

  tft.drawRoundRect(293 - X_Offset, 0 + Y_Offset,   8, 94  , 1, ILI9341_WHITE); // Draw rectangle round CPU temp bar

  /*Stop Scale running into MAX box,*/
  tft.fillRect (288 - X_Offset , 94 + Y_Offset,  27, 19 , ILI9341_BLACK); // Stop Scale running into MAX box

  // Max Text box CPU
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setCursor(295 - X_Offset , 100 + Y_Offset);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("MAX");
  tft.drawRoundRect(292 - X_Offset , 97 + Y_Offset,  23, 13 , 1, ILI9341_WHITE);

}


//>>>>>>>>>>>> CPU LOAD

void CPU_loadLevelGauge(int cpuUsage ) {

  /*Top CPU Load Level Clear Box,*/
  tft.fillRoundRect(306 - X_Offset, 0 + Y_Offset,   8, 102 , 1, ILI9341_BLACK);

  float CPUloadfactor = cpuUsage;

  /*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*/
  int CPUloadScalefactor =   ( CPUloadfactor + 1); // +1 so it always shows something


  if (CPUloadfactor >= 0 ) {
    /*Top CPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset, 1 + Y_Offset,   8,  CPUloadScalefactor   , 1, ILI9341_GREEN); // Top CPU Load Scale
  }

  if (CPUloadfactor >= 50 ) {
    /*Top CPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset, 1 + Y_Offset,   8,  CPUloadScalefactor   , 1, ILI9341_GREEN); // Top CPU Load Scale
  }

  if (CPUloadfactor >= 75) {
    /*Top CPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset, 1 + Y_Offset,   8,  CPUloadScalefactor   , 1, ILI9341_ORANGE); // Top CPU Load Scale
  }

  if (CPUloadfactor >= 83 ) {
    /*Top CPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset, 1 + Y_Offset,   8,  CPUloadScalefactor  , 1, ILI9341_RED); // Top CPU Load Scale
  }

  tft.drawRoundRect(306 - X_Offset, 0 + Y_Offset,   8,  94 , 1, ILI9341_WHITE); // Draw rectangle round CPU load bar
}


//---------------------- GPU--------------------


//>>>>>>>>>>>> GPU TEMP

void GPU_tempLevelGauge(int gpuDegree ) {

  /*Bottom GPU Temp Level Clear Box,*/
  tft.fillRoundRect(293 - X_Offset , 129 + Y_Offset,   8, 102 , 1, ILI9341_BLACK);

  float GPUtempfactor = gpuDegree;

  /*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*/
  int GPUtempScalefactor = (GPUtempfactor + 1); // +1 so it always shows something

  if (GPUtempfactor >= 0 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset , 130 + Y_Offset,  8, GPUtempScalefactor , 1, ILI9341_GREEN); // Bottom GPU Temp Scale
  }

  if (GPUtempfactor >= 25 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset , 130 + Y_Offset,  8, GPUtempScalefactor , 1, ILI9341_GREEN); // Bottom GPU Temp Scale
  }

  if (GPUtempfactor >= 50 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset , 130 + Y_Offset,  8, GPUtempScalefactor , 1, ILI9341_GREEN); // Bottom GPU Temp Scale
  }

  if (GPUtempfactor >= 75 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset , 130 + Y_Offset,  8, GPUtempScalefactor , 1, ILI9341_ORANGE); // Bottom GPU Temp Scale
  }

  if (GPUtempfactor >= 83 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset , 130 + Y_Offset,  8, GPUtempScalefactor , 1, ILI9341_RED); // Bottom GPU Temp Scale
  }

  tft.drawRoundRect(293 - X_Offset , 129 + Y_Offset,   8, 94 , 1, ILI9341_WHITE); // Draw rectangle round GPU temp bar

  /*Stop Scale running into MAX box,*/
  tft.fillRect (289 - X_Offset , 223 + Y_Offset,  27, 17 , ILI9341_BLACK);

  // Max Text box GPU
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setCursor(295 - X_Offset , 229 + Y_Offset);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("MAX");
  tft.drawRoundRect(292 - X_Offset , 226 + Y_Offset,  23, 13 , 1, ILI9341_WHITE);
}

//>>>>>>>>>>>> GPU LOAD

void GPU_loadLevelGauge(int gpuUsage ) {

  /*Bottom GPU Load Level Clear Box,*/
  tft.fillRoundRect(306 - X_Offset , 129 + Y_Offset,   8, 102 , 1, ILI9341_BLACK);

  float GPUloadfactor = gpuUsage;

  /*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*/
  int GPUloadScalefactor = (GPUloadfactor + 1); // +1 so it always shows something

  if (GPUloadfactor >= 0 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset , 130 + Y_Offset, 8, GPUloadScalefactor , 1, ILI9341_GREEN);
  }
  if (GPUloadfactor >= 25 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset , 130 + Y_Offset, 8, GPUloadScalefactor , 1, ILI9341_GREEN);
  }
  if (GPUloadfactor >= 50 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset , 130 + Y_Offset, 8, GPUloadScalefactor  , 1, ILI9341_GREEN);
  }
  if (GPUloadfactor >= 75 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset , 130 + Y_Offset, 8, GPUloadScalefactor , 1, ILI9341_ORANGE);
  }
  if (GPUloadfactor >= 90 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset , 130 + Y_Offset, 8, GPUloadScalefactor , 1, ILI9341_RED);
  }

  tft.drawRoundRect(306 - X_Offset , 129 + Y_Offset,   8, 94 , 1, ILI9341_WHITE); // Draw rectangle round GPU load bar
}
