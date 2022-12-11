#include <Arduino.h>


// Wyjscie = Człon P + Człon I + Człon D

// Człon P = Kp * error gdzie error to roznica pomiędzy wielokością zadaną a mierzoną

// Człon I = Ki * sumaBłędów gdzie sumaBłędów = sumaBłędów + (error + lastError)*timeChange/2

// Człon D = Kd * Derror gdzie Derror = (error-lastError)/timeChange lub Derror = (Input - lastInput)/timeChange gdzie input to sygnał mierzony


class PID
{
private:
public:
    int settime = 1000;
    float Kp = 1, Ki = 0.0035, Kd = 0.7;
    float Pout, Iout, Dout;
    float currentMillis, lastMillis;
    unsigned int input;
    float error, lastError;
    float setPoint = 155;
    float errorSum;
    float derror;
    float output;

    PID()
    {
    }

    void start()
    {   
        extern Thermometer thermometer;
        extern Heater heater;

        currentMillis = millis();
        if (currentMillis - lastMillis >=settime)
        {
            input = thermometer.currentTemp;
            error = setPoint - input;
            errorSum = errorSum + ((error+lastError)*0.5);
            derror = (error - lastError);
            Pout = Kp*error;
            Iout = Ki*errorSum;
            Dout = Kd *derror;
            /*
            Serial.print("Człon P = ");
            Serial.print(Pout);
            Serial.print("  Człon i = ");
            Serial.print(Iout);
            Serial.print("  Człon D = ");
            Serial.println(Dout);
            */

            if(Iout > 100)
            {
                Iout = 100;
            }
            if(Iout < 0)
            {
                Iout = 0;
            }

            output = Pout + Iout + Dout;

            

            if(output > 100)
            {
                output = 100;
            }
            if(output < 0)
            {
                output = 0;
            }

            heater.SetPower(output);
            /*Serial.print("  Output = ");
            Serial.println(output);*/
            lastMillis = currentMillis;
            lastError = error;

        }
    }
};


