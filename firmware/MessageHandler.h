#ifndef _MESSAGE_HANDER_H_
#define _MESSAGE_HANDER_H_
#include <SerialReceiver.h>
#include "DictPrinter.h"
#include "constants.h"
#include "SavedVariables.h"

class MessageHandler : public SerialReceiver {

 public:
  void processMsg();

 private:
  DictPrinter dprint;
  void msgSwitchYard();
  void handleGetDevInfo();
  void handleGetCmds();

  bool checkNumberOfArgs(int num);
  bool checkSerialNumberArg(int serial_number);
  void systemCmdRsp(bool flag);

  void handleGetRspCodes();
  void handleSetSerialNumber();

  bool checkMilliVoltArg(int milli_volt);
  bool checkWaveformArg(int waveform);

  void handleAnalogWriteA();
  void handleAnalogWriteB();
  void handleAnalogWriteC();
  void handleAnalogWriteD();
  void handleAnalogWriteAll();

  void handleStartWaveform();
  void handleStopWaveform();

  // Development
  void handleDebug();
};

extern MessageHandler messageHandler;
#endif
