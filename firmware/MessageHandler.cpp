#include <util/atomic.h>
#include "MessageHandler.h"
#include "Streaming.h"
#include "SystemState.h"

enum {
  cmdGetDevInfo,                    // Done
  cmdGetCmds,                       // Done
  cmdGetRspCodes,                   // Done
  cmdSetSerialNumber,               //

  cmdAnalogWriteA,                 //
  cmdAnalogWriteB,                 //
  cmdAnalogWriteC,                 //
  cmdAnalogWriteD,                 //
  cmdAnalogWriteAll,                 //

  cmdStartWaveform,                 //
  cmdStopWaveform,                 //

  // DEVELOPMENT
  cmdDebug,
};


const int rspSuccess = 1;
const int rspError = 0;

void MessageHandler::processMsg() {
  while (Serial.available() > 0) {
    process(Serial.read());
    if (messageReady()) {
      msgSwitchYard();
      reset();
    }
  }
  return;
}

void MessageHandler::msgSwitchYard() {
  int cmd = readInt(0);
  dprint.start();
  dprint.addIntItem("cmd_id", cmd);

  switch (cmd) {

  case cmdGetDevInfo:
    handleGetDevInfo();
    break;

  case cmdGetCmds:
    handleGetCmds();
    break;

  case cmdGetRspCodes:
    handleGetRspCodes();
    break;

  case cmdSetSerialNumber:
    handleSetSerialNumber();
    break;

  case cmdAnalogWriteA:
    handleAnalogWriteA();
    break;

  case cmdAnalogWriteB:
    handleAnalogWriteB();
    break;

  case cmdAnalogWriteC:
    handleAnalogWriteC();
    break;

  case cmdAnalogWriteD:
    handleAnalogWriteD();
    break;

  case cmdAnalogWriteAll:
    handleAnalogWriteAll();
    break;

  case cmdStartWaveform:
    handleStartWaveform();
    break;

  case cmdStopWaveform:
    handleStopWaveform();
    break;

  // DEVELOPMENT
  case cmdDebug:
    handleDebug();
    break;

  default:
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "unknown command");
    break;
  }
  dprint.stop();
}

void MessageHandler::handleGetCmds() {
  dprint.addIntItem("status", rspSuccess);
  dprint.addIntItem("getDevInfo", cmdGetDevInfo);
  dprint.addIntItem("getCmds", cmdGetCmds);
  dprint.addIntItem("getRspCodes", cmdGetRspCodes);
  dprint.addIntItem("setArduinoSerialNumber", cmdSetSerialNumber);

  dprint.addIntItem("analogWriteA", cmdAnalogWriteA);
  dprint.addIntItem("analogWriteB", cmdAnalogWriteB);
  dprint.addIntItem("analogWriteC", cmdAnalogWriteC);
  dprint.addIntItem("analogWriteD", cmdAnalogWriteD);
  dprint.addIntItem("analogWriteAll", cmdAnalogWriteAll);

  dprint.addIntItem("startWaveform", cmdStartWaveform);
  dprint.addIntItem("stopWaveform", cmdStopWaveform);

  // DEVELOPMENT
  dprint.addIntItem("cmdDebug", cmdDebug);
}

void MessageHandler::handleGetDevInfo() {
  dprint.addIntItem("status", rspSuccess);
  dprint.addIntItem("model_number",  constants::modelNumber);
  dprint.addIntItem("serial_number", savedVariables.getSerialNumber());
  dprint.addIntItem("firmware_number", constants::firmwareNumber);
}

bool MessageHandler::checkNumberOfArgs(int num) {
  bool flag = true;
  if (numberOfItems() != num) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "incorrect number of arguments");
    flag = false;
  }
  return flag;
}

bool MessageHandler::checkSerialNumberArg(int serial_number) {
  bool flag = true;
  if ((serial_number<constants::serialNumberMin) || (constants::serialNumberMax<serial_number)) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "serial number argument out of range");
    flag = false;
  }
  return flag;
}

void MessageHandler::systemCmdRsp(bool flag) {
  if (flag) {
    dprint.addIntItem("status", rspSuccess);
  }
  else {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", systemState.errMsg);
  }
}

void MessageHandler::handleGetRspCodes() {
  dprint.addIntItem("status", rspSuccess);
  dprint.addIntItem("rsp_success",rspSuccess);
  dprint.addIntItem("rsp_error", rspError);
}

void MessageHandler::handleSetSerialNumber() {
  if (!checkNumberOfArgs(2)) {return;}
  int serialNumber = readInt(1);
  if (checkSerialNumberArg(serialNumber)) {
    systemCmdRsp(savedVariables.setSerialNumber(serialNumber));
  }
}

bool MessageHandler::checkMilliVoltArg(int milli_volt) {
  bool flag = true;
  if ((milli_volt<constants::milliVoltMin) || (constants::milliVoltMax<milli_volt)) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "milli_volt argument out of range");
    flag = false;
  }
  return flag;
}

bool MessageHandler::checkWaveformArg(int waveform) {
  bool flag = true;
  if ((waveform<constants::waveformMin) || (constants::waveformMax<waveform)) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "waveform argument out of range");
    flag = false;
  }
  return flag;
}

void MessageHandler::handleAnalogWriteA() {
  if (!checkNumberOfArgs(2)) {return;}
  int milli_volt = readInt(1);
  if (checkMilliVoltArg(milli_volt)) {
    systemState.stopWaveform();
    systemCmdRsp(systemState.analogWriteA(milli_volt));
  }
}

void MessageHandler::handleAnalogWriteB() {
  if (!checkNumberOfArgs(2)) {return;}
  int milli_volt = readInt(1);
  if (checkMilliVoltArg(milli_volt)) {
    systemState.stopWaveform();
    systemCmdRsp(systemState.analogWriteB(milli_volt));
  }
}

void MessageHandler::handleAnalogWriteC() {
  if (!checkNumberOfArgs(2)) {return;}
  int milli_volt = readInt(1);
  if (checkMilliVoltArg(milli_volt)) {
    systemState.stopWaveform();
    systemCmdRsp(systemState.analogWriteC(milli_volt));
  }
}

void MessageHandler::handleAnalogWriteD() {
  if (!checkNumberOfArgs(2)) {return;}
  int milli_volt = readInt(1);
  if (checkMilliVoltArg(milli_volt)) {
    systemState.stopWaveform();
    systemCmdRsp(systemState.analogWriteD(milli_volt));
  }
}

void MessageHandler::handleAnalogWriteAll() {
  if (!checkNumberOfArgs(2)) {return;}
  int milli_volt = readInt(1);
  if (checkMilliVoltArg(milli_volt)) {
    systemState.stopWaveform();
    systemCmdRsp(systemState.analogWriteAll(milli_volt));
  }
}

void MessageHandler::handleStartWaveform() {
  if (!checkNumberOfArgs(2)) {return;}
  int waveform = readInt(1);
  if (checkWaveformArg(waveform)) {
    systemCmdRsp(systemState.startWaveform(waveform));
  }
}

void MessageHandler::handleStopWaveform() {
  systemCmdRsp(systemState.stopWaveform());
}

// -------------------------------------------------


void MessageHandler::handleDebug() {
  char name[20];
  dprint.addIntItem("status", rspSuccess);
}


MessageHandler messageHandler;
