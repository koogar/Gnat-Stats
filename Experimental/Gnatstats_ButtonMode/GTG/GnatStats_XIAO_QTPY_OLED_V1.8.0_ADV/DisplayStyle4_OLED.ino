/*
   ___  _         _           ___ _        _
  |   \(_)____ __| |__ _ _  _/ __| |_ _  _| |___
  | |) | (_-< '_ \ / _` | || \__ \  _| || | / -_)
  |___/|_/__/ .__/_\__,_|\_, |___/\__|\_, |_\___/
           |_|          |__/         |__/

   GPU: Name/ Total Memory/ Used Memory/ Temp/ Load/
   CORE MHz / Shader MHz / VRAM MHz/ Fan%/ Power(watts)
 
*/

void DisplayStyle4_OLED() { // GPU STATS ONLY


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

  //---------------------------------------CPU & GPU Hardware ID--------------------------------------------------

  /* GPU Hardware ID*/
  String gpuName = "";

  display.setTextSize(0); // string font size
  display.println(gpuName);

  if (inputString.indexOf("GPU") > -1)
  {

    display.setTextSize(0);
    display.setCursor(0, 0);
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

  //---------------------------------------------Total GPU Memory-----------------------------------------------------------
  /*GPU Total Memory String*/
  int gpuMemoryStart = inputString.indexOf("GMT") + 3;
  int gpuMemoryEnd = inputString.indexOf("|", gpuMemoryStart);
  String gpuMemoryString = inputString.substring(gpuMemoryStart, gpuMemoryEnd);

  double totalGPUmem = atof(gpuMemoryString.c_str());
  double totalGPUmemSum = totalGPUmem / 1024;    // divide by 1024 to get the correct value
  float  totalGPUmemSumDP = totalGPUmemSum ;     // float to handle the decimal point when printed (totalGPUmemSumDP, 0)

  /*GPU Total Memory DISPLAY*/
  display.setCursor(100, 0);
  //display.print(gpuMemoryString); // Show Value in MB
  display.print(totalGPUmemSumDP, 0); // Show Value in GB
  display.println("G");

  //------------------------------------------ GPU MemClock/CoreClock/Shader -------------------------------------------------

  /*GPU Core Freq String*/
  int gpuCoreClockStart = inputString.indexOf("GCC") + 3;
  int gpuCoreClockEnd = inputString.indexOf("|", gpuCoreClockStart);
  String gpuCoreClockString = inputString.substring(gpuCoreClockStart, gpuCoreClockEnd);

  int gpuMemClockStart = inputString.indexOf("GMC") + 3;
  int gpuMemClockEnd = inputString.indexOf("|", gpuMemClockStart);
  String gpuMemClockString = inputString.substring(gpuMemClockStart, gpuMemClockEnd);

  int gpuShaderClockStart = inputString.indexOf("GSC") + 3;
  int gpuShaderClockEnd = inputString.indexOf("|", gpuShaderClockStart);
  String gpuShaderClockString = inputString.substring(gpuShaderClockStart, gpuShaderClockEnd);

  /*GPU Core/VRAM/Shader Display*/
  display.setTextSize(1);
  display.setCursor(42, 34);
  display.print("Core  :");
  display.print(gpuCoreClockString);
  display.setTextSize(1);
  display.print("MHz");

  display.setCursor(42, 44);
  display.print("VRAM  :");
  display.print(gpuMemClockString);
  display.print("MHz");

  display.setCursor(42, 54);
  display.print("Shader:");
  display.print(gpuShaderClockString);
  display.print("MHz");

  //----------------------------------------- GPU Temp/Load-----------------------------------------

  /*GPU Memory Used String*/
  int gpuMemoryUsedStart = inputString.indexOf("GMU") + 3;
  int gpuMemoryUsedEnd = inputString.indexOf("|", gpuMemoryUsedStart);
  String gpuMemoryUsedString = inputString.substring(gpuMemoryUsedStart, gpuMemoryUsedEnd);

  double gpuMemUsed = atof(gpuMemoryUsedString.c_str());
  double  gpuMemUsedSum = gpuMemUsed / 1024;
  //display.print(gpuMemoryUsedString); // can show values in MB & GB need to move the decimal point

  /*CPU Temp String*/ // needed for GPU String below
  int cpuStringStart = inputString.indexOf("C");
  int cpuDegree = inputString.indexOf("c");
  int cpuStringLimit = inputString.indexOf("|");
  String cpuString1 = inputString.substring(cpuStringStart + 1, cpuDegree);
  String cpuString2 = inputString.substring(cpuDegree + 1, cpuStringLimit - 1);

  /*GPU Temp String*/
  int gpuStringStart = inputString.indexOf("G", cpuStringLimit);
  int gpuDegree = inputString.indexOf("c", gpuStringStart);
  int gpuStringLimit = inputString.indexOf("|", gpuStringStart);
  String gpuString1 = inputString.substring(gpuStringStart + 1, gpuDegree);
  String gpuString2 = inputString.substring(gpuDegree + 1, gpuStringLimit - 1);

  /*GPU Fan% String*/
  int gpuFanStart = inputString.indexOf("GFANL") + 5;  // GPU Fan Load %
  int gpuFanEnd = inputString.indexOf("|", gpuFanStart);
  String gpuFanString = inputString.substring(gpuFanStart, gpuFanEnd);

  /*GPU FAN% Display*/
  display.setTextSize(1);
  display.setCursor(1, 12); //
  display.println("Fan");
  display.setCursor(1, 22);
  display.setTextSize(1);
  display.print(gpuFanString);
  display.setTextSize(1);
  display.print("%");

  /*GPU Used Memory Display*/
  display.setTextSize(1);
  display.setCursor(27, 12);
  display.print("Memory");
  display.setCursor(27, 22);
  //display.print(gpuMemUsedSum);         //  show values in GB
  display.print(gpuMemoryUsedString); //  show values in MB
  display.setTextSize(1);
  display.print("MB");

  /*GPU DISPLAY LOAD*/
  display.setCursor(71, 12);
  display.setTextSize(1);
  display.print("Load");
  display.setCursor(71, 22);
  display.print(gpuString2);
  display.setTextSize(1);
  display.println("%");      // Small Percent Symbol

  /*GPU DISPLAY TEMPERATURE*/
  display.setTextSize(1);
  display.setCursor(102, 12);
  display.print("Temp");
  display.setCursor(103, 22);
  display.print(gpuString1);
  display.setTextSize(1);

  /*GPU Centigrade*/
#ifdef noDegree
  display.print("C");       // Centigrade Symbol
#else
  display.print((char)247); //Degrees Symbol
  display.print("C");       // Centigrade Symbol
#endif
  //------------------------------------------------GPU Power Consumption (watts) Nvidia---------------------------------------------

  /*GPU Nvidia Power String*/
  int gpuPowerStart = inputString.indexOf("GPWR") + 4;
  int gpuPowerEnd = inputString.indexOf("|", gpuPowerStart);
  String gpuPowerString = inputString.substring(gpuPowerStart, gpuPowerEnd);

  /*GPU Display Power*/
  display.setCursor(1, 32); //
  display.println("-----");
  display.setTextSize(1);
  display.setCursor(1, 42); //
  display.println("Power");
  display.setTextSize(1);
  display.setCursor(1, 54); //
  display.print(gpuPowerString);
  display.print("w");

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
    display.println("D4");

    display.display();

    //>>>>>>>>>>>>>>>> Addition for Buttons >>>>>>>>>>>>
    inputString = "";
    stringComplete = false;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    oledDraw = 1;

  }
}
