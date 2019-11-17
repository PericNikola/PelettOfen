#ifndef functions_h
#define functions_h

//#include "globals.hpp"

void StartInit(void); 

void readParameter();
void readTemperatures();
void fireControl();
void writeOutputs();

void outputSerial();




float kessel_temp();
float abgas_temp();

//double berechneMasseZeiger(Kessel *ptr);

void ReadInput(void);
void zero_crosss_int();

#endif