/*
  Ota.cpp - Library for storing data in flash code.
  Created by Suresh Kumar, October 05, 2019.
*/

#include "Arduino.h" // Arduino Library
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include "mbedtls/md.h"  //sha1.h"//md.h"
#include <Preferences.h> // Preferences Library

#include "Ota.h" // H file for Ota.h
#include "Nvm.h"
#include "DeviceConstants.h"
#include <string>
#include "ShaLib.h"

/*
 * Constants 
*/
String webUrlStr = "";
HTTPClient httpClient;
ShaLib shalib1;

/*
 * Intilization of Class
 * Intilizes EEPROM with max Size
 * Set the Constant maxMem with max size
*/
Ota::Ota()
{
    //Default Constructor
}

/*

*/
void Ota::checkDoOta(String serialNumber, String activation)
{
    //Get Version Number
    String newShaMacRanCode = shalib1.getDigest(serialNumber, activation, WiFi.macAddress(), "SureshOtaKaval", "48");
    Serial.print("Code : ");
    Serial.print(newShaMacRanCode);
    while(true) {

    }
    httpClient.begin(webUrlStr + "index.jsp");
    int httpCode = httpClient.GET();
    if (httpCode > 0)
    {
        Serial.print("Received HTTP Code : ");
        Serial.println(httpCode);
        if (httpCode == HTTP_CODE_OK) {

        }
    }
}