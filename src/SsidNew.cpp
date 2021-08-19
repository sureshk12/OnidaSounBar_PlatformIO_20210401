/*
  KeySense.cpp - Library for storing data in flash code.
  Created by Suresh Kumar, July 11, 2019.
*/

#include "Arduino.h" // Arduino Library
#include <WiFi.h>
#include "SsidNew.h"
#include "KeySense.h"
#include "Nvm.h"
// #include "Ota.h"

/*
 * Constants 
*/

char ssidChar[33];
String ssidStr = "suresh";
String passStr = "kumar";
char passChar[65];
const int switchPin = 0;
const int ledPin = 2;
// Ota ota;

/*
 * Intilization of Class
 * Intilizes EEPROM with max Size
 * Set the Constant maxMem with max size
*/
SsidNew::SsidNew()
{
}

void SsidNew::setUpNewSsid()
{
  while (1)
  {
    KeySense ks;
    if (ks.switchDetect())
    {
      Serial.println("\nKey Detected");

      int gotSsid = 0; //0 = SSUD
      //Init WiFi as Station, start SmartConfig
      while (gotSsid == 0)
      {
        if (WiFi.isConnected())
        {
          Serial.println("WIFI is Connected, Disconnecting!!!");
          WiFi.disconnect();
        }
        WiFi.mode(WIFI_AP_STA);
        WiFi.beginSmartConfig();
        delay(1000);

        //Wait for SmartConfig packet from mobile
        Serial.println("Waiting for SmartConfig.");
        while (!WiFi.smartConfigDone())
        {
          delay(500);
          Serial.print(".");
        }
        Serial.println("");
        Serial.println("SmartConfig received.");

        //Wait for WiFi to connect to AP
        Serial.println("Waiting for WiFi");
        while (WiFi.status() != WL_CONNECTED)
        {
          delay(500);
          Serial.print(".");
        }
        //check if SSID is isSsidValid
        if (WiFi.status() == WL_CONNECTED)
        {
          Serial.println("WIFI Connected!!!!");
          gotSsid = 1;
          ssidStr = WiFi.SSID();
          passStr = WiFi.psk();
          Serial.print("ssid : ");
          Serial.print(ssidStr);
          Serial.print("Password : ");
          Serial.println(passStr);
          ssidStr.toCharArray(ssidChar, ssidStr.length() + 1);
          passStr.toCharArray(passChar, passStr.length() + 1);
          Nvm nvm;
          nvm.write_ssid(ssidChar, passChar);
          delay(1000); //Added due to Android error "EspTouch failed"
          // WiFi.smartConfigDone(); //Added due to Android error "EspTouch failed"
          WiFi.stopSmartConfig(); //Added due to Android error "EspTouch failed"
        }
        else
        {
          Serial.println("WIFI NOT connected ???");
          WiFi.stopSmartConfig();
        }
      }
      ESP.restart();
      /*
      while(1) {
        //Stop 
      }
      */
    }
  }
}

void SsidNew::wifiConnect()
{
  Nvm nvm;
  if (nvm.isSsidValid())
  {
    //Memory OK
    nvm.read_ssid(ssidChar, passChar);
    // Serial.println("[Ssid.cpp 107]In SSID trying to read SSID , pass");
    // Serial.print("SSID            = "); Serial.println(ssidChar);
    // Serial.print("PASS            = "); Serial.println(passChar);
    //Serial.printf("Read from Memory - SSID : %s , PASS : ********** \r\n", ssidChar);
    //ota.checkDoOta(ssidChar, passChar);
    delay(100);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssidChar, passChar);
    Serial.print("Waiting for WiFi");
    int printCount = 0;
    int ledStatus = 0; // 0 = OFF; 1 = ON
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");

      if (ledStatus == 0)
      {
        ledStatus = 1;
        digitalWrite(ledPin, HIGH);
      }
      else
      {
        ledStatus = 0;
        digitalWrite(ledPin, LOW);
      }

      printCount++;
      if (printCount > 50)
      {
        printCount = 0;
        Serial.println();
      }
      if ((digitalRead(switchPin)) == LOW)
      {
        setUpNewSsid();
      }
    }
    digitalWrite(ledPin, HIGH);
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("WiFi Connected.");
      Serial.print("IP Address      = ");
      Serial.println(WiFi.localIP());
      //   ota.checkDoOta(ssidChar, passChar);
    }
    else
    {
      Serial.println("WiFi NOT Connected.");
    }
  }
  else
  {
    //No SSID
    Serial.println("FALSE");
    setUpNewSsid();
  }
}