#include <Arduino.h>

class Thermometer
{
private:
    int thermPin;
    int pinValue = 0;
    int pinValueTmp = 0;
    int pinValueOld = 0;
    int countAttempt = 0;
    float voltResolution = maxVoltage / voltageResolution;

    float readRes = 0;

    float thermistorResistance(int inValue) // Wyliczenie oporu termistora
    {
        if (inValue < 1)
            inValue = 1;

        float vO = inValue * voltResolution;
        long double iR = vO / R1;
        float uT = maxVoltage - vO;
        float rT = uT / iR;
        return rT;
    }
    
    float readTemperatureResistance(int temperature) // Przeliczenie temperatury na ohmy
    {
        if (temperature > lengthTabFull)
        {
            return -1;
        }
        int indexTempTab = temperature / temperatureTabStep;
        int indexOffsetTempTab = temperature - (indexTempTab * temperatureTabStep);
        float resValue = resistanceTab[indexTempTab] - resistanceTab[indexTempTab + 1];
        resValue /= temperatureTabStep;
        resValue *= indexOffsetTempTab;
        resValue = resistanceTab[indexTempTab] - resValue;

        return resValue * 1000;
    }

public:
    int currentTemp = 0;

    Thermometer(int pin)
    {
        thermPin = pin;
    }

    int GetTempPin()
    {
        return analogRead(thermPin);
    }

    void temperatureRead()
    {
        pinValue = GetTempPin();

        for (int i = 0; i < maxAttempt; i++)
            pinValueTmp += pinValue;
        pinValueOld = pinValueTmp / maxAttempt;
        pinValueTmp = 0;
        float rT = thermistorResistance(pinValueOld);
        for (int i = 0; i < lengthTabFull; i++)
        {
            readRes = readTemperatureResistance(i);
            if (readRes <= rT)
            {
                currentTemp = i;
                return;
            }
        }
        currentTemp = -100;
        return;
    }
};
