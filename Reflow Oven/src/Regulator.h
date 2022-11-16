#include <Arduino.h>

class Regulator
{
private:
    int tempDifference = 0;
    int tempDifferenceOld = 0;
    int atakFactor = 30;
    int kontraFactor = 1000;
    int atak = 0;
    int kontra = 0;
    float timeElapsed, time, timeOld;
    int power = 0;
    int intervalToCompare = 900;
    int interval = 0;
    int temperaturaOld = 0;

public:
    volatile int temperaturaZadana = 155;
    volatile int aktualnyPowerPodtrzymania = 30;

    int komunikat1 = 0;
    int komunikat2 = 0;
    int komunikat3 = 0;
    int komunikat4 = 0;

    Regulator()
    {
    }

    void IrqGo()
    {
        extern Thermometer thermometer;
        extern Heater heater;
        if (temperaturaOld == thermometer.currentTemp && interval < intervalToCompare)
        {
            interval++;
            return;
        }
        interval = 0;
        temperaturaOld = thermometer.currentTemp;

        tempDifference = temperaturaZadana - thermometer.currentTemp;

        int tmp2 = temperaturaZadana - 155;

        if (tmp2 < 0)
            tmp2 = 0;

        atak = 0.01 * atak + ((atakFactor + tmp2) * tempDifference);

        time = millis();
        timeElapsed = (time - timeOld) / 1000;
        kontra = kontraFactor * ((tempDifference - tempDifferenceOld) / timeElapsed);
        timeOld = time;
        power = atak + kontra;

        if (power < 0)
        {
            power = 0;
        }
        if (power > 100)
        {
            power = 100;
        }

        tempDifferenceOld = tempDifference;

       /* if (tempDifference == 0 && power == 0)
        {
            power = aktualnyPowerPodtrzymania + (tmp2 / 3);
        }*/
        heater.SetPower(power);

        komunikat1 = atak;
        komunikat2 = kontra;
        komunikat3 = thermometer.currentTemp;
        komunikat4 = heater.GetPower();
    }
};
