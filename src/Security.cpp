/*
  * Security.cpp - Library for security.
  * Created by Suresh Kumar, March 29, 2021.
*/

#include "Arduino.h"     // Arduino Library
#include <Preferences.h> // Preferences Library
#include <WiFi.h>
#include "mbedtls/md.h"

#include "Security.h" // H file for Nvm
#include "ShaLib.h"

Security::Security(int x)
{
  // Constructor
  Serial.println("Iam in Security Constructor");
  
  devSerialNumberStr = "NOTVALIDSN";
  devActivationCodeStr = "NOTVALIDAC";
  devAwsCodeStr = "NOTVALIDAWSCODE";
  devMobCodeStr = "NOTVALIDMOBCODE";
  devShaDigest = "NOTVALIDMOBCODE";
}

void Security::begin(Preferences devLoadPreferences)
{
  ShaLib shalib;
  // initialize
  devSerialNumberStr = "";
  devActivationCodeStr = "";
  devAwsCodeStr = "";
  devMobCodeStr = "";
  devShaDigest = "";
  int devStep = 0;
  String devRandomStr = "";
  String devMacId = WiFi.macAddress();
  ;

  //   Preferences devLoadPreferences;
  devLoadPreferences.begin("sureshkaval@100", false); //create Partion

  devSerialNumberStr = devLoadPreferences.getString("serialNumber");
  devActivationCodeStr = devLoadPreferences.getString("activationCode");
  devShaDigest = devLoadPreferences.getString("securityCode");

  // Serial.println("SHA Digest loaded from Memory = " + devShaDigest);

  shalib.getRanAwsMod(devShaDigest, devStep, devRandomStr, devAwsCodeStr, devMobCodeStr);

  // Serial.println("Serial Number    from memory       = " + devSerialNumberStr);
  Serial.println("Activation Code  from memory       = " + devActivationCodeStr);
  Serial.println("AWS Code decoded from devShaDigest = " + devAwsCodeStr);
  Serial.println("Mob Code decoded from devShaDigest = " + devMobCodeStr);
  Serial.println("Random decoded from devShaDigest   = " + devRandomStr);
  Serial.print("devStep decoded from devShaDigest    = ");
  Serial.println(devStep);
  Serial.println("Mac ID from Device =               = " + devMacId);

  //Recreate the CODED SHA Digest

  String newShaMacRanCode = shalib.getDigest(devSerialNumberStr, devActivationCodeStr, devMacId, devRandomStr, "34");
  String newShaAwsRanCode = shalib.getDigest(devSerialNumberStr, devActivationCodeStr, devAwsCodeStr, devRandomStr, "34");
  String newShaMobRanCode = shalib.getDigest(devSerialNumberStr, devActivationCodeStr, devMobCodeStr, devRandomStr, "34");
  String newShaAwsMaccode = shalib.getDigest(devSerialNumberStr, devActivationCodeStr, devAwsCodeStr, devMacId, "34");
  String newShaMobMacCode = shalib.getDigest(devSerialNumberStr, devActivationCodeStr, devMobCodeStr, devMacId, "34");
  String newShaDigest = newShaMacRanCode + newShaAwsRanCode + newShaMobRanCode + newShaAwsMaccode + newShaMobMacCode;

  // Serial.println("RECREATEDVSHA BEFORE_CODEING = " + newShaDigest);
  //Get random step
  char newStepChar[2];
  String newStepStr = ltoa(devStep, newStepChar, 10);
  // Serial.println("New Step = " + newStepStr);
  //Encode
  int newPos = 3; //Step Position
  //Encode step
  newShaDigest[newPos] = newStepStr[0];
  //Encode random
  for (int x = 0; x < 8; x++)
  {
    newPos = newPos + devStep;
    newShaDigest[newPos] = devRandomStr[x];
  }
  for (int x = 0; x < 12; x++)
  {
    newPos = newPos + devStep;
    newShaDigest[newPos] = devAwsCodeStr[x];
    newPos = newPos + devStep;
    newShaDigest[newPos] = devMobCodeStr[x];
  }
  // Serial.println("AFTER _SAVE_AFTER _CODEING = " + newShaDigest);

  if (devShaDigest.length() == newShaDigest.length())
  {
    if (devShaDigest.equals(newShaDigest))
    {
    }
    else
    {
      devAwsCodeStr = "NOTVALIDAWSCODE";
      devMobCodeStr = "NOTVALIDMOBCODE";
    }
  }
  else
  {
    devAwsCodeStr = "NOTVALIDAWSCODE";
    devMobCodeStr = "NOTVALIDMOBCODE";
  }
  // Serial.println();
  // Serial.println("SERIAL NUMBER   = " + devSerialNumberStr);
  // Serial.println("ACTIVATION CODE = " + devActivationCodeStr);
  // Serial.println("AWS CODE        = " + devAwsCodeStr);
  // Serial.println("MOB CODe        = " + devMobCodeStr);
}

String Security::getSerialNumber()
{
  return devSerialNumberStr;
}

String Security::getActivationCode()
{
  return devActivationCodeStr;
}

String Security::getAwsCode()
{
  return devAwsCodeStr;
}

String Security::getMobCode()
{
  return devMobCodeStr;
}

String Security::getDevShaDigest()
{
  return devShaDigest;
}
