void DisplayStyle3 () {

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

    //---------------------------------------- Static Background ----------------------------------------------------

    display.setTextSize(2); //set background txt font size
    display.setCursor(1, 12);
    display.println("CPU");
    display.setCursor(1, 38);
    display.println("GPU");
    display.setTextSize(1); //set background txt font size

    //---------------------------------------CPU & GPU Hardware ID--------------------------------------------------

    /*CPU Manual Position Test*/
    //display.setTextSize(0);
    //display.setCursor(-35, 1);// Negative spacing so, CPU ID doesn't cause a rollover, on the next line
    //String cpuName = "Intel Core i7-5820K"; // Name spacing test

    /*CPU & GPU Hardware ID*/
    display.setTextSize(0); // string font size
    String cpuName = "";
    display.println(cpuName);

    /* GPU Manual Position Test*/
    //display.setTextSize(0);
    //display.setCursor(-42, 28); // Negative spacing so, GPU ID doesn't cause a rollover, on the next line
    //String gpuName = "Nvidia GeForce GTX 1080"; // Name spacing test

    display.setTextSize(0); // string font size
    String gpuName = "";
    display.println(gpuName);

    if (inputString.indexOf("CPU") > -1)
    {
      String cpuName = "";
      display.setTextSize(1);
      display.setCursor(0, 1);
      //display.setCursor(-35, 1);

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

    //------------------------------------------ CPU Freq -------------------------------------------------

    /*CPU Freq Display String*/
    int cpuCoreClockStart = inputString.indexOf("CHC") + 3;
    int cpuCoreClockEnd = inputString.indexOf("|", cpuCoreClockStart);
    String cpuClockString = inputString.substring(cpuCoreClockStart, cpuCoreClockEnd);

    /*CPU  Freq Display*/
    display.setTextSize(2);
    display.setCursor(42, 12);
    display.print(cpuClockString);
    display.setTextSize(1);
    display.print("MHz");

    //------------------------------------------ CPU Temp -------------------------------------------------

    /*CPU Temp Display String*/
    int cpuStringStart = inputString.indexOf("C");
    int cpuDegree = inputString.indexOf("c");
    int cpuStringLimit = inputString.indexOf("|");
    String cpuString1 = inputString.substring(cpuStringStart + 1, cpuDegree);
    String cpuString2 = inputString.substring(cpuDegree + 1, cpuStringLimit - 1);

    /*CPU Temp Display*/
    display.setTextSize(1);
    display.setCursor(105, 22);
    display.print(cpuString1);
    display.setTextSize(1);
#ifdef noDegree
    display.print("C");       // Centigrade Symbol
#else
    display.print((char)247); //Degrees Symbol
    display.print("C");       // Centigrade Symbol
#endif

    //------------------------------------------ GPU Freq/Temp -------------------------------------------------

    /* GPU temp V's GPU freq to check for throttling and max 'GPU Boost' */

    /*GPU Core Freq Display String*/
    int gpuCoreClockStart = inputString.indexOf("GCC") + 3;
    int gpuCoreClockEnd = inputString.indexOf("|", gpuCoreClockStart);
    String gpuCoreClockString = inputString.substring(gpuCoreClockStart, gpuCoreClockEnd);

    /*GPU Core Temp Display String*/
    int gpuStringStart = inputString.indexOf("G", cpuStringLimit);
    int gpuDegree = inputString.indexOf("c", gpuStringStart);
    int gpuStringLimit = inputString.indexOf("|", gpuStringStart);
    String gpuString1 = inputString.substring(gpuStringStart + 1, gpuDegree);
    String gpuString2 = inputString.substring(gpuDegree + 1, gpuStringLimit - 1);

    /*GPU Memory Used*/
    int gpuMemoryUsedStart = inputString.indexOf("GMU") + 3;
    int gpuMemoryUsedEnd = inputString.indexOf("|", gpuMemoryUsedStart);
    String gpuMemoryUsedString = inputString.substring(gpuMemoryUsedStart, gpuMemoryUsedEnd);

    double gpuMemUsed = atof(gpuMemoryUsedString.c_str());
    double  gpuMemUsedSum = gpuMemUsed / 1024;


    /*GPU Power*/
    int gpuPowerStart = inputString.indexOf("GPWR") + 4;
    int gpuPowerEnd = inputString.indexOf("|", gpuPowerStart);
    String gpuPowerString = inputString.substring(gpuPowerStart, gpuPowerEnd);

    /*GPU Fan %*/
    int gpuFanStart = inputString.indexOf("GFANL") + 5;  // GPU Fan Load %
    int gpuFanEnd = inputString.indexOf("|", gpuFanStart);
    String gpuFanString = inputString.substring(gpuFanStart, gpuFanEnd);

    /*GPU Fan RPM*/
    int gpuRPMStart = inputString.indexOf("GRPM") + 4;
    int gpuRPMEnd = inputString.indexOf("|", gpuRPMStart);
    String gpuRPMString = inputString.substring(gpuRPMStart, gpuRPMEnd);

    /*GPU Core Freq Display*/
    display.setTextSize(2);
    display.setCursor(42, 38);
    //display.print("Core  :");
    display.print(gpuCoreClockString);
    display.setTextSize(1);
    display.print("MHz");


    /*GPU Fan Power Display*/

    display.setCursor(1, 57);
    display.print("Fan:");
    //display.print(gpuRPMString);// RPM
    display.print(gpuFanString);  // %
    display.print("%");
    //display.print(" P:");
    //display.print(gpuPowerString);
    //display.print("w");

    /*GPU Memory Used Display*/
    display.print(" Used:");
    //display.print(gpuMemUsedSum);      //  show values in GB
    display.print(gpuMemoryUsedString); //  show values in MB
    display.print("MB");

    /*GPU Core Temp Display*/
    display.setTextSize(1);
    display.setCursor(105, 47);
    display.print(gpuString1);
    display.setTextSize(1);

#ifdef noDegree
    display.print("C");       // Centigrade Symbol
#else
    display.print((char)247); //Degrees Symbol
    display.print("C");       // Centigrade Symbol
#endif

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
    display.println("D3");
    display.display();


    //>>>>>>>>>>>>>>>> Addition for Buttons >>>>>>>>>>>>
    inputString = "";
    stringComplete = false;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    oledDraw = 1;

  }
}
