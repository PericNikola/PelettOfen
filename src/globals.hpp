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
  int pr01_MaxZeitEinProzess;         // Maximale Zeit die ein Startvorgang haben darf, -> Störung No-Fire
  int pr02_StabilieirungZeit_FIRE_ON; // Zeit solange die Flamme beim Status FIRE ON stabilisiert wird 
  int pr03_AbstandszeitReinigung;     // Reinunung Intervall des Pelett Brennbehälters
  int pr04_Schnecke_ein_LOAD_WOOD;    // Schneckeneinschaltzeit bei Start Vorgang
  int pr05_Schnecke_ein_FIRE_ON;      // Schneckenlaufzeit Stufe Fire ON
  int pr06_Schnecke_ein_STUFE1;       // Schneckenlaufzeit Stufe 1
  int pr07_Schnecke_ein_STUFE2;       // Schneckenlaufzeit Stufe 2
  int pr08_Schnecke_ein_STUFE3;       // Schneckenlaufzeit Stufe 3
  int pr09_Schnecke_ein_STUFE4;       // Schneckenlaufzeit Stufe 4
  int pr10_Schnecke_ein_STUFE5;       // Schneckenlaufzeit Stufe 5
  int pr11_Alarm_Verzoegerung;        // Verzögerung bis der Alarm Schritt aktiviert wird
  int pr12_BrennBehaelterReinT;       // Brenntopf Reinigungsdauer
  int pr13_AbgasTemp_OfenIstEIN;      // Minimale Rauchtemperatur, um den Ofen als eingeschaltet zu betrachten
  int pr14_AbgasTemp_Max;             // Maximale Abgastemperatur, ist diese erreicht, arbeit der Ofen auf Stufe 1 oder OFF
  int pr15_PumpeEinTemperatur;        // Pumpe Ein Relais für Wasserbezug (Wird bei mir nicht gebraucht das eigene Steuerung)
  int pr16_Vent_Drehzahl_LOAD_WOOD;   // Ventilatordrehzahl/Stufe beim Startvorgang
  int pr17_Vent_Drehzahl_FIRE_ON;
  int pr18_Vent_Drehzahl_STUFE1;
  int pr19_Vent_Drehzahl_STUFE2;
  int pr20_Vent_Drehzahl_STUFE3;
  int pr21_Vent_Drehzahl_STUFE4;
  int pr22_Vent_Drehzahl_STUFE5;

  int pr45_Ladezeit;                  // 
  int pr46_WarteZeitNachVorladen;     // Wartezeit nach dem Vorladen
};
#pragma pack(pop)

typedef enum STS_OFEN{
  STS_OFEN_OFF,           // Ofen ausgeschaltet
  STS_OFEN_RELAY_ON,      // Hauptstromkreis EIN
  STS_OFEN_VORLUEFTEN_ON, // Pelettgefäss ausblasen
  STS_OFEN_LOAD_WOOD_1,   // Mehr Pelett Vorladen zum Start
  STS_OFEN_LOAD_WOOD_2,   // Wartezeit nach dem Vorladen (pr45)
  STS_OFEN_LOAD_WOOD_3,   // Standard Peletteinwerfen (pr04)
  STS_OFEN_FIRE_ON,       // Flammenstabiliserung wenn Feuer brennt 
  STS_OFEN_NORMAL_BETRIEB,// Normalbetrieb des Ofens je nach eingestellter Stufe 1- 5
  STS_OFEN_TEMP_ERREICHT, // Kesselwasser Temperatur erreicht
  STS_OFEN_STUF1_AUSLAUF, // Wenn Kesseltempertur erreicht dann noch mit Stufe 1 fahren
  STS_OFEN_FIRE_STOP,     // Kesseltemperatur steigt immer noch dann Feuer ausbrennen lassen
  STS_OFEN_KUEHLEN,       // Ofen Kühlen lassen bzw. Warten
  STS_OFEN_ERROR          // Ofen hat eine Störung
  } stsOfen_t;

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
