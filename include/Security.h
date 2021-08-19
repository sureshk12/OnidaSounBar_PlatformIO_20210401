/*
  * Security.h - Library for security.
  * Created by Suresh Kumar, March 29, 2021.
*/
#ifndef Security_h
#define Security_h

#include "Arduino.h"

class Security
{
  public:
    Security(int x);
    void begin(Preferences preferences);

    String getSerialNumber();
    String getActivationCode();
    String getAwsCode();
    String getMobCode();
    
  private:
    String devSerialNumberStr;
    String devActivationCodeStr;
    String devAwsCodeStr;
    String devMobCodeStr;

};

#endif