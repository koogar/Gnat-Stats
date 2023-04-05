void DisplayStyle3 () {

  /* Serial stuff*/
  serialEvent();
  activityChecker();



  /* OLED DRAW STATS */
  if (stringComplete) {

    if (bootMode) {

      //splashScreen2();
      display.clearDisplay();
      display.display();

      bootMode = false;
    }

    lastActiveConn = millis();

    /* OLED Background */
    display.setTextSize(2); //set background txt font size
    display.setCursor(1, 12);
    display.println("CPU");
    display.setCursor(1, 38);
    display.println("GPU");
    display.setTextSize(1); //set background txt font size
    display.setCursor(1, 56);
    display.println("SYSRAM");
    display.setCursor(76, 56);
    display.println("Display3");

    display.display();


    /*CPU/GPU/RAM  Clearing Boxes, eg: display.fillRect(<X>, ^Y^, W, H, Color);*/
    display.fillRect(38, 11, 90, 16, BLACK); // fill CPU live stats section only
    display.fillRect(38, 37, 90, 16, BLACK); // fill GPU live stats section only
    display.fillRect(38, 54, 36 , 10, BLACK); // fill RAM live stats section only

    /* Position Test*/
    //display.drawRect(38, 11, 90, 16, WHITE); // fill CPU live stats section only
    //display.drawRect(38, 37, 90, 16, WHITE); // fill GPU live stats section only
    //display.drawRect(38, 54, 36 , 10, WHITE); // fill RAM live stats section only
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
      //display.setCursor(1, 1);
      display.setCursor(-35, 1);
      int cpuNameStart = inputString.indexOf("CPU:");
      if (inputString.indexOf("GPU") > -1)
      {
        cpuName = inputString.substring(cpuNameStart + 4, inputString.indexOf("GPU:"));
      }
      else
        cpuName = inputString.substring(cpuNameStart + 4);
      display.println(cpuName);

    }
    if (inputString.indexOf("GPU") > -1)
    {
      display.setTextSize(0);

      //display.setCursor(0, 28);
      display.setCursor(-41, 28); // Negative spacing so, Nvidia doesn't cause a rollover, on the next line

      int gpuNameStart = inputString.indexOf("GPU:");
      String gpuName = inputString.substring(gpuNameStart + 4);
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
    display.print((char)247);
    display.print("C");

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
    display.print((char)247); //Degrees Symbol
    display.print("C");       // Centigrade Symbol

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
    display.println(ramString);
    display.display();


    inputString = "";
    stringComplete = false;
    display.display();

    oledDraw = 1;


  }
}
