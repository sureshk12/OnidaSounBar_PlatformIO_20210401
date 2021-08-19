/*
  * HwConstants.h - Library to keep all constants related to Hardware.
  * 
*/
#ifndef DeviceConstants_h
#define DeviceConstants_h

#include "Arduino.h"

class DeviceConstants
{
public:
  const int switchPinVal = 0; //Switch Connected to Port 0
  const int ledPinVal = 2;    //LED Connected to Port 2

  const char *devSerNum = "11O9190001";

  //const String deviceSerialNumber = "11O9190001";//11O9190001//11O9190002//11O9190003//11O9190004

  String deviceSerialNumber;// = "11O9190001"; //11O9190001//11O9190002//11O9190003//11O9190004
  String deviceActivationCode;// = "ED25843042";      //ED25843042//3DF559A6C0//69CCD423F5//CE594E4782
  String deviceAwsCode;// = "DID-5DA5E7C14766";       //DID-5DA5E7C14766//DID-5177E02F5A24//DID-CC2C9D01FBAC//DID-606B61BCB67D
  String deviceMobileCode;// = "DKY-8757D8A728B1";    //DKY-8757D8A728B1//DKY-1DD0738F3A02//DKY-102CFECF6264//DKY-1FF9711E3C9F

  const char *verDevOri = "201910050"; //Really nou used will let us know original SW
  // {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  // { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
  //date value calculation = YEAR x 365 + Month valur (as sgown above) + Date
  const char *datDevOri = "7213";
  const char *webUrl = "http://www.ashank.com/OnidaTvData/"; //"http://www.ashank.com/OnidaTvDataV0/";"http://192.168.2.9/OnidaTvDataV0/";

  DeviceConstants();
  void putDeviceSerialNumber(String devSerNum);
  void putDeviceActivationCode(String devActCode);
  void putDeviceAwsCode(String devAwsCode);
  void putDeviceMobCode(String devMobCode);

  String getDeviceSerialNumber();
  String getDeviceActivationCode();
  String getDeviceAwsCode();
  String getDeviceMobCode();

private:
};

#endif