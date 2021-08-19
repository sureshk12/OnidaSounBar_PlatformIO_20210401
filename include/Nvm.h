/*
  * Nvm.h - Library for storing data in flash code.
  * Created by Suresh Kumar, July 11, 2019.
*/
#ifndef Nvm_h
#define Nvm_h

#include "Arduino.h"

class Nvm
{
  public:
    Nvm();

    boolean write_ssid(const char* ssidchar, const char* passchar);
    boolean read_ssid(char* ssidchar, char* passchar);
    boolean write_string(const char* addr, const char* str);
    boolean read_string(const char* addr, char* buf);
    boolean isSsidValid();
    int read_int(char* addr);
    void write_int(char* addr, int val);
    void write_String1(char* addr, String val);
    String read_String1(char* addr);
    
  private:

};

#endif