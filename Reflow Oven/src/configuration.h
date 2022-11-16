#include <Arduino.h>

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

#define PinA 2  
#define PinB 3  
#define heaterPin A0

//Heater

//Time
int currentMilis = 0; 
int lastMilis = 0;
int lastMilis2 = 0;
int time = 0;
int processTime = 0;
float temp = 0;
float temp1 = 0;
//PWN
int interval = 4000;  // Control time with pwn signal
int interval2 = 500;
const int oneSecond = 1000; // Data reading time. 1000 = 1s.
int cycle = 0;
//Display
// Temperatures to set
int preheatTemp = 155;
int reflowTemp = 220;
//Process
int stage = 0;
bool started = false;
// Menu
int userPick = 0;
int choice = 1;
int viewType = 1;
int showed = 0;
//Encoder
long count = 1; 
unsigned long time1 = 0;
long num = 1;
int press = 0; 
int changed = 0;
//Thermistor
int const thermistorPin = A1;
float const maxVoltage = 5;
int const voltageResolution = 1023;
float const R1 = 4700;
int const temperatureTabStep = 5;

float const resistanceTab[]
{
    327.24,254.8,199.990,157.600,125.245,100.000,81.000,65.650,53.500,43.780,35.899,29.990,25.00,20.900,17.550,14.760,12.540,10.660,9.1,7.784,6.710,5.850,5.070,4.410,3.850,3.340,2.940,
    2.580,2.271,2.0,1.770,1.589,1.414,1.259,1.122,0.997,0.896,0.797,0.719,0.643,0.582,0.533,0.483,0.437,0.396,0.360,0.328,0.2993,0.2737,0.2507,0.2300,0.2114,0.1946,0.1794,0.1656,0.1531,
    0.1417,0.1314,0.1220,0.1134,0.1056
};

int lengthResistanceTab = sizeof(resistanceTab)/sizeof(float);
int lengthTabFull= lengthResistanceTab * temperatureTabStep;
int const maxAttempt = 8;