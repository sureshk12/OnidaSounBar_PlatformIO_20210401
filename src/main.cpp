#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h> // Preferences Library
#include "SsidNew.h"
#include "TcpMdnsMqtt.h"
#include "DeviceConstants.h"
#include "security.h"
#include "Ota.h"
#include "DoSwWork.h"

Preferences preferences;
Security securityObj(0);
SsidNew ssidnew;
TcpMdnsMqtt tcpmdnsmqtt;
DeviceConstants dc;
Ota ota;
DoSwWork doswworkmain;

int testPrint = 0;                     //[TESTING]Used for Testing
const int switchPin = dc.switchPinVal; //Switch Port
const int ledPin = dc.ledPinVal;       //LED Port
const int switchControl = dc.ledSwitch;//Switch Control

String mainSerialNumber;
String mainActivationCode;
String mainAwsCode;
String mainMobCode;
String mainSecurityCode;
String mainVersion;

void setup()
{
  // put your setup code here, to run once:
  //Set Serial communication for Debug Messages
  Serial.begin(115200);
  delay(100);
  //Get Device Constants
  securityObj.begin(preferences);
  mainSerialNumber = securityObj.getSerialNumber();
  mainActivationCode = securityObj.getActivationCode();
  mainAwsCode = securityObj.getAwsCode();
  mainMobCode = securityObj.getMobCode();
  mainSecurityCode = securityObj.getDevShaDigest();
  //mainVersion = securityObj.getVersion();
  mainVersion = "000001";

  //Printing scurity codes...
  Serial.println("Serial Number : " + mainSerialNumber);
  Serial.println("ActivationCode : " + mainActivationCode);
  // Serial.println("AwsCode : " + mainAwsCode);
  // Serial.println("MobCode : " + mainMobCode);
  // Serial.println("MacId : " + WiFi.macAddress());
  //Serial.println(mainSecurityCode);
  //Serial.println("Version : " + mainVersion);

  //Set the Pins for LED and SWITCH
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(switchControl, OUTPUT);
  digitalWrite(ledPin, HIGH);
  digitalWrite(switchControl, HIGH);
  delay(50);
  doswworkmain.begin();

  //Check for SSID and connect to previous stored SSID
  ssidnew.wifiConnect();

  //Check OTA
  ota.checkDoOta(mainSerialNumber, mainActivationCode, mainVersion);

  //Start TCP and MQtt 
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