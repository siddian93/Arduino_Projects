#include <math.h>
#include "LiquidCrystal.h"
#define RELAY 8   


LiquidCrystal lcd(6,7,5,4,3,2);
  float A = 1.009249522e-03, B = 2.378405444e-04, C = 2.019202697e-07;
  float T,logRt,Tf,Tc;
  float Thermistor(int Vo) {
  logRt = log(10000.0*((1024.0/Vo-1))); 
  T = (1.0 / (A + B*logRt + C*logRt*logRt*logRt));  // We get the temperature value in Kelvin from this Stein-Hart equation
  Tc = T - 273.15;                 // Convert Kelvin to Celcius
  Tf = (T * 1.8) + 32.0;           // Convert Kelvin to Fahrenheit
  return T;
}

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  pinMode(RELAY, OUTPUT); 
}

void loop() {
  
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.print(int(Thermistor(analogRead(0))));
  lcd.print("C ");
  delay(500);  // wait 0.5 seconds before sampling temperature again

  if (Tc > 28) digitalWrite(RELAY, HIGH),lcd.setCursor(0,1),lcd.print("Light status:ON "),delay(500);
  else if (Tc < 28) digitalWrite(RELAY, LOW),lcd.setCursor(0,1),lcd.print("Light status:OFF"),delay(500);   
         
}
