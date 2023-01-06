#include <Arduino.h>
#include <TFT_ILI9163C.h>

class Display : public TFT_ILI9163C
{
private:
    const int maxY = 128;
    const int maxX = 160;
    const float multiplier = 2.34375;
    int currentMilis1 = 0;
    int lastMilis1 = 0;

public:
    // Variables
    int time = 0;
    float temp = 0;
    int prevTime = 0;
    float dispprevTemp = 0;
    float dispTemp = 0;
    // Constructor
    Display(uint8_t cspin, uint8_t dcpin, int _time, float _temp, uint8_t rstpin = 255)
        : TFT_ILI9163C(cspin, dcpin, rstpin)

    {
        time = _time;
        temp = _temp;
    }
    // Methods
    void showResolution()
    {
        print(width());
        print("x");
        println(height());
    }

    void gridChart()
    {

        drawFastHLine(0, maxY - 1, 160, WHITE);
        drawFastHLine(0, maxY - 21, 160, WHITE);
        setCursor(0, maxY - 30);
        print("47");
        drawFastHLine(0, maxY - 41, 160, WHITE);
        setCursor(0, maxY - 50);
        print("94");
        drawFastHLine(0, maxY - 60, 160, WHITE);
        setCursor(0, maxY - 70);
        print("140");
        drawFastHLine(0, maxY - 81, 160, WHITE);
        setCursor(0, maxY - 90);
        print("188");
        drawFastHLine(0, maxY - 100, 160, WHITE);
        setCursor(0, maxY - 110);
        print("234");
        drawFastHLine(0, maxY - 120, 160, WHITE);
        setCursor(0, 0);
        print("281");
    }

    void showTemperature()
    {
        setCursor(0, 0);
        fillRect(72, 0, 98, 128, BLACK);
        setCursor(2, 40);
        setTextSize(2);
        print("Time = ");
        print(time);
        setCursor(2, 60);
        print("Temp = ");
        println(temp);
        // temp =  thermo.temperature(RNOMINAL, RREF);
    }

    void drawChart()
    {
        // drawPixel(time, 128-dispTemp, CYAN);
        drawLine(prevTime, maxY - dispprevTemp, time, maxY - dispTemp, CYAN);
        prevTime = time;
        dispprevTemp = dispTemp;
        dispTemp = temp / multiplier;
    }

    void baseMenu()
    {
        if (showed == 0 || changed == 1)
        {
            switch (choice)
            {
            case 0:
                fillRect(0, 0, 160, 160, BLACK);
                setCursor(52, 45);
                setTextSize(2);
                print("Start");
                setCursor(40, 65);
                print("Options");
                showed = 1;
                break;

            case 1:
                fillRect(0, 0, 160, 160, BLACK);
                fillRect(0, 41, 160, 17, RED);
                setCursor(52, 42);
                setTextSize(2);
                print("Start");
                setCursor(40, 62);
                print("Options");
                setCursor(8, 82);
                print("Select Paste");
                showed = 1;
                break;

            case 2:
                fillRect(0, 0, 160, 160, BLACK);
                setCursor(52, 42);
                setTextSize(2);
                print("Start");
                fillRect(0, 61, 160, 17, RED);
                setCursor(40, 62);
                print("Options");
                setCursor(8, 82);
                print("Select Paste");
                showed = 1;
                break;

                 case 3:
                fillRect(0, 0, 160, 160, BLACK);
                setCursor(52, 42);
                setTextSize(2);
                print("Start");
                setCursor(40, 62);
                print("Options");
                fillRect(0, 81, 160, 17, RED);
                setCursor(8, 82);
                print("Select Paste");
                showed = 1;
                break;
            }
        }
    }

    void optionsMenu()
    {
        if (showed == 0 || changed == 1)
        {
            switch (choice)
            {
            case 0:
                fillRect(0, 0, 160, 124, BLACK);
                setCursor(57, 42);
                setTextSize(2);
                print("View");
                setCursor(8, 62);
                print("Temperatures");;
                setCursor(8, 82);
                print("Mode");;
                showed = 1;
                break;

            case 1:
                fillRect(0, 0, 160, 124, BLACK);
                fillRect(0, 41, 160, 17, RED);
                setCursor(57, 42);
                setTextSize(2);
                print("View");
                setCursor(8, 62);
                print("Temperatures");
                setCursor(57, 82);
                print("Mode");;
                showed = 1;
                break;

            case 2:
                fillRect(0, 0, 160, 124, BLACK);
                setCursor(57, 42);
                setTextSize(2);
                print("View");
                fillRect(0, 61, 160, 17, RED);
                setCursor(8, 62);
                print("Temperatures");
                setCursor(57, 82);
                print("Mode");;
                showed = 1;
                break;


                case 3:
                fillRect(0, 0, 160, 124, BLACK);
                setCursor(57, 42);
                setTextSize(2);
                print("View");
                setCursor(8, 62);
                print("Temperatures");
                fillRect(0, 81, 160, 17, RED);
                setCursor(57, 82);
                print("Mode");;
                showed = 1;
                break;

            }
        }
    }

    void viewMenu()
    {
        if (showed == 0 || changed == 1)
        {
            switch (choice)
            {
            case 0:
                fillRect(0, 0, 160, 124, BLACK);
                setCursor(52, 45);
                setTextSize(2);
                print("Chart");
                setCursor(40, 65);
                print("Digital");
                showed = 1;
                break;

            case 1:
                fillRect(0, 0, 160, 124, BLACK);
                fillRect(0, 44, 160, 17, RED);
                setCursor(52, 45);
                setTextSize(2);
                print("Chart");
                setCursor(40, 65);
                print("Digital");
                showed = 1;
                break;

            case 2:
                fillRect(0, 0, 160, 124, BLACK);
                setCursor(52, 45);
                setTextSize(2);
                print("Chart");
                fillRect(0, 64, 160, 17, RED);
                setCursor(40, 65);
                print("Digital");
                showed = 1;
                break;
            }
        }
    }

    void temperaturesMenu()
    {
        if (showed == 0 || changed == 1)
        {
            switch (choice)
            {
            case 0:
                fillRect(0, 0, 160, 124, BLACK);
                setCursor(43, 47);
                setTextSize(2);
                print("Preheat");
                setCursor(48, 67);
                print("Peak");
                showed = 1;

                break;

            case 1:
                fillRect(0, 0, 160, 124, BLACK);
                fillRect(0, 46, 160, 17, RED);
                setCursor(43, 47);
                setTextSize(2);
                print("Preheat");
                setCursor(48, 67);
                print("Peak");
                showed = 1;
                break;

            case 2:
                fillRect(0, 0, 160, 124, BLACK);
                setCursor(43, 47);
                setTextSize(2);
                print("Preheat");
                fillRect(0, 66, 160, 17, RED);
                setCursor(48, 67);
                print("Peak");
                showed = 1;
                break;
            }
        }
    }

    void pwnMenu()
    {
        if (showed == 0 || changed == 1)
        {
            switch (choice)
            {
            case 0:
                fillRect(0, 0, 160, 124, BLACK);
                setCursor(43, 47);
                setTextSize(2);
                print("Preheat");
                setCursor(48, 67);
                print("Reflow");
                showed = 1;

                break;

            case 1:
                fillRect(0, 0, 160, 124, BLACK);
                fillRect(0, 46, 160, 17, RED);
                setCursor(43, 47);
                setTextSize(2);
                print("Preheat");
                setCursor(48, 67);
                print("Reflow");
                showed = 1;
                break;

            case 2:
                fillRect(0, 0, 160, 124, BLACK);
                setCursor(43, 47);
                setTextSize(2);
                print("Preheat");
                fillRect(0, 66, 160, 17, RED);
                setCursor(48, 67);
                print("Reflow");
                showed = 1;
                break;
            }
        }
    }

    void modeMenu()
    {
        if (showed == 0 || changed == 1)
        {
            switch (choice)
            {
            case 0:
                fillRect(0, 0, 160, 124, BLACK);
                setCursor(43, 47);
                setTextSize(2);
                print("Preheat");
                setCursor(48, 67);
                print("Reflow");
                showed = 1;

                break;

            case 1:
                fillRect(0, 0, 160, 124, BLACK);
                fillRect(0, 46, 160, 17, RED);
                setCursor(43, 47);
                setTextSize(2);
                print("Preheat");
                setCursor(48, 67);
                print("Reflow");
                showed = 1;
                break;

            case 2:
                fillRect(0, 0, 160, 124, BLACK);
                setCursor(43, 47);
                setTextSize(2);
                print("Preheat");
                fillRect(0, 66, 160, 17, RED);
                setCursor(48, 67);
                print("Reflow");
                showed = 1;
                break;
            }
        }
    }

    void pasteMenu()
    {
        if (showed == 0 || changed == 1)
        {
            switch (choice)
            {
            case 0:
                fillRect(0, 0, 160, 124, BLACK);
                setCursor(3, 47);
                setTextSize(1);
                print("Sn96.5Ag3Cu0.5");
                setCursor(3, 67);
                print("Sn62Pb36Ag2");
                showed = 1;

                break;

            case 1:
                fillRect(0, 0, 160, 124, BLACK);
                fillRect(0, 46, 160, 17, RED);
                setCursor(3, 47);
                setTextSize(1);
                print("Sn96.5Ag3Cu0.5");
                setCursor(3, 67);
                print("Sn62Pb36Ag2");
                showed = 1;
                break;

            case 2:
                fillRect(0, 0, 160, 124, BLACK);
                setCursor(3, 47);
                setTextSize(1);;
                print("Sn96.5Ag3Cu0.5");
                fillRect(0, 66, 160, 17, RED);
                setCursor(3, 67);
                print("Sn62Pb36Ag2");
                showed = 1;
                break;
            }
        }
    }
    
    void preheatTempControl()
    {
        if (showed == 0 || changed == 1)
        {
            fillRect(0, 0, 160, 124, BLACK);
            setCursor(63, 58);
            setTextSize(2);
            print(preheatTemp);
            showed = 1;
        }
    }

    void reflowTempControl()
    {
        if (showed == 0 || changed == 1)
        {
            fillRect(0, 0, 160, 124, BLACK);
            setCursor(63, 58);
            setTextSize(2);
            print(reflowTemp);
            showed = 1;
        }
    }

    void changeScreen(int screen1, int screen2, int screen3, int changeViewType, bool changeToAnalogParam, bool changeMode, bool changeTemp, int parameter1, int parameter2)
    {
        if (press == 1)
        {
            switch (choice)
            {
            case 1:
                userPick = screen1;
                press = 0;
                changed = 1;
                time = 0;
                if (changeViewType == 1)
                    viewType = 2;
                if (changeToAnalogParam)
                {
                    count = parameter1;
                    num = parameter1;
                }
                if(changeMode)
                {
                    plateu = true;
                }
                break;

                if(changeTemp)
                {
                    preheatTemp = 155;
                    reflowTemp = 210;
                }

            case 2:
                userPick = screen2;
                press = 0;
                changed = 1;
                time = 0;
                if (changeViewType == 1)
                    viewType = 1;
                if (changeToAnalogParam)
                {
                    count = parameter2;
                    num = parameter2;
                }

                if(changeMode)
                {
                    plateu = false;
                }


                if(changeTemp)
                {
                    preheatTemp = 155;
                    reflowTemp = 220;
                }

                break;
            case 3:
                userPick = screen3;
                press = 0;
                changed = 1;
                time = 0;
                break;
            default:
                userPick = screen1;
                break;
            }
        }
    }

    void Draw()
    {
        currentMilis1 = millis();
        setTextSize(1);

        if (showed == 0 || changed == 1)
        {
            fillRect(0, 0, 160, 160, BLACK);
            showed = 1;
        }

        if (currentMilis1 - lastMilis1 >= oneSecond)
        {
            switch (viewType)
            {
            case 1:
                showTemperature();
                break;

            case 2:
                if (maxX >= time)
                {

                    gridChart();
                    drawChart();
                }
                else
                {
                    fillRect(0, 0, 160, 128, BLACK);
                    time = 0;
                    prevTime = 0;
                    gridChart();
                }
                break;
            }

            lastMilis1 = currentMilis1;
            time += 1;
        }
    }
};
