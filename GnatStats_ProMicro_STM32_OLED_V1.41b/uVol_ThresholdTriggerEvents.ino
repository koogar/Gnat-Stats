/*
  ------------------------------------------------------------------------------------------
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
  ------------------------------------------------------------------------------------------
*/



// ------------------- CPU load / Temp Event  --------------------

void uVol_TriggerCPU_load(int cpuUsage ) {

  float CPUloadfactor = cpuUsage ;

  if (CPUloadfactor >= 0 ) {
    pixels.setPixelColor(0, BLUE);
    pixels.setPixelColor(2, BLUE);

  }
  if (CPUloadfactor >= 25 ) {
    pixels.setPixelColor(0, BLUE);
    pixels.setPixelColor(2, BLUE);
  }

  if (CPUloadfactor >= (50) ) {
    pixels.setPixelColor(0, RED);
    pixels.setPixelColor(2, RED);
  }

  if (CPUloadfactor >= (90) ) {
    pixels.setPixelColor(0, RED);
    pixels.setPixelColor(2, RED);
  }

  pixels.show();

}


void uVol_TriggerCPU_temp(int cpuDegree ) {

  float CPUtempfactor = cpuDegree ;

  if (CPUtempfactor >=  50) {
    pixels.setPixelColor(0, BLUE);
    pixels.setPixelColor(2, BLUE);
  }

  if (CPUtempfactor >= 60 ) {
    pixels.setPixelColor(0, RED);
    pixels.setPixelColor(2, RED);

  }

  if (CPUtempfactor >= (70) ) {
    pixels.setPixelColor(0, RED);
    pixels.setPixelColor(2, RED);

  }

  if (CPUtempfactor >= (80) ) {
    pixels.setPixelColor(0, RED);
    pixels.setPixelColor(2, RED);

  }

  pixels.show();

}

// -------------------  GPU Load / Temp Event  --------------------


void uVol_TriggerGPU_load(int gpuUsage ) {

  float GPUloadfactor = gpuUsage ;

  if (GPUloadfactor >= 0 ) {
    pixels.setPixelColor(1, BLUE);
    pixels.setPixelColor(3, BLUE);
  }

  if (GPUloadfactor >= 25 ) {
    pixels.setPixelColor(1, BLUE);
    pixels.setPixelColor(3, BLUE);
  }

  if (GPUloadfactor >= (50) ) {
    pixels.setPixelColor(1, BLUE);
    pixels.setPixelColor(3, BLUE);
  }

  if (GPUloadfactor >= (70) ) {
    pixels.setPixelColor(1, RED);
    pixels.setPixelColor(3, RED);
  }
  if (GPUloadfactor >= (90) ) {
    pixels.setPixelColor(1, RED);
    pixels.setPixelColor(3, RED);
  }

  pixels.show();

}


void uVol_TriggerGPU_temp(int gpuDegree ) {

  float GPUtempfactor = gpuDegree ;

  if (GPUtempfactor >=  50) {

    pixels.setPixelColor(1, BLUE);
    pixels.setPixelColor(3, BLUE);

  }

  if (GPUtempfactor >= 60 ) {

    pixels.setPixelColor(1, BLUE);
    pixels.setPixelColor(3, BLUE);

  }

  if (GPUtempfactor >= (70) ) {

    pixels.setPixelColor(1, RED);
    pixels.setPixelColor(3, RED);
  }

  if (GPUtempfactor >= (80) ) {

    pixels.setPixelColor(1, RED);
    pixels.setPixelColor(3, RED);
  }

  pixels.show();

}
