#include <LiquidCrystal.h>          //Lib for the LCD screen
#include "DHT.h"                    //Lib for the Temperature sensor (DHT11)
#include "MQ135.h"                  //Lib for the Air Quality sensor (MQ135)            
#define DHTPIN 6
#define DHTTYPE DHT11

const int ANALOGPIN = 0;                                      //PIN MQ135 sensor
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;   //PIN LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht(DHTPIN, DHTTYPE);
MQ135 gasSensor = MQ135(ANALOGPIN);

void setup()
{
  lcd.begin(16, 2);           //LCD initialization 
  dht.begin();                //DHT sensor initialization
}

void loop() 
{
  delay(2000);
  float ppm = gasSensor.getPPM ();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("Failed to read from DHT sensor!");
    return ;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.setCursor(0, 0);
  lcd.print("ArQ= ");
  lcd.print(ppm);
  lcd.print(" PPM");
  lcd.setCursor(0, 1);
  lcd.print("T=");
  lcd.setCursor(2, 1);
  lcd.print(t - 2);
  lcd.setCursor(6, 1);
  lcd.print("C");
  lcd.setCursor(9, 1);
  lcd.print("H=");
  lcd.setCursor(11, 1);
  lcd.print(h);
  lcd.setCursor(15, 1);
  lcd.print("%");
}
