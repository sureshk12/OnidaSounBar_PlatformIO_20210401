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
  versionStr = "NOTVALIDVERSION";
}

void Security::begin(Preferences devLoadPreferences)
{
  ShaLib shalib;
  // initialize

  devprojStr = "";
  devSsidStr = "";
  devPassStr = "";
  devSerialNumberStr = "";
  devActivationCodeStr = "";
  devAwsCodeStr = "";
  devMobCodeStr = "";
  devShaDigest = "";
  versionStr = "";
  int devStep = 0;
  int devMobAwsStep = 0; 
  String devRandomStr = "";
  String devMacId = WiFi.macAddress();

  //   Preferences devLoadPreferences;
  devLoadPreferences.begin("sureshkaval@100", false); //create Partion
  devprojStr = devLoadPreferences.getString("project");
  // devSsidStr = "";
  // devPassStr = "";
  devSerialNumberStr = devLoadPreferences.getString("serialNumber");
  devActivationCodeStr = devLoadPreferences.getString("activationCode");
  devShaDigest = devLoadPreferences.getString("securityCode");
  versionStr = devLoadPreferences.getString("version");

  // Serial.println("SHA Digest loaded from Memory = " + devShaDigest);

  shalib.getRanAwsMod(devShaDigest, devStep, devRandomStr, devMobAwsStep, devAwsCodeStr, devMobCodeStr);

  // Serial.println("\nSerial Number    from memory       = " + devSerialNumberStr);
  // Serial.println("Activation Code  from memory       = " + devActivationCodeStr);
  // Serial.println("AWS Code decoded from devShaDigest = " + devAwsCodeStr);
  // Serial.println("Mob Code decoded from devShaDigest = " + devMobCodeStr);
  // Serial.println("Random decoded from devShaDigest   = " + devRandomStr);
  // Serial.print("devStep decoded from devShaDigest    = ");
  // Serial.println(devStep);
  // Serial.print("devMobAwsStep decoded from devShaDigest    = ");
  // Serial.println(devMobAwsStep);
  // Serial.println("Mac ID from Device =               = " + devMacId);
  // Serial.println("Security Code from memory         = " + devShaDigest);

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

  // Get new MobAwsStep
  char newMobAwsStepChar[2];
  String newMobStrStepStr = ltoa(devMobAwsStep, newMobAwsStepChar, 10);

  //Encode
  int newPos = 3; //Step Position
  //Encode step
  newShaDigest[newPos] = newStepStr[0];

  //Encode mobAwsStep
  newShaDigest[2] = newMobStrStepStr[0];

  //Encode random
  for (int x = 0; x < 8; x++)
  {
    newPos = newPos + devStep;
    newShaDigest[newPos] = devRandomStr[x];
  }
  for (int x = 0; x < 32; x++)
  {
    newPos = newPos + devStep;
    newShaDigest[newPos] = devAwsCodeStr[x];
    //newPos = newPos + devStep;
    newShaDigest[newPos + devMobAwsStep] = devMobCodeStr[x];
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
  // Serial.println("SERIAL NUMBER Calculated  = " + devSerialNumberStr);
  // Serial.println("ACTIVATION CODE Calculated= " + devActivationCodeStr);
  // Serial.println("AWS CODE Calculated       = " + devAwsCodeStr);
  // Serial.println("MOB CODE calculated        = " + devMobCodeStr);
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

String Security::getVersion()
{
  return versionStr;
}
