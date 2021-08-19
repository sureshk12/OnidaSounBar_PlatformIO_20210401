/*
  * DeviceConstants function.cpp - Library for security.
  * Created by Suresh Kumar, March 29, 2021.
*/

#include "Arduino.h"         // Arduino Library
#include "Deviceconstants.h" // H File for device constsnts

DeviceConstants::DeviceConstants()
{

}

void DeviceConstants::putDeviceSerialNumber(String devSerNum) {
    deviceSerialNumber = devSerNum;
    // Serial.println("Storing Serial number = " + deviceSerialNumber);
    // String temp = deviceSerialNumber;
    // Serial.println("Reading after storing = " + temp);
}

void DeviceConstants::putDeviceActivationCode(String devActCode) {
    deviceActivationCode = devActCode;
}

void DeviceConstants::putDeviceAwsCode(String devAwsCode) {
    deviceAwsCode = devAwsCode;
}

void DeviceConstants::putDeviceMobCode(String devMobCode) {
    deviceMobileCode = devMobCode;
}

String DeviceConstants::getDeviceSerialNumber() {
    Serial.print("returning Serial number = "); Serial.println(deviceSerialNumber);
    return deviceSerialNumber;
}

String DeviceConstants::getDeviceActivationCode() {
    return deviceActivationCode;
}

String DeviceConstants::getDeviceAwsCode() {
    return deviceAwsCode;
}

String DeviceConstants::getDeviceMobCode() {
    return deviceMobileCode;
}