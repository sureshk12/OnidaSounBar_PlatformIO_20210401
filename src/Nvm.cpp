/*
  Nvm.cpp - Library for storing data in flash code.
  Created by Suresh Kumar, July 11, 2019.
*/

#include "Arduino.h"  // Arduino Library
#include <Preferences.h>   // Preferences Library
#include "Nvm.h"      // H file for Nvm


/*
 * Constants 
*/
Preferences pref;

/*
 * Intilization of Class
 * Intilizes EEPROM with max Size
 * Set the Constant maxMem with max size
*/
Nvm::Nvm()
{
  // initialize Preferences  
  pref.begin("sureshkaval@100",false);  
}

boolean Nvm::write_string(const char* addr, const char* str){
  pref.begin("sureshkaval@100",false); 
  pref.putString(addr, str);
  pref.end();
  return true;
}


boolean Nvm::read_string(const char* addr, char* buf){
  pref.begin("sureshkaval@100",false);
  String temp = pref.getString(addr);
  //Serial.println (preferences.getString(addr));
  temp.toCharArray(buf, temp.length()+1);
  pref.end();
  return true;
}

/*
 * Public Function 
 * To check if EEprom is valid
 * Return TRUE if EEPROM is valid
 * Return False if EEPROM is not valid
*/
boolean Nvm::isSsidValid(){
  char buf[6] = {'S', 'U', 'R', 'E', 'S', 'H'};
  char correctBuf[6];
  read_string("project",correctBuf);
  boolean retValue = true;
  for (int p=0; p<6; p++) {
    //Serial.print(buf[p]);Serial.print(" : ");Serial.println(correctBuf[p]);
    if(buf[p] != correctBuf[p]) {
      retValue = false;
    }
  }
  return retValue;
}

boolean Nvm::write_ssid(const char* ssidchar, const char* passchar){
  String project = "SURESH";
  char projectchar[7];
  project.toCharArray(projectchar, project.length()+1);
  Serial.printf("Writing PROJECT : %s , SSID: %s , PASS: %s\n", projectchar, ssidchar, passchar);
  write_string("project", projectchar);
  delay(100);
  write_string("ssid", ssidchar);
  delay(100);
  write_string("pass", passchar);
  delay(100);
  char ssidreadchar[33];
  char passreadchar[65];
  read_ssid(ssidreadchar, passreadchar);
  return true;  
}

boolean Nvm::read_ssid(char* ssidchar, char* passchar){
  read_string("ssid", ssidchar);
  //Serial.print("INSIDE SSID : ");
  //Serial.println(ssidchar);
  read_string("pass", passchar);
  //Serial.print("INSIDE PASS : ");
  //Serial.println(passchar);
  return true;
}

int Nvm::read_int(char* addr) {
  pref.begin("sureshkaval@100",false);
  return(pref.getInt(addr));
}

void Nvm::write_int(char* addr, int val) {
  pref.begin("sureshkaval@100",false);
  pref.putInt(addr, val);
}

void Nvm::write_String1(char* addr, String val) {
  pref.begin("sureshkaval@100",false);
  pref.putString(addr, val);
}

String Nvm::read_String1(char* addr) {
  pref.begin("sureshkaval@100",false);
  return(pref.getString(addr));
}