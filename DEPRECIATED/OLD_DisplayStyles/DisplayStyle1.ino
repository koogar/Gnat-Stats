/*
   ___ ___ ___ ___ _      ___   __  ___  ___ ___ ___ ___ _  _   _
  |   \_ _/ __| _ \ |    /_\ \ / / / __|/ __| _ \ __| __| \| | / |
  | |) | |\__ \  _/ |__ / _ \ V /  \__ \ (__|   / _|| _|| .` | | |
  |___/___|___/_| |____/_/ \_\_|   |___/\___|_|_\___|___|_|\_| |_|

CPU BIG Temp / Load
GPU BIG Temp / Load
Used System RAM Small 
*/

void DisplayStyle1 () {

  //-------------------------------------------Clearing Box ----------------------------------------------------

  //Clearing Boxes, eg: display.fillRect(<X>, ^Y^, W, H, Color);*/
  display.fillRect (0, 0, 128, 64, BLACK); // Clear entire screen 
  
  //--------------------------------------- Display Background ----------------------------------------------------

  /* OLED Background */
  display.setTextSize(2); //set background txt font size
  display.setCursor(1, 12);
  display.println("CPU");
  display.setCursor(1, 38);
  display.println("GPU");
  display.setTextSize(1); //set background txt font size
  display.setCursor(1, 56);
  display.println("SYSRAM");


  /*CPU/GPU/RAM  Clearing Boxes, eg: display.fillRect(<X>, ^Y^, W, H, Color);*/
  //display.fillRect(38, 11, 90, 16, BLACK); // fill CPU live stats section only
  //display.fillRect(38, 37, 90, 16, BLACK); // fill GPU live stats section only
  //display.fillRect(38, 54, 36, 10, BLACK); // fill RAM live stats section only
  /* Position Test*/
  //display.drawRect(38, 11, 90, 16, WHITE); // fill CPU live stats section only
  //display.drawRect(38, 37, 90, 16, WHITE); // fill GPU live stats section only
  //display.drawRect(38, 54, 36, 10, WHITE); // fill RAM live stats section only
  //display.drawRect(68, 54, 58, 10, WHITE); // Flash bottom right corner when updating

  //---------------------------------------CPU & GPU Hardware ID----------------------------------------------------

  /*CPU & GPU Hardware ID*/

  /*CPU Manual Position Test*/
  //display.setTextSize(0);
  //display.setCursor(-35, 1);// Negative spacing so, CPU ID doesn't cause a rollover, on the next line
  //String cpuName = "Intel Core i7-5820K"; // Name spacing test

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



  //----------------------------------------SYSTEM RAM USAGE---------------------------------------------------

  /*SYSTEM RAM String*/
  int ramStringStart = inputString.indexOf("R", gpuStringLimit);
  int ramStringLimit = inputString.indexOf("|", ramStringStart);
  String ramString = inputString.substring(ramStringStart + 1 , ramStringLimit);


  /*RAM USAGE*/
  display.setTextSize(1); //set background txt font size
  display.setCursor(42, 56);
  display.print(ramString); 
  


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
  display.println("D1");
  display.display();

  oledDraw = 1;

}
