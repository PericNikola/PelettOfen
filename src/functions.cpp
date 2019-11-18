#include <Arduino.h>
#include "esp_adc_cal.h"
#include "functions.hpp"
#include "globals.hpp"
#include <Adafruit_MAX31856.h>
#include <EEPROM.h>
#include <string.h>

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(CS, MOSI, MISO, CLK);
stsOfen_t stsOfen; //


void StartInit(){
  // put your setup code here, to run once:
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  //Configure ADC
  adc1_config_width(ADC_WIDTH_12Bit);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_11db);
  
  //Configure Thermosensor
  maxthermo.begin();
  maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);
  maxthermo.setNoiseFilter(MAX31856_NOISE_FILTER_50HZ);
  //EEPROM.write(0, 123);
  //EEPROM.commit();
}

void readParameter() {

  ;
}
void readInputs(){
  ;
}
void readTemperatures() {
  *ptrIstTempKessel=kessel_temp();
  *ptrIstAbgasTemperatur=abgas_temp();
}
void fireControl(){
  
  switch (stsOfen)
  {
  case STS_OFEN_OFF:
    digitalWrite(LED_BUILTIN, HIGH);
    stsOfen=STS_OFEN_RELAY_ON;
    ;
    break;
  case STS_OFEN_RELAY_ON:
    delay(1000);
    stsOfen=STS_OFEN_VORLUEFTEN_ON;
    ;
    break;
  
  case STS_OFEN_VORLUEFTEN_ON:
    ;
    break;
  case STS_OFEN_LOAD_WOOD_1:
    ;
    break;
  case STS_OFEN_LOAD_WOOD_2:
    ;
    break;
  case STS_OFEN_LOAD_WOOD_3:
    ;
    break;
  case STS_OFEN_FIRE_ON:
    ;
    break;
  case STS_OFEN_NORMAL_BETRIEB:
    ;
    break;
  case STS_OFEN_TEMP_ERREICHT:
    ;
    break;
  case STS_OFEN_STUF1_AUSLAUF:
    ;
    break;
  case STS_OFEN_FIRE_STOP:
    ;
    break;
  case STS_OFEN_KUEHLEN:
    ;
    break;
  case STS_OFEN_ERROR:
    ;
    break;
  
  default:
    break;
  }
  Serial.println(stsOfen);
  
}
void writeOutputs(){
  ;
}


void outputSerial(){
  Serial.println("");
  Serial.print("NTC Temperautur :");
  Serial.println(*ptrIstTempKessel);
  Serial.print("Thermocouple Temperautur :");
  Serial.println(*ptrIstAbgasTemperatur);
  Serial.print("Differenz NTC <-> Thermocouple: ");
  Serial.println(*ptrIstTempKessel - *ptrIstAbgasTemperatur);

  Serial.println ("Parameter aus EEPROM 1: ");
  //Serial.print(EEPROM.read(0));
}
//
void compare(const struct s *left, const struct s *right) { 
  //if (0 == memcmp(left, right, sizeof(struct s))) {
    /* ... */
  //};
  ;
}

float kessel_temp(){
  const uint32_t  V_REF= 3300.0;  // ADC reference voltage
  const float THERMISTORNOMINAL =10000.0;
  const float TEMPERATURENOMINAL= 25.0;
  const float BCOEFFICIENT =3950.0;
  const int NUMSAMPLES =10;
    
  float average, kelvin, Resistance, celsius;
  int samples[NUMSAMPLES];
  int i;
      
    // put your main code here, to run repeatedly:
    // Characterize ADC
    // Calculate ADC characteristics i.e. gain and offset factors
        esp_adc_cal_characteristics_t characteristics;
        esp_adc_cal_get_characteristics(V_REF, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, &characteristics);
    
    // Read ADC and obtain result in mV
    // take N samples in a row, with a slight delay
      for (i=0; i< NUMSAMPLES; i++){
        //if ( millis() - lastmillis >= AnalogReadIntervall ){
          samples[i] = adc1_to_voltage(ADC1_CHANNEL_0, &characteristics); // Read Analog Voltage value 
          
          //samples[i] = (ReadVoltage(36),3); // Read Analog Voltage value 
          //lastmillis =millis();
        //}
      }

  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
    average += samples[i]; // Anzahl Messwerte zusammenzählen
    }
    average /= NUMSAMPLES;    // Die Summer durch die Anzahl dividieren, dadurch glättung 
     
    Resistance = (3300.0 / average)-1;
    Resistance = 10000.00 / Resistance;
    
    kelvin = Resistance/THERMISTORNOMINAL; // R/Ro
    
    kelvin = logf(kelvin); // ln(R/Ro)
      
    kelvin = (1.0/BCOEFFICIENT) * kelvin; // 1/B * ln(R/Ro)
    
    kelvin = (1.0/(TEMPERATURENOMINAL+273.15)) + kelvin; // 1/To + 1/B * ln(R/Ro)
    kelvin = 1.0/kelvin; // 1/( 1/To + 1/B * ln(R/Ro) )​
    
    // Convert Kelvin to Celsius
    celsius = kelvin - 273.15;

    return celsius;

    
}
float abgas_temp(){
  float Temp;

  Temp=maxthermo.readThermocoupleTemperature();

  return Temp;
}





void berechneMasseZeiger(Kessel *ptr){
  ptr ->istTemp =1200;
  ptr ->sollTemp=12;
}




