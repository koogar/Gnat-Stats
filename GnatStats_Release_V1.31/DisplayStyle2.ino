/*
   ___ ___ ___ ___ _      ___   __  ___  ___ ___ ___ ___ _  _   ___
  |   \_ _/ __| _ \ |    /_\ \ / / / __|/ __| _ \ __| __| \| | |_  )
  | |) | |\__ \  _/ |__ / _ \ V /  \__ \ (__|   / _|| _|| .` |  / /
  |___/___|___/_| |____/_/ \_\_|   |___/\___|_|_\___|___|_|\_| /___|

*/
void DisplayStyle2 () {

  //---------------------------------------- Static Background ----------------------------------------------------

  display.setTextSize(2); //set background txt font size
  display.setCursor(1, 12);
  display.println("CPU");
  display.setCursor(1, 38);
  display.println("GPU");
  display.setTextSize(1); //set background txt font size

  display.display();

  //-------------------------------------------Clearing Boxes ----------------------------------------------------

  /*CPU/GPU/RAM  Clearing Boxes, eg: display.fillRect(<X>, ^Y^, W, H, Color);*/
  display.fillRect(38, 11, 90, 18, BLACK);  // fill CPU live stats section only
  display.fillRect(82, 37, 46, 25, BLACK);  // fill GPU Freq live stats section only
  display.fillRect( 0, 54, 35, 10, BLACK);   // fill GPU Temp live stats section only

  /* Position Test*/
  //display.drawRect(38, 11, 90, 16, WHITE); // fill CPU live stats section only
  //display.drawRect(82, 37, 46, 25, WHITE); // fill GPU Freq live stats section only
  //display.drawRect(0,  54, 35, 10, WHITE);  // fill GPU Temp live stats section only


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
      cpuNameStart = cpuNameStart + 10;
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
    display.println(cpuName);

  }
  if (inputString.indexOf("GPU") > -1)
  {
    display.setTextSize(0);

    display.setCursor(0, 28);
    //display.setCursor(-41, 28); // Negative spacing so, Nvidia doesn't cause a rollover, on the next line
    int gpuNameStart = inputString.indexOf("GPU:");
    if (inputString.indexOf("NVIDIA", gpuNameStart) > -1) {
      gpuNameStart = gpuNameStart + 11;
    }
    else {
      gpuNameStart = gpuNameStart + 8;
    }


    int gpuNameEnd = inputString.indexOf("|", gpuNameStart);
    String gpuName = inputString.substring(gpuNameStart, gpuNameEnd);
    display.println(gpuName);
  }




  //------------------------------------------ CPU Freq -------------------------------------------------

  /*CPU Freq Display String*/
  int cpuCoreClockStart = inputString.indexOf("CHC") + 3;
  int cpuCoreClockEnd = inputString.indexOf("|", cpuCoreClockStart);
  String cpuClockString = inputString.substring(cpuCoreClockStart, cpuCoreClockEnd);

  /*CPU Core Freq*/
  display.setTextSize(2);
  display.setCursor(42, 12);
  display.print(cpuClockString);
  display.setTextSize(1);
  display.print("MHz");

  //------------------------------------------ CPU Temp -------------------------------------------------

  /*CPU Display String*/
  int cpuStringStart = inputString.indexOf("C");
  int cpuDegree = inputString.indexOf("c");
  int cpuStringLimit = inputString.indexOf("|");
  String cpuString1 = inputString.substring(cpuStringStart + 1, cpuDegree);
  String cpuString2 = inputString.substring(cpuDegree + 1, cpuStringLimit - 1);

  /*CPU TEMPERATURE*/
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

  /*GPU Core Freq*/
  int gpuCoreClockStart = inputString.indexOf("GCC") + 3;
  int gpuCoreClockEnd = inputString.indexOf("|", gpuCoreClockStart);
  String gpuCoreClockString = inputString.substring(gpuCoreClockStart, gpuCoreClockEnd);

  int gpuMemClockStart = inputString.indexOf("GMC") + 3;
  int gpuMemClockEnd = inputString.indexOf("|", gpuMemClockStart);
  String gpuMemClockString = inputString.substring(gpuMemClockStart, gpuMemClockEnd);

  int gpuShaderClockStart = inputString.indexOf("GSC") + 3;
  int gpuShaderClockEnd = inputString.indexOf("|", gpuShaderClockStart);
  String gpuShaderClockString = inputString.substring(gpuShaderClockStart, gpuShaderClockEnd);


  display.setTextSize(1);
  display.setCursor(42, 38);
  display.print("Core  :");
  display.print(gpuCoreClockString);
  display.setTextSize(1);
  display.print("MHz");       // Centigrade Symbol
  display.setCursor(42, 46);
  display.print("VRAM  :");
  display.print(gpuMemClockString);
  display.print("MHz");
  display.setCursor(42, 54);
  display.print("Shader:");
  display.print(gpuShaderClockString);
  display.print("MHz");

  // GPU Temp


  /*GPU Display String*/
  int gpuStringStart = inputString.indexOf("G", cpuStringLimit);
  int gpuDegree = inputString.indexOf("c", gpuStringStart);
  int gpuStringLimit = inputString.indexOf("|", gpuStringStart);
  String gpuString1 = inputString.substring(gpuStringStart + 1, gpuDegree);
  String gpuString2 = inputString.substring(gpuDegree + 1, gpuStringLimit - 1);

  /*GPU TEMPERATURE*/
  display.setTextSize(1);
  display.setCursor(1, 56);
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
  display.println("D2");

  display.display();

  oledDraw = 1;

}
