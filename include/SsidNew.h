/*
  * KeySense.h - Library to check if Key is pressed for > 10 sec.
  * if Key Press is detected return boolean TRUE.
  * If 
*/
#ifndef SsidNew_h
#define SsidNew_h

#include "Arduino.h"

class SsidNew
{
  public:
    SsidNew();
    void setUpNewSsid();
    void wifiConnect();
  private:
};

#endif