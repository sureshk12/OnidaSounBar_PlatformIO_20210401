/*
  * ShaLib.h - Library for generatiing SHA256 digest.
  * Created by Suresh Kumar, March 30, 2021.
*/
#ifndef DoSwWork_h
#define DoSwWork_h

#include "Arduino.h"

class DoSwWork
{
private:
  
public:
  static int switchStatus;

  DoSwWork();
  void begin();
  int on_Off(String data);
};

#endif