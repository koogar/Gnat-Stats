/*
   ___  _         _           ___ _        _
  |   \(_)____ __| |__ _ _  _/ __| |_ _  _| |___
  | |) | (_-< '_ \ / _` | || \__ \  _| || | / -_)
  |___/|_/__/ .__/_\__,_|\_, |___/\__|\_, |_\___/
           |_|          |__/         |__/

   CPU: Name/Big Temp /Big Load
   GPU: Name/GPU Total Memory /Big Temp /Big Load
   RAM: System Memory Used / Memory Total

*/

void DisplayStyle1_OLED () {

#ifdef OLED_SH1106
  display.setTextColor(SH110X_WHITE);
#endif

#ifdef OLED_SH1106_SPI
  display.setTextColor(SH110X_WHITE);
#endif

  //>>>>>>>>>>>>>>>> Addition for Buttons >>>>>>>>>>>>>>
  /* OLED DRAW STATS */
  if (stringComplete) {

    if (bootMode) {

      display.clearDisplay();
      display.display();

      bootMode = false;
    }

    lastActiveConn = millis();
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    //-------------------------------------------Clearing Box ----------------------------------------------------

    //Clearing Boxes, eg: display.fillRect(<X>, ^Y^, W, H, Color);*/
    display.fillRect (0, 0, 128, 64, BLACK); // Clear entire screen for testing

    //--------------------------------------- Display Background ----------------------------------------------------

    /* OLED Background */
    display.setTextSize(2); //set background txt font size
    display.setCursor(1, 12);
    display.println("CPU");
    display.setCursor(1, 38);
    display.println("GPU");
    display.setTextSize(1); //set background txt font size
    display.setCursor(1, 56);
    display.println("SYSRAM: ");

    //---------------------------------------CPU & GPU Hardware ID----------------------------------------------------

    /*CPU & GPU Hardware ID*/
    display.setTextSize(0); // string font size
    String cpuName = "";
    display.println(cpuName);

    display.setTextSize(0); // string font size
    String gpuName = "";
    display.println(gpuName);

    if (inputString.indexOf("CPU") > -1)
    {
      String cpuName = "";
      display.setTextSize(1);
      display.setCursor(0, 1);

      int cpuNameStart = inputString.indexOf("CPU:");
      if (inputString.indexOf("Intel", cpuNameStart) > -1) {
        cpuNameStart = cpuNameStart + cpuNameStartLength;;
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

      /* CPU Manual Name*/
#ifdef Manual_cpuName
      display.println(set_CPUname);
#else
      /* CPU Auto Detect Name*/
      display.println(cpuName);
#endif

    }
    if (inputString.indexOf("GPU") > -1)
    {
      display.setTextSize(0);

      display.setCursor(0, 28);
      //display.setCursor(-41, 28); // Negative spacing so, Nvidia doesn't cause a rollover, on the next line
      int gpuNameStart = inputString.indexOf("GPU:");
      if (inputString.indexOf("NVIDIA", gpuNameStart) > -1) {
        gpuNameStart = gpuNameStart + gpuNameStartLength;;
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
      display.println(gpuName);
    }

    //------------------------------------------ CPU Load/Temp -------------------------------------------------

    /*CPU Display String*/
    int cpuStringStart = inputString.indexOf("C");
    int cpuDegree = inputString.indexOf("c");
    int cpuStringLimit = inputString.indexOf("|");
    String cpuString1 = inputString.substring(cpuStringStart + 1, cpuDegree);
    String cpuString2 = inputString.substring(cpuDegree + 1, cpuStringLimit - 1);

    /*CPU TEMPERATURE*/
    display.setTextSize(2);
    display.setCursor(42, 12);
    display.print(cpuString1);
    display.setTextSize(1);

#ifdef noDegree
    display.print("C");       // Centigrade Symbol
#else
    display.print((char)247); //Degrees Symbol
    display.print("C");       // Centigrade Symbol
#endif

    /*CPU LOAD, ALL CORES*/
    display.setTextSize(2);
    display.print(cpuString2);
    display.setTextSize(1);
    display.println("%");    // Small Percent Symbol

    //------------------------------------------ GPU Load/Temp -------------------------------------------------

    /*GPU Display String*/
    int gpuStringStart = inputString.indexOf("G", cpuStringLimit);
    int gpuDegree = inputString.indexOf("c", gpuStringStart);
    int gpuStringLimit = inputString.indexOf("|", gpuStringStart);
    String gpuString1 = inputString.substring(gpuStringStart + 1, gpuDegree);
    String gpuString2 = inputString.substring(gpuDegree + 1, gpuStringLimit - 1);

    /*GPU TEMPERATURE*/
    display.setTextSize(2);
    display.setCursor(42, 38);
    display.print(gpuString1);
    display.setTextSize(1);

#ifdef noDegree
    display.print("C");       // Centigrade Symbol
#else
    display.print((char)247); //Degrees Symbol
    display.print("C");       // Centigrade Symbol
#endif

    /*GPU LOAD*/
    display.setTextSize(2);
    display.print(gpuString2);
    display.setTextSize(1);
    display.println("%");      // Small Percent Symbol

    //---------------------------------------------Total GPU Memory-----------------------------------------------------------

    int gpuMemoryStart = inputString.indexOf("GMT") + 3;
    int gpuMemoryEnd = inputString.indexOf("|", gpuMemoryStart);
    String gpuMemoryString = inputString.substring(gpuMemoryStart, gpuMemoryEnd);

    double totalGPUmem = atof(gpuMemoryString.c_str());
    double totalGPUmemSum = totalGPUmem / 1024;    // divide by 1024 to get the correct value
    float  totalGPUmemSumDP = totalGPUmemSum ;     // float to handle the decimal point when printed (totalGPUmemSumDP, 0)

    display.setCursor(103, 28);
    ////display.print(gpuMemoryString); // Show Value in MB
    //display.print(totalGPUmemSumDP, 0); // Show Value in GB

#ifdef Manual_gpuRam
    display.print(set_GPUram);
#else
    display.print(totalGPUmemSumDP, 0); // Show Value in GB
#endif

    display.println("GB");
    //----------------------------------------SYSTEM  RAM TOTAL---------------------------------------------------
    /*SYSTEM RAM String*/
    int ramStringStart = inputString.indexOf("R", gpuStringLimit);
    int ramStringLimit = inputString.indexOf("|", ramStringStart);
    String ramString = inputString.substring(ramStringStart + 1 , ramStringLimit);


    /*SYSTEM RAM AVALABLE String*/
    int AramStringStart = inputString.indexOf("RA", ramStringLimit);
    int AramStringLimit = inputString.indexOf("|", AramStringStart);
    String AramString = inputString.substring(AramStringStart + 2 , AramStringLimit);

    /*SYSTEM RAM TOTAL String*/
    double intRam = atof(ramString.c_str());
    double intAram = atof(AramString.c_str());
    //double  intRamSum = intRam + intAram;
    float  intRamSum = intRam + intAram; //float to handle the decimal point when printed (intRamSum,0)

    /*RAM USED/TOTAL*/
    display.setCursor(42, 56);
    display.print(intRamSum, 0); display.print(" / "); display.print(ramString); //display.print("GB");

    //--------------------------Trigger an event when CPU or GPU threshold is met ---------------------------------


#ifdef uVol_enableThesholdtriggers

    //uVol_TriggerCPU_temp( cpuString1.toInt() ); // Neopixel CPU  Temperature
    uVol_TriggerCPU_load( cpuString2.toInt() ); // Neopixel CPU  Load

    //uVol_TriggerGPU_temp( gpuString1.toInt() ); // Neopixel GPU  Temperature
    uVol_TriggerGPU_load( gpuString2.toInt() ); // Neopixel GPU  Load

#endif

#ifdef enableCustomThesholdtriggers

    CustomTriggerCPU_temp( cpuString1.toInt() ); // Neopixel CPU  Temperature
    CustomTriggerCPU_load( cpuString2.toInt() ); // Neopixel CPU  Load

    CustomTriggerGPU_temp( gpuString1.toInt() ); // Neopixel GPU  Temperature
    CustomTriggerGPU_load( gpuString2.toInt() ); // Neopixel GPU  Load

#endif

#ifdef enableNeopixelGauges

    CPU_loadGauge( cpuString2.toInt() ); // Neopixel Ring Gauge  CPU  Load
    //CPU_tempGauge( cpuString1.toInt() ); // Neopixel Ring Gauge  CPU  Temperature

    GPU_loadGauge( gpuString2.toInt() ); // Neopixel Ring Gauge  GPU  Load
    //GPU_tempGauge( gpuString1.toInt() ); // Neopixel Ring Gauge  GPU  Temperature

#endif

    display.setTextSize(1);
    display.setCursor(115, 1);
    //display.drawCircle(115, 4, 4,WHITE); // Flash top right corner when updating

    display.println("D1");
    display.display();

    //>>>>>>>>>>>>>>>> Addition for Buttons >>>>>>>>>>>>
    inputString = "";
    stringComplete = false;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    oledDraw = 1;

  }
}
