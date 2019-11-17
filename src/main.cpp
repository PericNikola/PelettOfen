#include <Arduino.h>
#include "functions.hpp"
#include <string.h>

unsigned long lastmillis = 0;
int auswahl=0;
#define INTERVAL_MESSAGE1 1000



void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  StartInit();
}

  

void loop() {

  
  // put your main code here, to run repeatedly:
  if(millis() > lastmillis + INTERVAL_MESSAGE1){


    readTemperatures();
    outputSerial();
    fireControl();
    
    

    lastmillis = millis();

    
    /*

    switch(auswahl){
        case 0:
            Serial.print("Schritt 0");
            auswahl=1;

            break;

        case 1:

            Serial.print("Schritt 1");
            auswahl=2;

            break;

        case 2:

            Serial.print("Schritt 2");
            auswahl=3;
            break;

        case 3:

            Serial.print("Schritt 3");
            auswahl=0;

            break;

        default:

            Serial.print("Wollen Sie wirklich behaupten, dass Ihnen nichts davon zusagt?");

    }
    */
  }
}