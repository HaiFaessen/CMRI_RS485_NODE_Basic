/***********************************************************************
  Program      :  CMRI RS485 NODE Basic Sketch
  Author       :  H&HExpres, Hai faessen
  Description  :  Basic Sketch for using  the Arduino as a CMRI Node over RS485 Including a HeartBeat
  Version      :  1.1
  Date         :  3 January 2025
  CopyRight (c): H&HExpress 1996-2025

    The Files 
       included:  CMRI-RS485-Node-ESP32-Basi-Sketch-Example.ino

                  Definitions.h             Contains all Definitions and Variables needed for the sketch
                  HeartBeat.h               Contains the HeartBeat Definitions as is by Hai Faessen
                  HeartBeat.ino             Contains the HeartBeat Functions   as is by Hai Faessen
                  Node_RS485_Functions.h    Contains the Definitions and Variables Needed for your own CMRI Node
                  Node_RS485_Functions.ino  Contains the Function Needed for your own CMRI Node


  Change History:
      1.1     :  Start of Basic CMRI Node Sketch used RS485

      
      
*/
// Setting App Version
String  CMRINodeName="<CMRI-Node-<HB-RS485-Basic-Sketch->-<VERSION_";
String  CMRINodeVersion="V1.1";
#define CMRINodeNumber 1
#define DE_PIN 2

// Basic import of Header Files
#include <Auto485.h>
#include <CMRI.h>
//#include <WiFi.h>
#include <Wire.h>

//HeartBeat Settings
#include "Definitions.h"                   // Basic Definitions as Timers
#include "HeartBeat.h"                     // HeartBeat Definitions

// Adding Header File for the Functions
#include "Node_Serial_Functions.h"         // Holds the Libraries to include and Global Variables

// Setting up the CMRI Node
Auto485 bus(DE_PIN); 
CMRI cmri(CMRINodeNumber, 64, 64, bus);         // node number, number of inputs, number of outputs




void setup() {
  Serial.begin(115200); //Just for debug console feedback, not CMRI connection
  delay(1000);
  Serial.print(CMRINodeName);              // Prints Function of Node and App Version
  Serial.print(CMRINodeVersion);           // Node App Version
  Serial.print(F("Node Number: "));
  Serial.println(CMRINodeNumber);
  Serial.println(F(">"));
  Serial.println("");
  delay(1000);
  
  // Setup Initial Settings
  HeartBeat_setup();           // HeartBeat Setup
  InitializingPinsToBeUsed();  // Located in the Node_Serial_Functions.ino
}

void loop() {

  HeartBeat();       // LED will blink every second as soon when the Connection to JMRI is established. If it disconnects it stops.
  
  cmri.process();    // Running the CMRI Process
  
  SettingOutputs();  // Setting Outputs like Turnouts, Lights etc //Located in the Node_Serial_Functions.ino
  ReadingSensors();  // Reading Sensors so they can be processed  //Located in the Node_Serial_Functions.ino
 
}
