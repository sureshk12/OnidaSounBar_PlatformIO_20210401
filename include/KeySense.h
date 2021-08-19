/*
  * KeySense.h - Library to check if Key is pressed for > 10 sec.
  * if Key Press is detected return boolean TRUE.
  * If 
*/
#ifndef KeySense_h
#define KeySense_h

#include "Arduino.h"

class KeySense
{
  public:
    KeySense();
    boolean switchDetect();
  private:
};

#endif