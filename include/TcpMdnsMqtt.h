/*
  * TcpMdnsMqtt.h - Library for storing data in flash code.
  * Created by Suresh Kumar, July 25, 2019.
*/
#ifndef TcpMdnsMqtt_h
#define TcpMdnsMqtt_h

#include "Arduino.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
//#include "TcpMdnsMqtt.h"
//#include "SplRemote.h"

class TcpMdnsMqtt {
  public:
  TcpMdnsMqtt();
  void startTcpMdnsMqtt(String serNum, String actCode, String awsCode, String mobCode);
  void tcpLoop();
  void mqttLoop();
  // void decodeData(String dataString);

  private:
    String deviceSerialNumber = "";
    String deviceActivationCode = "";
    String deviceAwsCode = "";
    String deviceMobileCode = "";     

};

#endif