#include <Arduino.h>

class Encoder
{
private:
    /* data */
public:
    // Variables

    // Constructor
    Encoder(/* args */)
    {
    }
    // Methods
    static void blinkA()
    {
        if ((millis() - time1) > 3)
            count++;
        time1 = millis();
    }

    static void blinkB()
    {
        if ((millis() - time1) > 3)
            count--;
        time1 = millis();
    }

    void analogButton()
    {
        if (digitalRead(8) < 1 && changed == 0)
        {
            press = 1;
        }

        if (digitalRead(8) == 1)
        {
            changed = 0;
            press = 0;
        }

        while (num != count)
        {
            num = count;
            choice = num;
            showed = 0;
        }
    }

    void analogButtonControl(int control)
    {
        if (choice > control)
        {
            choice = 1;
            num = 1;
            count = 1;
        }

        if (choice < 1)
        {
            choice = control;
            num = control;
            count = control;
        }
    }
};
