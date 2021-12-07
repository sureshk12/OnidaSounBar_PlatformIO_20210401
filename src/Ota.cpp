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
String webUrlStr = "http://192.168.2.5:8080/Esp32Initialize/";
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

void Ota::doOta(String serialNumber, String activation) {
    //Compose macid
    Serial.println("Starting OTA Process...");
    String espMacId = WiFi.macAddress();
    String macId = espMacId.substring(0, 2) + espMacId.substring(3, 5) + espMacId.substring(6, 8) + espMacId.substring(9, 11) + espMacId.substring(12, 14) + espMacId.substring(15, 17);
    macId.toLowerCase();
    Serial.print("macId : ");
    Serial.println(macId);
    //Create 12 digit random Number
    char buf[16];
    String s1 = ltoa(random(1, 999999), buf, 10);
    String s2 = ltoa(random(1, 999999), buf, 10);
    String randStr = s1 + s2;
    Serial.print("randStr : ");
    Serial.println(randStr);
    //Create Security String
    String newShaMacRanStr = shalib1.getDigest(serialNumber, activation, macId, randStr, "48");
    //Generate Random number
    int step = random(2, 6);
    Serial.print("ranInt : ");
    Serial.println(step);
    Serial.print("Code Before: ");
    Serial.println(newShaMacRanStr);
    //Code macId to Code
    newShaMacRanStr[1] = (char)(step + 48);
    for (int x = 1; x < 13; x++)
    {
        newShaMacRanStr[2 + (x * step)] = macId[x - 1];
        newShaMacRanStr[2 + (x * step) + 1] = randStr[x - 1];
    }

    // Serial.print("Code After : ");
    // Serial.print(newShaMacRanStr);
    // httpClient.begin(webUrlStr + "initializeEspAudio?serialNumber=" + serialNumber + "&activationCode=" + activation + "&securityCode=" + newShaMacRanStr);
    // int httpCode = httpClient.GET();
    // Serial.print("HTTP Response code: ");
    // Serial.println(httpCode);
    // if (httpCode > 0)
    // {
    //     if (httpCode == HTTP_CODE_OK)
    //     {
    //         String payload = httpClient.getString();
    //         Serial.println(payload);
    //     }
    // }

    WiFiClient client;
    //t_httpUpdate_return ret = httpUpdate.update(client, webUrlStr + "initializeEspAudio?serialNumber=" + serialNumber + "&activationCode=" + activation + "&securityCode=" + newShaMacRanStr);
    t_httpUpdate_return ret = httpUpdate.update(client, webUrlStr + "/OnidaSounBar_PlatformIO_20210401_20211205.bin");
    Serial.print("ret :");
    Serial.println(ret);
    switch (ret)
    {
        case HTTP_UPDATE_FAILED:
            Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
            break;

        case HTTP_UPDATE_NO_UPDATES:
            Serial.println("HTTP_UPDATE_NO_UPDATES");
            break;

        case HTTP_UPDATE_OK:
            Serial.println("HTTP_UPDATE_OK");
            break;
    }

    //Testing Code...stops here!!!!!
    // while (true)
    // {

    // }
}

void Ota::checkDoOta(String serialNumber, String activation, String version)
{
    //Get Version Number
    httpClient.begin(webUrlStr + "GetVersion?serialNumber=" + serialNumber + "&activationCode=" + activation);
    int httpCode = httpClient.GET();
    Serial.print("HTTP Response code: ");
    Serial.println(httpCode);
    if (httpCode > 0)
    {
        if (httpCode == HTTP_CODE_OK)
        {
            String payload = httpClient.getString();
            if (payload != "NOT OK") {
                // Serial.println(payload);
                // Serial.println(payload.length());
                String newVersion = payload.substring(payload.length() - 8, payload.length()-2);
                Serial.println(version.toInt());
                Serial.println(newVersion.toInt());
                if (version.toInt() < newVersion.toInt())
                {
                    Serial.println("Downloading OTA");
                    doOta(serialNumber, activation);
                }
                else {
                    Serial.println("Version is current");
                }
            } else {
                Serial.println("Not Valid request");
            }
        }
    }
    //Testing Code...stops here!!!!!
    // while (true)
    // {

    // }
}