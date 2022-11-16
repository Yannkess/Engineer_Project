import processing.serial.*;

Serial COMPort;  // Create object from Serial class

String[] lines = new String[0];

void setup() 
{
  frameRate(5);
  String portName = Serial.list()[1];
  COMPort = new Serial(this, portName, 9600);
  
}

void draw() 
{
  if (COMPort.available() > 0) {  // If data is available,
    String read = COMPort.readString();  // read and store it to string read
    print(read);
    lines = append(lines, read);// append new read to string lines
  } else {
    saveStrings("F:\\Programowanie\\Arduino\\Reflow Oven\\Dane\\wykres.txt", lines);//save string to file
  }
}
