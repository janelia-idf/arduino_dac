#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "string.h"
#include "SystemState.h"

SystemState::SystemState() {
  setErrMsg("");
}

void SystemState::setErrMsg(char *msg) {
  strncpy(errMsg,msg,SYS_ERR_BUF_SZ);
}

void SystemState::initialize() {
  dac = AD57X4R(constants::dacCsPin);

  // Initialize SPI:
  SPI.setDataMode(SPI_MODE2);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();

  // Initialize DAC
  dac.init(AD57X4R::AD5754R, AD57X4R::UNIPOLAR_5V, AD57X4R::ALL);
  dac_max_value = dac.getMaxDacValue();

  // Initialize time triggered scheduler
  tts.init();
  updateTaskId = -1;
}

bool SystemState::analogWriteChannel(AD57X4R::channels channel, int milli_volt) {
  unsigned int value = map(milli_volt,constants::milliVoltMin,constants::milliVoltMax,0,dac_max_value);
  dac.analogWrite(channel,value);
  return true;
}

bool SystemState::analogWriteA(int milli_volt) {
  analogWriteChannel(AD57X4R::A,milli_volt);
  return true;
}

bool SystemState::analogWriteB(int milli_volt) {
  analogWriteChannel(AD57X4R::B,milli_volt);
  return true;
}

bool SystemState::analogWriteC(int milli_volt) {
  analogWriteChannel(AD57X4R::C,milli_volt);
  return true;
}

bool SystemState::analogWriteD(int milli_volt) {
  analogWriteChannel(AD57X4R::D,milli_volt);
  return true;
}

bool SystemState::analogWriteAll(int milli_volt) {
  analogWriteChannel(AD57X4R::ALL,milli_volt);
  return true;
}

bool SystemState::startWaveform(int waveform) {
  stopWaveform();
  int update_rate = 5;
  int count = -1;
  tts.setTime(0);
  updateTaskId = (int)tts.addTaskUsingDelay(100,inlineUpdate,waveform,update_rate,count,false);
  return true;
}

bool SystemState::stopWaveform() {
  if (updateTaskId >= 0) {
    tts.removeTask((uint8_t)updateTaskId);
    updateTaskId = -1;
  }
  return true;
}

bool SystemState::update(int waveform) {
  int period = 1000;
  int amplitude = 5000;
  int milli_volt = 0;
  int cycle_time = tts.ms()%period;
  if (waveform == 0) {
    float angle = (6.2832*cycle_time)/period;
    double value = sin(angle);
    milli_volt = value*amplitude/2 + amplitude/2;
  } else if (waveform == 1) {
    if (cycle_time <= period/2) {
      milli_volt = 2*(amplitude/period)*cycle_time;
    } else {
      milli_volt = amplitude - 2*(amplitude/period)*(cycle_time - period/2);
    }
  } else if (waveform == 2) {
    milli_volt = (amplitude/period)*cycle_time;
  } else if (waveform == 3) {
    if (cycle_time <= period/2) {
      milli_volt = amplitude;
    } else {
      milli_volt = 0;
    }
  }
  analogWriteA(milli_volt);
  return true;
}

SystemState systemState;
