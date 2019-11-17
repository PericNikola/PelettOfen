#ifndef globals_h
#define globals_h

#define FALSE 0
#define TRUE 1

// Inputs Pins für Thermocouple
#define CS 5
#define MOSI 19
#define MISO 23
#define CLK 18

// ZeroCross Detect Pin
#define ZeroCross 36
#define TempKesselGPIO 39
#define FaultMAX31856 34

#define EEPROM_SIZE 1

#pragma pack(push, 1)
struct MachineParameter {
  int pr01_MaxZeitEinProzess;         // Maximale Zeit die ein Startvorgang haben darf
  int pr02_StabilieirungZeit_FIRE_ON; // Zeit solange die Flamme beim Status FIRE ON stabilisiert wird
  int pr03_AbstandszeitReinigung;     // Reinunung Intervall des Pelett Brennbehälters
  int pr04_Schnecke_ein_LOAD_WOOD;    // Schneckeneinschaltzeit bei Start Vorgang
  int pr05_Schnecke_ein_FIRE_ON;      // Schneckenlaufzeit Stufe Fire ON
  int pr06_Schnecke_ein_STUFE1;
  int pr07_Schnecke_ein_STUFE2;
  int pr08_Schnecke_ein_STUFE3;
  int pr09_Schnecke_ein_STUFE4;
  int pr10_Schnecke_ein_STUFE5;
  int pr11;
  int pr12;
  int pr13;
  int pr14;
  int pr15;
  int pr16_Vent_Drehzahl_LOAD_WOOD;   // Ventilatordrehzahl/Stufe beim Startvorgang
  int pr17_Vent_Drehzahl_FIRE_ON;
  int pr18_Vent_Drehzahl_STUFE1;
  int pr19_Vent_Drehzahl_STUFE2;
  int pr20_Vent_Drehzahl_STUFE3;
  int pr21_Vent_Drehzahl_STUFE4;
  int pr22_Vent_Drehzahl_STUFE5;
};
#pragma pack(pop)

typedef enum STS_OFEN{
  STS_OFEN_OFF,
  STS_OFEN_RELAY_ON,
  STS_OFEN_VORLUEFTEN_ON,
  STS_OFEN_VENT_ON,
  STS_OFEN_LOAD_WOOD,
  STS_OFEN_FIRE_ON,
  STS_OFEN_NORMAL_BETRIEB,
  STS_OFEN_TEMP_ERREICHT,
  STS_OFEN_FIRE_STOP,
  STS_OFEN_KUEHLEN,
  STS_OFEN_ERROR } stsOfen_t;

typedef enum PARAMETER{
  PARA_KESSEL_T_MIN,
  PARA_KESSEL_T_MAX
  

};

// Temperatur Variables
float istTempKessel;
float *ptrIstTempKessel = &istTempKessel; // Kesseltemperatur



float istAbgasTemperatur;
float *ptrIstAbgasTemperatur = &istAbgasTemperatur; // Abgastemperatur

#define INTERVAL_ABGASTEMP_READ 1000

//

struct Kessel
{
  float istTemp = 0;
  float sollTemp = 0;
};

struct Abgas
{
  float istTemp = 0;
  float sollTemp = 0;
};

#endif
