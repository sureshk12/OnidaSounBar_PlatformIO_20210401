/*
  KeySense.cpp - Library for storing data in flash code.
  Created by Suresh Kumar, July 11, 2019.
*/

#include "Arduino.h"  // Arduino Library
#include "KeySense.h"
#include "DeviceConstants.h"

/*
 * Constants 
*/
DeviceConstants dc1;

const int switchPin1 = dc1.switchPinVal;
const int ledPin1 = dc1.ledPinVal;
int keyDebounceCount = 0; //Counter for debouncing
unsigned long debounceStartTime = 0;
int ledStatus = 0; // 0 = OFF; 1 = ON

/*
 * Intilization of Class
 * Intilizes EEPROM with max Size
 * Set the Constant maxMem with max size
*/
KeySense::KeySense()
{
  
}

boolean KeySense::switchDetect(int num) {
  debounceStartTime = millis();
  keyDebounceCount = 1;
  ledStatus = 1;
  while ((keyDebounceCount > 0) && (millis() < (debounceStartTime + 6000))) {
    delay(100);
    //Push_button_state = digitalRead(switchPin1);
    if ((digitalRead(switchPin1)) == LOW) {
      keyDebounceCount ++;
      //Serial.println("Switch is LOW");
    } else {
      keyDebounceCount --;
      //Serial.println("Switch is HIGH");
    }
    if(ledStatus == 0) {
      ledStatus = 1;
      digitalWrite(ledPin1, HIGH);
    } else {
      ledStatus = 0;
      digitalWrite(ledPin1, LOW);
    }
    if (keyDebounceCount > num)
    {
      break;
    }
  }
  //Serial.print("Count = ");
  //Serial.println(keyDebounceCount);
  if(keyDebounceCount > num) {
    //Serial.println("Key detected !!! Stopping");
    return true;
  }
  //did not detect Key Sense
  digitalWrite(ledPin1, HIGH);
  //Serial.println("Did Not detect key!!!!");
  return false;
}