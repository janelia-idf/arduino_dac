#include <SPI.h>
#include <Streaming.h>
#include <EEPROM.h>
#include <util/atomic.h>

#include "AD57X4R.h"
#include "SerialReceiver.h"
#include "DictPrinter.h"
#include "TimeTriggeredScheduler.h"

#include "constants.h"
#include "SystemState.h"
#include "MessageHandler.h"

void setup() {
  Serial.begin(constants::baudrate);
  systemState.initialize();
}

void loop() {
  messageHandler.processMsg();
}
