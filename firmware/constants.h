#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

namespace constants {
  // Communications parameters
  extern const int baudrate;

  // Device parameters
  extern const int modelNumber;
  extern const int serialNumberMin;
  extern const int serialNumberMax;
  extern const int firmwareNumber;

  // Pin assignment
  extern const int dacCsPin;

  // Dac parameters
  extern const int milliVoltMin;
  extern const int milliVoltMax;

  // Waveform parameters
  extern const int waveformMin;
  extern const int waveformMax;

}
#endif
