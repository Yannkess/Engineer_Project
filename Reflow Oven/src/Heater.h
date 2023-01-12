#include <Arduino.h>

class Heater
{
private:

    float currentMillisf, lastMillisf = 0;
    volatile int power = 100;
    const int timeOnToCompare = 100;
    volatile int timeOn = timeOnToCompare;
    volatile int timeOff = 0;
    int timeOnCount = 0;
    int timeOffCount = 0;
    bool hotOn = false;
    volatile bool swOn = false;
    


public:

    
    Heater()
    {
    }

    void Start()
    {

        currentMillisf = millis();
        if(swOn == false)
        {
            return;
        }
        if (timeOnCount < timeOn)
        {
            if(hotOn == false)
            {
                hotOn = true;
                analogWrite(heaterPin, 255);
            }
            timeOnCount++;
            


            return;
        }
        if (timeOffCount < timeOff)
        {
            if(hotOn == true)
            {
                hotOn = false;
                analogWrite(heaterPin,0);
            }
            timeOffCount++;
            return;
        }
        timeOffCount = 0;
        timeOnCount = 0;
    }

    void On()
    {
        swOn = true;
    }

    void Off()
    {
        swOn = false;
        analogWrite(heaterPin, 0);
    }

    void SetPower(int _power)
    {
        if (_power <0)
        _power = 0;
        if(_power > 100)
        _power = 100;
        power = _power;
        timeOn = timeOnToCompare - (100- power);
        timeOff = timeOnToCompare - timeOn;
    }

    int GetPower()
    {
        return power;
    }
};
