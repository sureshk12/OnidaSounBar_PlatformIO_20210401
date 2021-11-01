#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h> // Preferences Library
#include "SsidNew.h"
#include "TcpMdnsMqtt.h"
#include "DeviceConstants.h"
#include "security.h"
#include "Ota.h"

Preferences preferences;
Security securityObj(0);
SsidNew ssidnew;
TcpMdnsMqtt tcpmdnsmqtt;
DeviceConstants dc;
Ota ota;

int testPrint = 0;                     //[TESTING]Used for Testing
const int switchPin = dc.switchPinVal; //Switch Port
const int ledPin = dc.ledPinVal;       //LED Port

String mainSerialNumber;
String mainActivationCode;
String mainAwsCode;
String mainMobCode;
String mainSecurityCode;

void setup()
{
  // put your setup code here, to run once:
  //Set Serial communication for Debug Messages
  Serial.begin(115200);
  delay(100);

  securityObj.begin(preferences);
  mainSerialNumber = securityObj.getSerialNumber();
  mainActivationCode = securityObj.getActivationCode();
  mainAwsCode = securityObj.getAwsCode();
  mainMobCode = securityObj.getMobCode();
  mainSecurityCode = securityObj.getDevShaDigest();

  //Printing scurity codes...
  // Serial.println("Serial Number : " + mainSerialNumber);
  // Serial.println("ActivationCode : " + mainActivationCode);
  // Serial.println("AwsCode : " + mainAwsCode);
  // Serial.println("MobCode : " + mainMobCode);
  // Serial.println("MacId : " + WiFi.macAddress());
  //Serial.println(mainSecurityCode);

  //Set the Pins for LED and SWITCH
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  // Serial.println("iam in main setup function line 26");
  //Check for SSID and connect to previous set SSID
  ssidnew.wifiConnect();
  //Check OTA
  // ota.checkDoOta(mainSerialNumber, mainActivationCode);
  tcpmdnsmqtt.startTcpMdnsMqtt(mainSerialNumber, mainActivationCode, mainAwsCode, mainMobCode);
  delay(500); // needed to start-up task1
}

void loop()
{
  // put your main code here, to run repeatedly:
  //[TESTING]Used for Testing
  if (testPrint == 0)
  {
    Serial.println("Waiting for USER command!!!!");
    testPrint = 1;
  }

  if ((digitalRead(switchPin)) == LOW)
  {
    ssidnew.setUpNewSsid();
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    ssidnew.wifiConnect();
  }

  tcpmdnsmqtt.mqttLoop();
  tcpmdnsmqtt.tcpLoop();
  delay(100);
}