#include <Arduino.h>
#include <configuration.h>
#include <Display.h>
#include <Encoder.h>
#include <Thermometer.h>
#include <Heater.h>
#include <Regulator.h>
#include <PID.h>
#include <Reader.h>

Display display = Display(10, 9, time, temp);
Encoder encoder = Encoder();
Thermometer thermometer = Thermometer(thermistorPin);
Heater heater;
Regulator regulator;
PID pid;
Reader reader;



void reflowSoldering()
{
  currentMilis = millis();
  heater.Start();
  reader.read();

  switch (stage)
  {
  case 0:
    
    started = true;
    heater.On();
    if (plateu == false)
    {
    stage = 2;
    }
    if (temp < preheatTemp)
    {
      pid.setPoint = preheatTemp;
      pid.start();
    }
    if (temp >= preheatTemp)
    {
      stage = 1;
      processTime = 0;
    }
    break;

  case 1:

    pid.start();

    if (currentMilis - lastMilis2 >= oneSecond)
    {
      processTime += 1;
      lastMilis2 = currentMilis;
      /*
      Serial.print("Process Time Stage 1: ");
      Serial.print(processTime);
      Serial.print("       temp = ");
      Serial.println(temp);
      */
    }

    if (processTime >= 60)
    {
      stage = 2;
      processTime = 0;
    }

    break;

  case 2:

    pid.setPoint = reflowTemp+10;

    if (temp1 < reflowTemp)
    {
      pid.start();
    }

    if (currentMilis - lastMilis2 >= oneSecond)
    {
      processTime += 1;
      lastMilis2 = currentMilis;
      temp1 = temp;
      /*
      Serial.print("Process Time Stage 2: ");
      Serial.print(processTime);
      Serial.print("       temp = ");
      Serial.println(temp);
      */
    }

    if (temp1 >= reflowTemp)
    {
      stage = 3;
      processTime = 0;
      temp1 = 0;
    }
    break;

  case 3:
    heater.Off();
    /*
    Serial.print("Im in stage 3");
    Serial.print("       temp = ");
    Serial.println(temp);
    analogWrite(A0, 0);
    */

    if (temp <= 100)
    {

      userPick = 0;
      display.changeScreen(0, 0, 0, 0, false,false,false, 0, 0);
    }
    break;
  }
}

void menu()
{
  encoder.analogButton();

  switch (userPick)
  {
  case 0:
    started = false;
    time = 0;
    display.prevTime = 0;
    temp = 0;
    display.dispprevTemp = 0;
    display.dispTemp = 0;
    stage = 3;
    heater.Off();
    analogWrite(A0, 0);
    encoder.analogButtonControl(3);
    display.baseMenu();
    display.changeScreen(1, 2, 8, 0, false,false,false, 0, 0);
    break;

  case 1:
    if (!started)
    {
      stage = 0;
    }
    thermometer.temperatureRead();
    temp = thermometer.currentTemp;
    display.temp = temp;
    display.Draw();
    reflowSoldering();
    encoder.analogButtonControl(3);
    display.changeScreen(0, 0, 0, 0, false,false,false, 0, 0);
    break;

  case 2:
    encoder.analogButtonControl(3);
    display.optionsMenu();
    display.changeScreen(3, 4, 7, 0, false,false,false, 0, 0);
    break;

  case 3:
    encoder.analogButtonControl(2);
    display.viewMenu();
    display.changeScreen(0, 0, 0, 1, false,false,false, 0, 0);
    break;

  case 4:
    encoder.analogButtonControl(2);
    display.temperaturesMenu();
    display.changeScreen(5, 6, 0, 0, true,false,false, preheatTemp, reflowTemp);
    break;

  case 5:
    preheatTemp = num;
    display.preheatTempControl();
    display.changeScreen(0, 0, 0, 0, false,false,false, 0, 0);
    break;

  case 6:
    reflowTemp = num;
    display.reflowTempControl();
    display.changeScreen(0, 0, 0, 0, false,false,false, 0, 0);
    break;

   case 7:
   encoder.analogButtonControl(2);
   display.modeMenu();
   display.changeScreen(0, 0, 0, 0, false,true,false, 0, 0);
   break;

   case 8:
   encoder.analogButtonControl(2);
   display.pasteMenu();
   display.changeScreen(0, 0, 0, 0, false,false,true, 0, 0);

  }
}

void setup()
{

  Serial.begin(9600);
  display.begin();
  display.setRotation(1);
  

  pinMode(PinA, INPUT);
  pinMode(PinB, INPUT);
  pinMode(8, INPUT_PULLUP);

  attachInterrupt(0, encoder.blinkA, LOW);
  attachInterrupt(1, encoder.blinkB, LOW);
}

void loop()
{
   menu();
}