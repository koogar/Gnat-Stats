/*
  ------------------------------------------------------------------------------------------
    _____          _                    _______   _
   / ____|        | |                  |__   __| (_)
  | |    _   _ ___| |_ ___  _ __ ___      | |_ __ _  __ _  __ _  ___ _ __ ___
  | |   | | | / __| __/ _ \| '_ ` _ \     | | '__| |/ _` |/ _` |/ _ \ '__/ __|
  | |___| |_| \__ \ || (_) | | | | | |    | | |  | | (_| | (_| |  __/ |  \__ \
   \_____\__,_|___/\__\___/|_| |_| |_|    |_|_|  |_|\__, |\__, |\___|_|  |___/
                                                    __/ | __/ |
                                                   |___/ |___/

  Custom Trigger functions, when CPU or GPU threshold are met
  ------------------------------------------------------------------------------------------
*/

// ------------------- CPU load Event  --------------------

void CustomTriggerCPU_load(int cpuUsage ) {

  float CPUloadfactor = cpuUsage ;

  if (CPUloadfactor >= 0 ) {
    //Do Something!!!

  }
  if (CPUloadfactor >= 25 ) {
    //Do Something!!!
  }

  if (CPUloadfactor >= (50) ) {
    //Do Something!!!
  }

  if (CPUloadfactor >= (90) ) {
    //Do Something!!!
  }
}


// ------------------- CPU Temp Event  --------------------

void CustomTriggerCPU_temp(int cpuDegree ) {

  float CPUtempfactor = cpuDegree ;

  if (CPUtempfactor >=  50) {
    //Do Something!!!
  }

  if (CPUtempfactor >= 60 ) {
    //Do Something!!!

  }

  if (CPUtempfactor >= (70) ) {
    //Do Something!!!

  }

  if (CPUtempfactor >= (80) ) {
    //Do Something!!!

  }
}

// -------------------  GPU Load Event  --------------------


void CustomTriggerGPU_load(int gpuUsage ) {

  float GPUloadfactor = gpuUsage ;

  if (GPUloadfactor >= 0 ) {
    //Do Something!!!
  }

  if (GPUloadfactor >= 25 ) {
    //Do Something!!!
  }

  if (GPUloadfactor >= (50) ) {
    //Do Something!!!
  }

  if (GPUloadfactor >= (70) ) {
    //Do Something!!!
  }
  if (GPUloadfactor >= (90) ) {
    //Do Something!!!
  }
}

// -------------------  GPU Temp Event  --------------------

void CustomTriggerGPU_temp(int gpuDegree ) {

  float GPUtempfactor = gpuDegree ;

  if (GPUtempfactor >=  50) {

    //Do Something!!!

  }

  if (GPUtempfactor >= 60 ) {

    //Do Something!!!

  }

  if (GPUtempfactor >= (70) ) {

    //Do Something!!!
  }

  if (GPUtempfactor >= (80) ) {

    //Do Something!!!
  }
}
