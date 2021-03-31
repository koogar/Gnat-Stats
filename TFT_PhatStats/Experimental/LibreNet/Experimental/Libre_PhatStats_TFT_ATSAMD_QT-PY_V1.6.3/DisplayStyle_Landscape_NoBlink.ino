
/*

   _____  _           _               _                     _
  |  __ \(_)         | |             | |                   | |
  | |  | |_ ___ _ __ | | __ _ _   _  | |     __ _ _ __   __| |___  ___ __ _ _ __   ___
  | |  | | / __| '_ \| |/ _` | | | | | |    / _` | '_ \ / _` / __|/ __/ _` | '_ \ / _ \
  | |__| | \__ \ |_) | | (_| | |_| | | |___| (_| | | | | (_| \__ \ (_| (_| | |_) |  __/
  |_____/|_|___/ .__/|_|\__,_|\__, | |______\__,_|_| |_|\__,_|___/\___\__,_| .__/ \___|
              | |             __/ |                                       | |
              |_|            |___/                                        |_|
*/

/*Optimised for ILI9341 320 x 240 in landscape*/

void DisplayStyle_Landscape_NoBlink () {

  serialEvent();
  activityChecker();

  /* TFT DRAW STATS */
  if (stringComplete) {

    if (bootMode) {

      //splashScreen2();

      tft.fillScreen(ILI9341_BLACK);
      bootMode = false;
    }

    lastActiveConn = millis();


    //--------------------------------------- Display Background ----------------------------------------------------

    backlightON (); //Turn ON display when there is  activity


    tft.setRotation(3);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
    tft.setFont(); // set to default Adafruit library font
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);

#ifdef Debug
    tft.setTextColor(ILI9341_WHITE, ILI9341_RED); // used to stop flickering when updating digits that do not increase in length. CPU/GPU load still need a clear box on the end digits
#endif


    /* Display Background */
    //----------------------------------------- Boost/Turbo Clear Box----------------------------------------------


    /* CPU Portrait TURBO/TJMAX, */
    tft.fillRoundRect  (107, 91, 86, 20, 4, ILI9341_BLACK);   //
    tft.drawRoundRect  (106, 90, 88, 22, 4, ILI9341_SILVER); //

    /* GPU Portrait BOOST/TJMAX, */
    tft.fillRoundRect  (107, 210, 86, 20, 4, ILI9341_BLACK);   //
    tft.drawRoundRect  (106, 209, 88, 22, 4, ILI9341_SILVER); //

    /* CPU  Freq Line */
    tft.drawFastHLine(110, 50, 200,  ILI9341_SILVER);

    /*GPU Memory Used Line */
    tft.drawFastHLine(110, 170, 200, ILI9341_SILVER);

    //--------------------------------------Borders----------------------------------------

    /* (X  ,Y ,  W ,  H , Radius ,    Color*/

    /* CPU Outline, */
    tft.drawRoundRect  (13,  22, 88,  89, 6,    ILI9341_WHITE);

    /* GPU Outline, */
    tft.drawRoundRect  (13, 144, 88,  89, 6,    ILI9341_WHITE);

    tft.drawRoundRect  (0,   0  , 320, 120, 8,    ILI9341_BLUE);

    tft.drawRoundRect  (0, 124, 320, 116, 8,    ILI9341_GREEN);


    //------------------------------------CPU/GPU/RAM BMP IMAGES--------------------------------------------

    /* Blank CPU PCB BMP, */
    tft.drawBitmap(16, 25, CPU3_BMP, 82, 82, ILI9341_GREEN);

#ifdef INTEL_CPU
    //tft.drawBitmap(16, 25, IntelCoreOnly_BMP, 88, 82, ILI9341_BLUE);
    tft.drawBitmap(16, 25, IntelCoreOnly_BMP, 88, 82, ILI9341_SILVER);
#endif

#ifdef AMD_CPU
    tft.drawBitmap(16, 25, AMDCoreOnly_BMP, 88, 82, ILI9341_RED);
#endif


    tft.setTextSize(1);
    tft.setCursor(116, 8); // (Left/Right, UP/Down)
    tft.println("Temp     /     Load"); // CPU

    tft.setTextSize(1);
    tft.setCursor(200, 130);
    tft.println("Load  /  Fan Load"); // GPU

    tft.setTextSize(3);
    tft.setCursor(1, 132); // (Left/Right, UP/Down)

#ifdef NVIDIA_GRAPHICS
    tft.drawBitmap(16, 148, Nvidia_Logo_BMP, 82, 82, ILI9341_GREEN); // Nvidia Logo
#endif

#ifdef AMD_GRAPHICS
    tft.drawBitmap(16, 148, RADEON_Logo_BMP, 82, 82, ILI9341_RED); // Nvidia Logo
#endif

#ifdef INTEL_GRAPHICS
    //tft.fillRoundRect  (14, 141, 86,  87, 5,    ILI9341_BLUE);  // INTEL GPU Logo
    tft.drawBitmap(13, 147, IntelCoreOnly_BMP, 88, 82, ILI9341_BLUE);
#endif


    //---------------------------------------CPU & GPU Hardware ID---------------------------------------------------------

    /* CPU & GPU Hardware ID */

    if (inputString.indexOf("CPU") > -1)
    {
      String cpuName = "";
      tft.setTextSize(1);
      tft.setCursor(16, 8);// (Left/Right, UP/Down)
      //tft.setCursor(-35, 1);

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
      tft.println(cpuName);

    }
    if (inputString.indexOf("GPU") > -1)
    {
      tft.setTextSize(1);
      tft.setCursor(16, 130);  // Position GPU Name
      //tft.setCursor(-41, 28);   // Negative spacing so, Nvidia doesn't cause a rollover, on the next line
      int gpuNameStart = inputString.indexOf("GPU:");
      if (inputString.indexOf("NVIDIA", gpuNameStart) > -1) {
        gpuNameStart = gpuNameStart + gpuNameStartLength;
      }
      else {
        gpuNameStart = gpuNameStart + 8;
      }

      int gpuNameEnd = inputString.indexOf("|", gpuNameStart);
      String gpuName = inputString.substring(gpuNameStart, gpuNameEnd);
      tft.println(gpuName);
    }

    //------------------------------------------------------RX indicator---------------------------------------------------

    tft.setCursor(284, 9);
    tft.print("RX");
    tft.fillCircle(306, 12, 7, ILI9341_RED);// Landscape Flash RX top right corner when updating
    tft.drawCircle(306, 12, 8, ILI9341_WHITE);

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
    tft.setCursor(109 , 25);// (Left/Right, UP/Down)
    tft.print(cpuString1);  // CPU TEMP
    //tft.println("100"); // Test Spacing
    tft.setTextSize(1);

#ifdef noDegree
    tft.print("C");       // Centigrade Symbol
#else
    tft.print((char)247); //Degrees Symbol
    tft.print("C");       // Centigrade Symbol
#endif

    /* CPU LOAD, ALL CORES */
    tft.setTextSize(3);
    tft.setCursor(154 , 25);// (Left/Right, UP/Down)
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
    tft.setCursor(105, 55);// (Left/Right, UP/Down)
    tft.print(cpuClockString);
    tft.setTextSize(1);
    tft.print("MHz");

    /* CPU OVERCLOCK Display Freq Gain */
    //tft.setCursor(225, 48);// (Left/Right, UP/Down)
    //tft.setTextSize(1);
    //tft.print ("CPU O/C: ");
    //tft.print(cpuOverclockSum, 0); // Show Value in MHZ
    //tft.println ("MHz");

#ifdef  enable_ShowFrequencyGain

    /* CPU OVERCLOCK Display Freq Gain in MHz */
    tft.setCursor(109, 94);// (Left/Right, UP/Down)

    //tft.print ("O/C:+ ");

#ifdef ShowFrequencyGainMHz
    tft.setTextSize(2);
    tft.print ("+");
    tft.print(cpuOverclockSum, 0);            // Show Value in MHz
    tft.println ("MHz");
#endif
#ifdef ShowFrequencyGain%
    tft.setTextSize(2);
    tft.print (" +");
    tft.print(cpuOverclockGainPercentSum, 0); // Show Value in %
    tft.println ("%");
#endif
#endif


    //--------------------------------------- CPU FAN NOT WORKING!!!--------------------------------------------

    /*CPU FAN String, Libre CFL{CpuFanSpeedLoad}
      int cpuFanStart = inputString.indexOf("CF") + 2;
      int cpuFanEnd = inputString.indexOf("|", cpuFanStart);
      String cpuFanString = inputString.substring(cpuFanStart, cpuFanEnd);
      //Char erase and spacing adjust, MaDerer
      while (cpuFanString.length() < 3) cpuFanString = " " + cpuFanString;
    */
    /*CPU FAN Display
      tft.setTextSize(1);
      tft.setCursor(215, 9);// (Left/Right, UP/Down)
      tft.setTextSize(1);
      tft.print("/ Fan Load");

      tft.setTextSize(3);
      tft.setCursor(245, 25);// (Left/Right, UP/Down)
      //tft.print("49");
      tft.print(cpuFanString); //CPU FAN NOT WORKING!!!

      #ifdef  smallPercent
      tft.setTextSize(2);
      tft.print("%");
      #else
      tft.setTextSize(3);
      tft.print("%");
      #endif
    */
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
    tft.setCursor(109, 144);// (Left/Right, UP/Down)
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
    tft.setCursor(154 , 144); // (Left/Right, UP/Down)
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

    /* GPU VRAM Freq, */
    int gpuMemClockStart = inputString.indexOf("GMC") + 3;
    int gpuMemClockEnd = inputString.indexOf("|", gpuMemClockStart);
    String gpuMemClockString = inputString.substring(gpuMemClockStart, gpuMemClockEnd);

    /* GPU SHADER Freq, */
    int gpuShaderClockStart = inputString.indexOf("GSC") + 3;
    int gpuShaderClockEnd = inputString.indexOf("|", gpuShaderClockStart);
    String gpuShaderClockString = inputString.substring(gpuShaderClockStart, gpuShaderClockEnd);

    /* GPU OVERCLOCK Freq Gain in MHz, */
    double gpuOverclockGain = atof(gpuCoreClockString.c_str());
    double  gpuOverclockSum = gpuOverclockGain - GPU_BOOST; //values in Mhz

    /* GPU OVERCLOCK Freq Gain in Percent, eg: 1683MHz/100 = 16.83MHz(1%) , (OC Gain)254MHz / 16.83MHz(1%) = 15.09%,*/
    double gpuOverclockGainPercentSum = gpuOverclockSum / (GPU_BOOST / 100); // % of gain over Stock GPU


#ifdef  enable_ShowFrequencyGain
    /* GPU OVERCLOCK Display Freq Gain, */
    //tft.setCursor(225, 56);// (Left/Right, UP/Down)
    tft.setCursor(109, 213);
    //tft.print ("GPU O/C: ");

#ifdef ShowFrequencyGainMHz
    tft.setTextSize(2);
    tft.print ("+");
    tft.print(gpuOverclockSum, 0);            // Show Value in MHz
    tft.println ("MHz");
#endif
#ifdef ShowFrequencyGain%
    tft.setTextSize(2);
    tft.print ("  +");
    tft.print(gpuOverclockGainPercentSum, 0); // Show Value in %
    tft.println ("%");
#endif

#endif


    tft.setCursor(200, 180);// (Left/Right, UP/Down)
    tft.setTextSize(1);
    tft.print("VRAM     :");
    tft.print(gpuMemClockString);

    tft.setTextSize(1);
    tft.print("MHz");

    tft.setCursor(200, 190); // (Left/Right, UP/Down)
    tft.setTextSize(1);
    tft.print("Shader   :");
    tft.print(gpuShaderClockString);

    tft.setTextSize(1);
    tft.print("MHz");

    tft.setTextSize(1);
    tft.setCursor(200, 200);  // (Left/Right, UP/Down)
    tft.print("Core     :");
    tft.print(gpuCoreClockString);

    tft.setTextSize(1);
    tft.print("MHz");       // Centigrade Symbol

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
    tft.setCursor(120, 130);  // Position GPU Total Memory
    tft.print(totalGPUmemSumDP, 0); // Show Value in GB

    tft.setTextSize(1);
    tft.print("GB");
    //----------------------------------------------GPU Memory Used----------------------------------------------------------

    /*GPU Memory Used */
    int gpuMemoryUsedStart = inputString.indexOf("GMU") + 3;
    int gpuMemoryUsedEnd = inputString.indexOf("|", gpuMemoryUsedStart);
    String gpuMemoryUsedString = inputString.substring(gpuMemoryUsedStart, gpuMemoryUsedEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuMemoryUsedString.length() < 4) gpuMemoryUsedString = " " + gpuMemoryUsedString;

    tft.setCursor(109, 179);    // (Left/Right, UP/Down)
    tft.setTextSize(3);
    tft.print(gpuMemoryUsedString); //  show values in MB

    tft.setTextSize(1);
    tft.print("MB");

    /*
      double gpuMemUsed = atof(gpuMemoryUsedString.c_str()); //values in MB
      double  gpuMemUsedSumGB = gpuMemUsed / 1024; //values in GB

      end of GPU total memory, Use fill box on last char "B" as its not a string
      tft.fillRect(163, 179, 34, 25, ILI9341_updateBox);   //  GPU Used Memory Character Erase

      tft.print(gpuMemUsedSumGB); //  show values in GB
      tft.setTextSize(0); tft.print("GB");
    */


    //------------------------------------------------GPU Power Consumption--------------------------------------------------------
#ifdef enable_gpuPowerStats

    /* GPU Power */  // Nvidia Driver 457.51 works. Broken in Driver Version: 460.79 460.89
    int gpuPowerStart = inputString.indexOf("GPWR") + 4;
    int gpuPowerEnd = inputString.indexOf("|", gpuPowerStart);
    String gpuPowerString = inputString.substring(gpuPowerStart, gpuPowerEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuPowerString.length() < 6) gpuPowerString = " " + gpuPowerString;

    tft.setTextSize(1);
    tft.setCursor(200, 222);   // (Left/Right, UP/Down)
    tft.print("Power    :");
    tft.print(gpuPowerString); //GPU Power Watts

    tft.setTextSize(1);
    tft.print("w");
#endif

    //------------------------------------------------GPU FAN Speed Percentage-------------------------------------------------------
#ifdef enable_gpuFanStats%
    /* GPU Fan Load% */
    int gpuFanStart = inputString.indexOf("GFANL") + 5;  //
    int gpuFanEnd = inputString.indexOf("|", gpuFanStart );
    String gpuFanString = inputString.substring(gpuFanStart, gpuFanEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuFanString.length() < 3) gpuFanString = " " + gpuFanString;

    tft.setTextSize(3);
    tft.setCursor(242, 144);   // (Left/Right, UP/Down)
    //tft.print("Fan Load :");
    tft.print(gpuFanString);   //GPU Fan %

#ifdef  smallPercent
    tft.setTextSize(2);
    tft.print("%");
#else
    tft.setTextSize(3);
    tft.print("%");
#endif
#endif

#ifdef enable_gpuFanStatsRPM
    /* GPU Fan RPM */
    int gpuRPMStart = inputString.indexOf("GRPM") + 4;
    int gpuRPMEnd = inputString.indexOf("|", gpuRPMStart);
    String gpuRPMString = inputString.substring(gpuRPMStart, gpuRPMEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuRPMString.length() < 4) gpuRPMString = " " + gpuRPMString;

    tft.setTextSize(1);
    //tft.setCursor(150, 120); // (Left/Right, UP/Down)
    tft.setCursor(200, 210);   // (Left/Right, UP/Down)
    tft.print("Fan Speed:");
    tft.print(gpuRPMString);   //GPU Fan RPM

    tft.setTextSize(1);
    tft.print("RPM");
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

    tft.setTextSize(1);
    tft.setCursor(224 , 65); // (Left/Right, UP/Down)
    tft.println("System RAM");

    tft.drawFastHLine(220, 75, 71, ILI9341_SILVER);
    tft.setTextSize(1);

    tft.setCursor(220 , 80); // (Left/Right, UP/Down)
    tft.println("TOTAL / USED");

    tft.setCursor(206, 94); // (Left/Right, UP/Down)
    tft.setTextSize(2);
    tft.print(intRamSum, 0) ; tft.setTextSize(0); tft.print("GB"); tft.print(" ");
    tft.setTextSize(2);
    tft.print(ramString)    ; tft.setTextSize(0); tft.print("GB");

    //------------------------------------------ RX indicator Clear------------------------------------------------

    tft.fillCircle(306, 12, 7, ILI9341_BLACK);// Flash top right corner when updating

    //-------------------------------------------------------------------------------------------------------------

    displayDraw = 1;

    //--------------------------Trigger an event when CPU or GPU threshold is met ---------------------------------

#ifdef enable_BoostIndicator
    CustomTriggerCPU_BOOST_LSNB( cpuClockString.toInt     ()); // CPU Frequency
    CustomTriggerGPU_BOOST_LSNB( gpuCoreClockString.toInt ()); // GPU Frequency
#endif

#ifdef enable_ThrottleIndicator
    CustomTriggerCPU_ThrottleIndicator_LSNB( cpuString1.toInt() ); //  CPU TJMax/Throttle Incicator BMP
    CustomTriggerGPU_ThrottleIndicator_LSNB( gpuString1.toInt() ); //  GPU TJMax/Throttle Incicator BMP
#endif

#ifdef enableNeopixelGauges

    CPU_loadGauge( cpuString2.toInt() ); // Neopixel Ring Gauge  CPU  Load
    //CPU_tempGauge( cpuString1.toInt() ); // Neopixel Ring Gauge  CPU  Temperature

    GPU_loadGauge( gpuString2.toInt() ); // Neopixel Ring Gauge  GPU  Load
    //GPU_tempGauge( gpuString1.toInt() ); // Neopixel Ring Gauge  GPU  Temperature

#endif
    inputString = "";
    stringComplete = false;
    //tft.fillScreen(ILI9341_BLACK);

  }
}


/*
    _____          _                    _______   _
   / ____|        | |                  |__   __| (_)
  | |    _   _ ___| |_ ___  _ __ ___      | |_ __ _  __ _  __ _  ___ _ __ ___
  | |   | | | / __| __/ _ \| '_ ` _ \     | | '__| |/ _` |/ _` |/ _ \ '__/ __|
  | |___| |_| \__ \ || (_) | | | | | |    | | |  | | (_| | (_| |  __/ |  \__ \
   \_____\__,_|___/\__\___/|_| |_| |_|    |_|_|  |_|\__, |\__, |\___|_|  |___/
                                                    __/ | __/ |
                                                   |___/ |___/

  Custom Trigger functions, when CPU or GPU threshold are met
*/


// -------------------  CPU Throttle Indicator Event Landscape --------------------

void CustomTriggerCPU_ThrottleIndicator_LSNB(int cpuDegree ) {  // i5-9600k TJMax is 100c
  float CPUtempfactor = cpuDegree ;

  if (CPUtempfactor >= CPU_TJMAX ) {  // TJ Max for the Intel 9900K 100c

    /* CPU Junction Max Throttle Temp, */
    tft.fillRoundRect  (107, 91, 86, 20, 4, ILI9341_RED);   //
    tft.setTextSize(2);
    tft.setCursor(121, 94);
    tft.setTextColor(ILI9341_BLACK);

    tft.println("TJMax"); // CPU Turbo Clock
  }
}

// -------------------  GPU Throttle Indicator Event Landscape --------------------

void CustomTriggerGPU_ThrottleIndicator_LSNB(int gpuDegree ) {
  float GPUtempfactor = gpuDegree ;

  if (GPUtempfactor >= GPU_TJMAX ) {  //GTX 1080 TJMax = 83c

    /* GPU Junction Max Throttle Temp, */
    tft.fillRoundRect  (107, 210, 86, 20, 4, ILI9341_RED);   //

    tft.setTextSize(2);
    tft.setCursor(121, 213);
    tft.setTextColor(ILI9341_BLACK);

    tft.println("TJMax"); // GPU Boost Clock

  }
}

// -------------------  CPU Turbo Boost Indicator Event Landscape --------------------

void CustomTriggerCPU_BOOST_LSNB(int cpuClockString ) {
  float CPUboostfactor = cpuClockString;

  delay(350); // Small delay so Turbo frequency gains stay on screen longer
  tft.drawRoundRect  (106, 90, 88, 22, 4, ILI9341_WHITE); //

  if (CPUboostfactor >  CPU_BOOST) {  // i5-9600k boost is 3700Mhz to 4700Mhz
    //Do Something!!!

#ifdef CPU_OverClocked //Do Nothing!!

    tft.fillRoundRect  (107, 91, 86, 20, 4, ILI9341_BLACK);   //
    tft.setTextSize(1);
    tft.setCursor(118, 97);
    tft.setTextColor(ILI9341_WHITE);
    tft.println("OVERCLOCKED"); // CPU Turbo Clock

#else

    /* CPU Turbo Clock, */
    tft.fillRoundRect  (107, 91, 86, 20, 4, ILI9341_GREEN);   //
    tft.setTextSize(2);
    tft.setCursor(121, 94);
    tft.setTextColor(ILI9341_BLACK);
    tft.println("TURBO");
#endif

  }
}

// -------------------  GPU Boost Clock Indicator Event Landscape --------------------

void CustomTriggerGPU_BOOST_LSNB(int gpuCoreClockString ) {

  float GPUboostfactor = gpuCoreClockString ;

  tft.drawRoundRect  (106, 209, 88, 22, 4, ILI9341_WHITE); //

  if (GPUboostfactor >  GPU_BOOST) {  //GTX 1080 boost = 1607Mhz to 1733mhz

    /* GPU Boost Clock, */
    tft.fillRoundRect  (107, 210, 86, 20, 4, ILI9341_GREEN);   //

    tft.setTextSize(2);
    tft.setCursor(121, 213);
    tft.setTextColor(ILI9341_BLACK);

    tft.println("BOOST");
  }
}
