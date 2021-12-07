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
  String getDevShaDigest();
  String getVersion();

private:
  String devprojStr;
  String devSsidStr;
  String devPassStr;
  String devSerialNumberStr;
  String devActivationCodeStr;
  String devAwsCodeStr;
  String devMobCodeStr;
  String devShaDigest;
  String versionStr;
};

#endif