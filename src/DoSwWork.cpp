#include "Arduino.h" // Arduino Library
#include "DoSwWork.h"
#include "DeviceConstants.h"

DeviceConstants devConsts;
//String prevData = "";
unsigned long startTime;
unsigned long delta;

int DoSwWork::switchStatus;

DoSwWork::DoSwWork()
{
}

void DoSwWork::begin() {
    //Serial.println("Iam in DoSwWork - begin function");
    digitalWrite(devConsts.ledSwitch, HIGH);
    switchStatus = 1;
    startTime = millis();
}

int DoSwWork::on_Off(String data)
{
    delta = millis() - startTime;
    if (delta > 500)
    {
        startTime = millis();
        Serial.println("Data Received in on_off= " + data);
        //prevData = data;
        if (data.equals("10"))
        {
            digitalWrite(devConsts.ledSwitch, LOW);
            switchStatus = 0;
        }
        if (data.equals("11"))
        {
            digitalWrite(devConsts.ledSwitch, HIGH);
            switchStatus = 1;
        }
        if(data.equals("13")) {
            if (switchStatus == 0) {
                digitalWrite(devConsts.ledSwitch, HIGH);
                switchStatus = 1;
            } else {
                digitalWrite(devConsts.ledSwitch, LOW);
                switchStatus = 0;
            }            
        }
        return switchStatus;
    } else {
        return 99;
    }
}
