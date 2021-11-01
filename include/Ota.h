/*
  * Ota.h - Library for OTA function.
  * Created by Suresh Kumar, October 05, 2019.
*/
#ifndef Ota_h
#define Ota_h

#include "Arduino.h"

class Ota
{
  public:
    Ota();
    void checkDoOta(String serialNumber, String activation);

  private:
    void getWebDate();
    void checkWebSite();
    int getLatestVersion();
    void doOta();
    String getShaCode(char *inputString);
};

#endif