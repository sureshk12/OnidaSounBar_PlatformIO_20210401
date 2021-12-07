/*
  TcpMdnsMqtt.cpp - Library for storing data in flash code.
  Created by Suresh Kumar, July 11, 2019.
*/

#include "Arduino.h"  // Arduino Library
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ESPmDNS.h>
#include "TcpMdnsMqtt.h"
//#include "SplRemote.h"
#include <string>
#include "ShaLib.h"

WiFiServer wifiServer(5045);//TCP Server
uint8_t data[300];
WiFiClientSecure httpsClient;//Https Client
PubSubClient mqttClient(httpsClient);//Mqtt Client
ShaLib shalib;

long messageSentAt = 0;
int dummyValue = 0;
char pubMessage[128];

//AWS
const char *endpoint = "a90n4qxu56af4-ats.iot.us-east-1.amazonaws.com";
const int port = 8883;

const char *sur;
char *pubTopic;
char *subTopic;
char *myHostname;

extern const char rootCA[];
extern const char certificate[];
extern const char privateKey[];

String recdSerNum = "";
String recdActCode = "";
String mobCode = "";
String awsCode = "";
String recdDummyVal = "";
String recdRepeatValue = "";
String recdAdditionData = "";
String recdMainData = "";
String recdDigest = "";

String tSerNum = "";
String tActCode = "";
String tAwsCode = "";
String tMobCode = "";

//SplRemote splremote(0);
//const char *myHostname = "HallTv";//hostname for mDNS

TcpMdnsMqtt::TcpMdnsMqtt() {

}

void decodeData(String dataString) {
  String dataStr = dataString;
  recdSerNum = dataStr.substring(0, 14);
  recdActCode = dataStr.substring(15,25);
  recdDigest = dataStr.substring(26,90);
  recdDummyVal = dataStr.substring(91,94);
  recdRepeatValue = dataStr.substring(95,97);
  recdAdditionData = dataStr.substring(98,100);
  recdMainData = dataStr.substring(101,103);
  // Serial.print(recdSerNum);Serial.print(" ? ");Serial.println(tSerNum);
  // Serial.print(recdActCode);Serial.print(" ? ");Serial.println(tActCode);    
  // Serial.println("recdDigest = " + recdDigest);
  // Serial.print(recdRepeatValue);Serial.print(" : ");Serial.print(recdAdditionData);Serial.print(" : ");Serial.println(recdMainData);    
}

String calculateDigestfromReceivedDigest(String rDigest, String dAwsMobCode) {
  //get STEP
  // Serial.println("Digest Recd = " + rDigest);
  char str[2];
  str[0] = rDigest[3];
  int calStep = str[0] - 48;
  // Serial.print("calculatedStep = "); Serial.println(calStep);
  //Get Random
  String calRan = "";
  for (int x =0; x < 8; x++) {
    calRan = calRan + rDigest[(3 + calStep) + (x * calStep) ];
  }
  // Serial.println("Calculated random = " + calRan);

  // Serial.println("Received Serial Number = " + recdSerNum);
  // Serial.println("Received Activation = " + recdActCode);
  // Serial.println("Received DataStr = " + recdMainData);
  // Serial.println("Device AWS / Mobile code = " + dAwsMobCode);

  String calDigest = shalib.getDigest(recdSerNum, recdActCode, dAwsMobCode, calRan, recdMainData);
  //code the step @ pos 3
  calDigest[3]=calStep + 48;
  //code the random number
  for(int x = 0; x < 8; x++) {
    calDigest[(3 + calStep) + (x * calStep)] = calRan[x];
  }

  // Serial.println("Calculated Digest = " + calDigest);
  return calDigest;
}

void mqttCallback (char* topic, byte* payload, unsigned int length) {
  // Serial.print("AWS Message : ");
  // Serial.println(topic);
  // for (int i = 0; i < length; i++) {
  //     Serial.print((char)payload[i]);
  // }
  // Serial.print("\r\n");
  String datStrM = (char *)payload;
  decodeData(datStrM); 

  int err = 0;
  if(recdSerNum.equals(tSerNum)) {                   
    if(recdActCode.equals(tActCode)) {
      //Move Forward
      String calculatedDigest = calculateDigestfromReceivedDigest(recdDigest, tAwsCode);
      // Serial.println("Calculated Digest = " + calculatedDigest);
      if(recdDigest.equals(calculatedDigest)) {
        // client.write("OK::\r\n\0");
        Serial.println("AWS Data = " + recdRepeatValue + " : " + recdAdditionData + " : " + recdMainData);
      } else {
        // client.write("WRONGDEVICE\r\n\0");
        Serial.println("WRONGDEVICE3\r\n\0");
        //err = 1;
      }
    } else {
      // client.write("WRONGDEVICE\r\n\0");
      Serial.println("WRONGDEVICE2\r\n\0");
      //err = 1;
    }
  } else {
    // client.write("WRONGDEVICE\r\n\0");
    Serial.println("WRONGDEVICE1\r\n\0");
    //err = 1;
  }
  int pprint = 0;
  while(err == 1) {
    if(pprint == 0){
      pprint = 1;
      Serial.println("WRONG CREDENTIALS :-( ");
    }
  }

  //splremote.sendDeviceCommand(0, (char *)payload, serialNumber, awsCode, mobileCode); 
}

void TcpMdnsMqtt::startTcpMdnsMqtt(String serNum1, String actCode1, String awsCode1, String mobCode1) {
  deviceSerialNumber = serNum1;
  deviceActivationCode = actCode1;
  deviceAwsCode = awsCode1;
  deviceMobileCode = mobCode1;
  tSerNum = serNum1;
  tActCode = actCode1;
  tAwsCode = awsCode1;
  tMobCode = mobCode1;

  char y[15];
  char u[15];
  char v[15];
  deviceSerialNumber.toCharArray(y, deviceSerialNumber.length()+1);
  pubTopic = y;
  deviceSerialNumber.toCharArray(u, deviceSerialNumber.length()+1);
  subTopic = u;
  deviceSerialNumber.toCharArray(v, deviceSerialNumber.length()+1);
  myHostname = v;

  //Set up WiFi Server
  //!!!! NO Error checking implemented

  wifiServer.begin();//TCP Socket server  
  //splremote.loadStbData();
  delay(100);
  
  //MDNS
  //!!!! NO Error checking implemented
  //delay(500);
  if (!MDNS.begin(myHostname)) {
    Serial.println("Error setting up MDNS responder!");
  } else {
    delay(1000);
    Serial.println("mDNS responder started");
    // Add service to MDNS-SD
    MDNS.addService("onida", "tcp", 5045);
  }
  //delay(1000);
  // Configure MQTT Client
  httpsClient.setCACert(rootCA);
  httpsClient.setCertificate(certificate);
  httpsClient.setPrivateKey(privateKey);

  mqttClient.setServer(endpoint, port);
  mqttClient.setCallback(mqttCallback);
  
  while (!mqttClient.connected()) {
    
    if (mqttClient.connect("ESP32_device")) {
      Serial.println("AWS Connected.");
      int qos = 0;
      mqttClient.subscribe(subTopic, qos);
      Serial.println("Topic Subscribed.");
    } else {
      Serial.print("Failed. Error state=");
      Serial.print(mqttClient.state());
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void TcpMdnsMqtt::tcpLoop() {
  WiFiClient client = wifiServer.available();
  boolean isClientConnected = false;  
  //unsigned long tart = millis(); 
  if (client) {                     
    Serial.println("new client");         
    /* check client is connected */           
    while (client.connected()) { 
      isClientConnected = true;         
      if (client.available()) {
        int len = client.read(data, 300);
        if(len < 300){
            data[len] = '\0';  
        }else {
            data[299] = '\0';
        }
        // Serial.print("MOB Message Received: ");            
        // Serial.println((char *)data);
        String dataStr = (char *)data;
        decodeData((char*)data);
        if(data[11] != 's') {
          String returnData = "";
          if(recdSerNum.equals(deviceSerialNumber)) {                   
            if(recdActCode.equals(deviceActivationCode)) {
              String calculatedDigest = calculateDigestfromReceivedDigest(recdDigest, deviceMobileCode);
              // Serial.println("received Digest = " + recdDigest);
              // Serial.println("Calculated Digest = " + calculatedDigest);
              if(recdDigest.equals(calculatedDigest)) {
              // if(mobCode.equals(deviceMobileCode)) {
                client.write("OK::\r\n\0");
                Serial.println("MOB Data = " + recdRepeatValue + " : " + recdAdditionData + " : " + recdMainData);
              } else {
                client.write("WRONGDEVICE\r\n\0");
              }
            } else {
               client.write("WRONGDEVICE\r\n\0");          
            }
          } else {
            client.write("WRONGDEVICE\r\n\0");
          }
          //client.stop(); 
        } else {
          String key2 = dataStr.substring(11,17);
          String key3 = dataStr.substring(18, 24);
          String key4 = dataStr.substring(25,35);
          Serial.println(key2);
          Serial.println(key3);
          Serial.println(key4);
          
          if(recdSerNum.equals(deviceSerialNumber)) {
            // Serial.println("key1 : Ok");
            if(key2.equals("suresh")) {
              //Serial.println("key2 : Ok");
              if(key3.equals("kaval0")) {
                //Serial.println("key3 : Ok");
                if(key4.equals(deviceActivationCode)) {
                  //Serial.println("key4 : Ok");
                  Serial.println("Iam in Registration Routive");

                  client.print(deviceMobileCode);
                  client.print(",");
                  client.println(deviceAwsCode);

                  Serial.print("Sent to Client Device Id as : ");
                  Serial.print(deviceMobileCode);
                  Serial.print(" : ");
                  Serial.println(deviceAwsCode);
                }
              }
            }
          }
        }       
      }
    }    
    if (isClientConnected) {
      //Serial.println("Client disconnected");
    }
  }  
}

void connectAWSIoT() {
  while (!mqttClient.connected()) {
    if (mqttClient.connect("ESP32_device")) {
      Serial.println("AWS Connected.");
      int qos = 0;
      mqttClient.subscribe(subTopic, qos);
      Serial.println("Topic Subscribed.");
    } else {
      Serial.print("Failed. Error state=");
      Serial.print(mqttClient.state());
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void TcpMdnsMqtt::mqttLoop() {
  if (!mqttClient.connected()) {
      Serial.println("Looks like lost connection!!!");
      connectAWSIoT();
  }
  mqttClient.loop();
}