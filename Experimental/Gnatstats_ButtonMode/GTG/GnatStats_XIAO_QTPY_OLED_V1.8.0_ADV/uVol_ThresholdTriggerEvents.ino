/*
     __      __   _                         _____                        _     
     \ \    / /  | |                       / ____|                      ( )    
  _   \ \  / /__ | |_   _ _ __ ___   ___  | |  __  __ _ _   _  __ _  ___|/ ___ 
 | | | \ \/ / _ \| | | | | '_ ` _ \ / _ \ | | |_ |/ _` | | | |/ _` |/ _ \ / __|
 | |_| |\  / (_) | | |_| | | | | | |  __/ | |__| | (_| | |_| | (_| |  __/ \__ \
  \__,_| \/ \___/|_|\__,_|_| |_| |_|\___|  \_____|\__,_|\__,_|\__, |\___| |___/
                                                               __/ |           
                                                              |___/          
  Trigger functions when CPU or GPU thresholds are met

  uVolume MK2 Rev 1.2 Example CPU Enclosure Top / GPU Enclosure Bottom
*/



// ------------------- CPU load / Temp Event  --------------------

void uVol_TriggerCPU_load(int cpuUsage ) {

  /* Pre-define Hex NeoPixel colours,  eg. pixels.setPixelColor(0, neo_BLUE); https://htmlcolorcodes.com/color-names/ */
#define neo_RED        0xFF0000
#define neo_GREEN      0x008000
#define neo_BLUE       0x0000FF
///#define neo_ORANGE     0xFFA500
///#define neo_DARKORANGE 0xFF8C00
///#define neo_YELLOW     0xFFFF00
///#define neo_WHITE      0xFFFFFF


  float CPUloadfactor = cpuUsage ;

  if (CPUloadfactor >= 0 ) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(2, neo_BLUE);

  }
  if (CPUloadfactor >= 25 ) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(2, neo_BLUE);
  }

  if (CPUloadfactor >= (50) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(2, neo_RED);
  }

  if (CPUloadfactor >= (90) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(2, neo_RED);
  }

  pixels.show();

}


void uVol_TriggerCPU_temp(int cpuDegree ) {

  float CPUtempfactor = cpuDegree ;

  if (CPUtempfactor >=  50) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(2, neo_BLUE);
  }

  if (CPUtempfactor >= 60 ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(2, neo_RED);

  }

  if (CPUtempfactor >= (70) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(2, neo_RED);

  }

  if (CPUtempfactor >= (80) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(2, neo_RED);

  }

  pixels.show();

}

// -------------------  GPU Load / Temp Event  --------------------


void uVol_TriggerGPU_load(int gpuUsage ) {

  float GPUloadfactor = gpuUsage ;

  if (GPUloadfactor >= 0 ) {
    pixels.setPixelColor(1, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);  
  }

  if (GPUloadfactor >= 25 ) {
    pixels.setPixelColor(1, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);
  }

  if (GPUloadfactor >= (50) ) {
    pixels.setPixelColor(1, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);
  }
  
if (GPUloadfactor >= (70) ) {
    pixels.setPixelColor(1, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }
  if (GPUloadfactor >= (90) ) {
    pixels.setPixelColor(1, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  pixels.show();

}


void uVol_TriggerGPU_temp(int gpuDegree ) {

  float GPUtempfactor = gpuDegree ;

  if (GPUtempfactor >=  50) {

    pixels.setPixelColor(1, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);

  }

  if (GPUtempfactor >= 60 ) {

    pixels.setPixelColor(1, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);

  }

  if (GPUtempfactor >= (70) ) {

    pixels.setPixelColor(1, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  if (GPUtempfactor >= (80) ) {

    pixels.setPixelColor(1, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  pixels.show();

}
