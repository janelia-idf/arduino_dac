#ifndef _SYSTEM_STATE_H_
#define _SYSTEM_STATE_H_
#include <SPI.h>
#include "constants.h"
#include "TimeTriggeredScheduler.h"
#include "AD57X4R.h"


enum {SYS_ERR_BUF_SZ=50};

class SystemState {

 public:
  SystemState();

  void setErrMsg(char *);
  char errMsg[SYS_ERR_BUF_SZ];

  void initialize();

  bool analogWriteChannel(AD57X4R::channels channel, int milli_volt);
  bool analogWriteA(int milli_volt);
  bool analogWriteB(int milli_volt);
  bool analogWriteC(int milli_volt);
  bool analogWriteD(int milli_volt);
  bool analogWriteAll(int milli_volt);

  bool startWaveform(int waveform);
  bool stopWaveform();
  bool update(int waveform);

 private:
  AD57X4R dac;
  unsigned int dac_max_value;
  int updateTaskId;

};

extern SystemState systemState;

inline void inlineUpdate(int waveform) {systemState.update(waveform);}

#endif
