class Reader
{
private:
const int oneSecond = 1000;
int lastMilis = 0;

public:
int time = 0;
    Reader()
    {
    }

    void read()
    {
        extern Thermometer thermometer;
        currentMilis = millis();
        
        if (currentMilis - lastMilis >= oneSecond)
        {
            lastMilis = currentMilis;
            Serial.print(time);
            Serial.print(";");
            Serial.println(thermometer.currentTemp);
            time++;
        
        }
    }
};
