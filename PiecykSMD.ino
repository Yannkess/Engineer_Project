
#include <Adafruit_MAX31865.h>
#include "max6675.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

Adafruit_MAX31865 thermo = Adafruit_MAX31865(4, 5, 6, 7);
TFT_ILI9163C display = TFT_ILI9163C(10,9);

#define PinA 2  
#define PinB 3  

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF 430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL 100.0

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF



//int thermoDO = 2;
//int thermoCS = 3;
//int thermoCLK = 8;

//MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

//Measure and Time
int currentMilis = 0; 
int lastMilis = 0;
int lastMilis1 = 0;
int lastMilis2 = 0;
int currentMilis1 = 0;
int time = 0;
int prevTime = 0;
int processTime = 0;
float temp = 0;
//PWN
int interval = 7000;  // Control time with pwn signal
int interval2 = 500;
int oneSecond = 1000; // Data reading time. 1000 = 1s.
int cycle = 0;
//Display
int maxY = 128;
int maxX = 160;
float dispprevTemp = 0;
float dispTemp = 0;
float multiplier = 2.34375;
// Temperatures to set
int preheatTemp = 160;
int reflowTemp = 180;
//Process
int stage = 0;
bool started = false;
// Menu
int userPick = 0;
int choice = 1;
int viewType = 2;
int showed = 0;
//Encoder
long count = 1; 
long num = 1;
unsigned long time1 = 0;
int press = 0; 
int lock = 0;
int changed = 0;


void blinkA()
{
  if ((millis() - time1) > 3)
        count ++; 
  time1 = millis();
}

void blinkB()
{
  if ((millis() - time1) > 3)  
        count --;
  time1 = millis();
}

void ptFaults()
{
     uint8_t fault = thermo.readFault();
    if (fault)
     {
      Serial.print("Fault 0x");
      Serial.println(fault, HEX);
      if (fault & MAX31865_FAULT_HIGHTHRESH) 
      {
        Serial.println("RTD High Threshold");
      }
      if (fault & MAX31865_FAULT_LOWTHRESH) 
      {
        Serial.println("RTD Low Threshold");
      }
      if (fault & MAX31865_FAULT_REFINLOW) 
      {
        Serial.println("REFIN- > 0.85 x Bias");
      }
      if (fault & MAX31865_FAULT_REFINHIGH) 
      {
        Serial.println("REFIN- < 0.85 x Bias - FORCE- open");
      }
      if (fault & MAX31865_FAULT_RTDINLOW) {
        Serial.println("RTDIN- < 0.85 x Bias - FORCE- open");
      }
      if (fault & MAX31865_FAULT_OVUV) 
      {
        Serial.println("Under/Over voltage");
      }
      thermo.clearFault();
    }
}

void showResolution()
{
  display.print(display.width());
  display.print("x");
  display.println(display.height());
}

void showTemperature()
{
  display.setCursor(0, 0);
  display.fillRect(72, 0, 98, 128, BLACK);
  display.setCursor(2, 40);
  display.setTextSize(2);
  display.print("Time = ");
  display.print(time);
  display.setCursor(2,60);
  display.print("Temp = ");
  display.println(temp);
  temp =  thermo.temperature(RNOMINAL, RREF);
}

void gridChart()
{
  
  
    display.drawFastHLine(0, maxY-1, 160, WHITE);
    display.drawFastHLine(0, maxY-21, 160, WHITE);
    display.setCursor(0, maxY-30);
    display.print("47");
    display.drawFastHLine(0, maxY-41, 160, WHITE);
    display.setCursor(0, maxY-50);
    display.print("94");
    display.drawFastHLine(0, maxY-60, 160, WHITE);
    display.setCursor(0, maxY-70);
    display.print("140");
    display.drawFastHLine(0, maxY-81, 160, WHITE);
    display.setCursor(0, maxY-90);
    display.print("188");
    display.drawFastHLine(0, maxY-100, 160, WHITE);
    display.setCursor(0, maxY-110);
    display.print("234");
    display.drawFastHLine(0, maxY-120, 160, WHITE);
    display.setCursor(0,0);
    display.print("281");
  
}

void drawChart()
{
  //display.drawPixel(time, 128-dispTemp, CYAN);
  display.drawLine(prevTime,maxY-dispprevTemp, time, maxY-dispTemp, CYAN);
  prevTime = time;
  dispprevTemp = dispTemp;
  temp = thermo.temperature(RNOMINAL, RREF);
  dispTemp = temp/multiplier;

}

void baseMenu()
{
  if (showed == 0 || changed == 1){
  switch(choice)
  {
    case 0:
    display.fillRect(0, 0, 160, 160, BLACK);
    display.setCursor(52, 45);
    display.setTextSize(2);
    display.print("Start");
    display.setCursor(40,65);
    display.print("Options");
    showed = 1;
    break;

    case 1:
    display.fillRect(0, 0, 160, 160, BLACK);
    display.fillRect(0, 44, 160, 17, RED);
    display.setCursor(52, 45);
    display.setTextSize(2);
    display.print("Start");
    display.setCursor(40,65);
    display.print("Options");
    showed = 1;
    break;

    case 2:
    display.fillRect(0, 0, 160, 160, BLACK);
    display.setCursor(52, 45);
    display.setTextSize(2);
    display.print("Start");
    display.fillRect(0, 64, 160, 17, RED);
    display.setCursor(40,65);
    display.print("Options");
    showed = 1;
    break;
  }
  }
}

void optionsMenu()
{
  if (showed == 0 || changed == 1){
  switch(choice)
  {
    case 0:
      display.fillRect(0, 0, 160, 124, BLACK);
      display.setCursor(57, 40);
      display.setTextSize(2);
      display.print("View");
      display.setCursor(8,60);
      display.print("Temperatures");
      display.setCursor(61,80);
      display.print("PWN");
      showed = 1;
    break;

    case 1:
      display.fillRect(0, 0, 160, 124, BLACK);
      display.fillRect(0, 39, 160, 17, RED);
      display.setCursor(57, 40);
      display.setTextSize(2);
      display.print("View");
      display.setCursor(8,60);
      display.print("Temperatures");
      display.setCursor(61,80);
      display.print("PWN");
      showed = 1;
    break;

    case 2:
      display.fillRect(0, 0, 160, 124, BLACK);
      display.setCursor(57, 40);
      display.setTextSize(2);
      display.print("View");
      display.fillRect(0, 59, 160, 17, RED);
      display.setCursor(8,60);
      display.print("Temperatures");
      display.setCursor(61,80);
      display.print("PWN");
      showed = 1;
    break;

    case 3:
      display.fillRect(0, 0, 160, 124, BLACK);
      display.setCursor(57, 40);
      display.setTextSize(2);
      display.print("View");
      display.setCursor(8,60);
      display.print("Temperatures");
      display.fillRect(0, 79, 160, 17, RED);
      display.setCursor(61,80);
      display.print("PWN");
      showed = 1;
    break;
  }
  }
}

void viewMenu()
{
  if (showed == 0 || changed == 1){
  switch(choice)
  {
    case 0:
      display.fillRect(0, 0, 160, 124, BLACK);
      display.setCursor(52, 45);
      display.setTextSize(2);
      display.print("Chart");
      display.setCursor(40,65);
      display.print("Digital");
      showed = 1;
    break;

    case 1:
      display.fillRect(0, 0, 160, 124, BLACK);
      display.fillRect(0, 44, 160, 17, RED);
      display.setCursor(52, 45);
      display.setTextSize(2);
      display.print("Chart");
      display.setCursor(40,65);
      display.print("Digital");
      showed = 1;
    break;

    case 2:
      display.fillRect(0, 0, 160, 124, BLACK);
      display.setCursor(52, 45);
      display.setTextSize(2);
      display.print("Chart");
      display.fillRect(0, 64, 160, 17, RED);
      display.setCursor(40,65);
      display.print("Digital");
      showed = 1;
    break;
  }
  }
 
}
void temperaturesMenu()
{
  if (showed == 0 || changed == 1){
  switch(choice)
  {
    case 0:
      display.fillRect(0, 0, 160, 124, BLACK);
      display.setCursor(43, 47);
      display.setTextSize(2);
      display.print("Preheat");
      display.setCursor(48,67);
      display.print("Reflow");
      showed = 1;
     
    break;

    case 1:
      display.fillRect(0, 0, 160, 124, BLACK);
      display.fillRect(0, 46, 160, 17, RED);
      display.setCursor(43, 47);
      display.setTextSize(2);
      display.print("Preheat");
      display.setCursor(48,67);
      display.print("Reflow");
      showed = 1;
    break;

    case 2:
      display.fillRect(0, 0, 160, 124, BLACK);
      display.setCursor(43, 47);
      display.setTextSize(2);
      display.print("Preheat");
      display.fillRect(0, 66, 160, 17, RED);
      display.setCursor(48,67);
      display.print("Reflow");
      showed = 1;
    break;
  }
  }
}

void pwnMenu()
{
  if (showed == 0 || changed == 1){
  switch(choice)
  {
    case 0:
      display.fillRect(0, 0, 160, 124, BLACK);
      display.setCursor(43, 47);
      display.setTextSize(2);
      display.print("Preheat");
      display.setCursor(48,67);
      display.print("Reflow");
      showed = 1;
     
    break;

    case 1:
      display.fillRect(0, 0, 160, 124, BLACK);
      display.fillRect(0, 46, 160, 17, RED);
      display.setCursor(43, 47);
      display.setTextSize(2);
      display.print("Preheat");
      display.setCursor(48,67);
      display.print("Reflow");
      showed = 1;
    break;

    case 2:
      display.fillRect(0, 0, 160, 124, BLACK);
      display.setCursor(43, 47);
      display.setTextSize(2);
      display.print("Preheat");
      display.fillRect(0, 66, 160, 17, RED);
      display.setCursor(48,67);
      display.print("Reflow");
      showed = 1;
    break;
  }
  }
}

void preheatTempControl()
{
  if (showed == 0 || changed == 1){
    display.fillRect(0, 0, 160, 124, BLACK);
    display.setCursor(63, 58);
    display.setTextSize(2);
    display.print(preheatTemp); 
    showed = 1;    
  }
}

void reflowTempControl()
{
  if (showed == 0 || changed == 1){
    display.fillRect(0, 0, 160, 124, BLACK);
    display.setCursor(63, 58);
    display.setTextSize(2);
    display.print(reflowTemp); 
    showed = 1;
  }
}

void preheatPWNControl()
  { 
    if (showed == 0 || changed == 1)
    {
    display.fillRect(0, 0, 160, 124, BLACK);
    display.setCursor(63, 58);
    display.setTextSize(2);
    display.print(interval); 
    showed = 1; 
  }
}

void reflowPWNControl()
{
  if (showed == 0 || changed == 1){
    display.fillRect(0, 0, 160, 124, BLACK);
    display.setCursor(63, 58);
    display.setTextSize(2);
    display.print(interval2); 
    showed = 1;
  }
}

void reflowSoldering()
{
  currentMilis = millis();

  switch(stage)
  {
    case 0:
      Serial.println(temp);
      started = true;
      if (temp < preheatTemp - 30)
      {
        analogWrite(A0,255);
      }
      else if (temp >= preheatTemp - 30)
      {
        analogWrite(A0,0);
      }
      if (temp >= preheatTemp)
      {
        stage = 1;
        processTime = 0;        
      }
    break;
    
    case 1:
     
      if (currentMilis - lastMilis >= interval and cycle == 0) 
      {
        cycle = 1;
        lastMilis = currentMilis;
        analogWrite(A0, 255);
        //Serial.println(1);
      }

      if (currentMilis - lastMilis >= interval and cycle == 1) 
      {
        cycle = 0;
        lastMilis = currentMilis;
        analogWrite(A0, 0);
        // Serial.println(0);   
      }

      if (currentMilis - lastMilis2 >= oneSecond)
      {
        processTime += 1;
        lastMilis2 = currentMilis;
        Serial.print("Process Time Stage 1: ");
        Serial.println(processTime);
      }

      if(processTime >= 60)
      {
        stage = 2;
        processTime = 0;
      }
 

    break;

    case 2:
     
      if (currentMilis - lastMilis >= interval2 and cycle == 0) 
        {
          cycle = 1;
          lastMilis = currentMilis;
          analogWrite(A0, 255);
          //Serial.println(1);
        }

      if (currentMilis - lastMilis >= interval2 and cycle == 1) 
        {
          cycle = 0;
          lastMilis = currentMilis;
          analogWrite(A0, 0);
          // Serial.println(0);        
        }

      if (currentMilis - lastMilis2 >= oneSecond)
        {
          processTime += 1;
          lastMilis2 = currentMilis;
          Serial.print("Process Time Stage 2: ");
          Serial.println(processTime);
        }

      if (processTime >=45)
        {
          stage = 3;
          processTime = 0;
        }
    break; 

    case 3:
      Serial.println("Im in stage 3");
      analogWrite(A0, 0);

      if(temp <= 45)
      {

        userPick = 0;
        display.fillRect(0, 0, 124, 160, BLACK);
        
        

        
      }
    break;
  }
}

void measureAndDraw()
{
  uint16_t rtd = thermo.readRTD();
  currentMilis1 = millis();
  display.setTextSize(1);

   if (showed == 0 || changed == 1){
    display.fillRect(0, 0, 160, 160, BLACK);
    showed = 1;
  }


  if (currentMilis1 - lastMilis1 >= oneSecond) 
    {
      switch(viewType)
        {
          case 1:
            showTemperature();
          break;
        
          case 2:
            if(maxX >= time)
              {

                gridChart();
                drawChart();
              }
            else 
              {
                display.fillRect(0, 0, 160, 128, BLACK);
                time = 0;
                prevTime = 0;
                gridChart();
              }
          break;
        }
        
        // Check and print any faults
        ptFaults();
        lastMilis1 = currentMilis1;
        time += 1;
    }

}

void analogButton()
{
  if(digitalRead(8) < 1 && changed == 0)
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
  if(choice > control)
  {
    choice = 1;
    num = 1;
    count = 1;
  }

  if(choice < 1)
  {
    choice = control;
    num = control;
    count = control;
  }
}

void changeScreen(int screen1, int screen2, int screen3, int changeViewType, bool changeToAnalogParam, int parameter1, int parameter2)
{
  if(press == 1){
    switch(choice)
      {
        case 1:
          userPick = screen1;
          press = 0; 
          changed = 1; 
          if (changeViewType == 1)
          viewType = 2;
          if(changeToAnalogParam)
          { 
          count = parameter1;
          num = parameter1;       
          }    
        break;
        case 2:
          userPick = screen2;
          press = 0;
          changed = 1; 
          if (changeViewType == 1)
          viewType = 1; 
          if(changeToAnalogParam)
          {
          count = parameter2;
          num = parameter2;
          }
        break;
        case 3:
          userPick = screen3;
          press = 0;
          changed = 1;
        break;
        default:
          userPick = screen1;        
        break;
      }
  }
}


void menu()
{
  analogButton();
 
  switch(userPick)
  {
    case 0:
    started = false;
    time = 0;
    prevTime = 0;
    temp = 0;
    dispprevTemp = 0;
    dispTemp = 0;
    analogButtonControl(2);
    baseMenu();
    changeScreen(1,2,0,0,false,0,0);
    break;
    
    case 1:
    if(!started)
    {
      stage = 0;
    }
    measureAndDraw();
    reflowSoldering();
    analogButtonControl(3);
    changeScreen(0,0,0,0,false,0,0);
    break;

    case 2:
    analogButtonControl(3);
    optionsMenu();
    changeScreen(3,4,5,0,false,0,0); 
    break;

    case 3:
    analogButtonControl(2);
    viewMenu();
    changeScreen(0,0,0,1,false,0,0);
    break;

    case 4:
    analogButtonControl(2);
    temperaturesMenu();
    changeScreen(6,7,0,0,true,preheatTemp,reflowTemp); 
    break;

    case 5:
    analogButtonControl(2);
    pwnMenu();
    changeScreen(8,9,0,0,true,interval,interval2); 
    break;

    case 6:
    preheatTemp = num; 
    preheatTempControl();
    changeScreen(0,0,0,0,false,0,0); 
    break;

    case 7:
    reflowTemp = num; 
    reflowTempControl();
    changeScreen(0,0,0,0,false,0,0);   
    break;

    case 8:
    interval = num; 
    preheatPWNControl();
    changeScreen(0,0,0,0,false,0,0);  
    break;

    case 9:
    interval2 = num; 
    reflowPWNControl();
    changeScreen(0,0,0,0,false,0,0); 
    break;
        
        
  }

}

void setup() 
{
  Serial.begin(9600);
  thermo.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
  display.begin();
  display.setRotation(1);

  pinMode(PinA,INPUT); 
  pinMode(PinB,INPUT); 
  pinMode(8, INPUT_PULLUP);

  attachInterrupt(0, blinkA, LOW);  
  attachInterrupt(1, blinkB, LOW);  

}


void loop() 
{
  menu();
}

