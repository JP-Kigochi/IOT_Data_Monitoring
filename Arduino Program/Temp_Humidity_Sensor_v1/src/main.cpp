#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

int DHTPIN = 2;
LiquidCrystal_I2C lcd(0x27,16, 2);

#define DHTTYPE 11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Temperature and Humidity test");

  lcd.init();
  lcd.backlight();
  lcd.clear();

  dht.begin();
}

void loop() {
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Error checking
  if (isnan(h) || isnan(t)){
    Serial.println("Error reading the sensor");
    return;
  }

  // display readings on serial monitor
  Serial.println("___________________________");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(char(186));
  Serial.println("C ");
  Serial.println("___________________________");
  Serial.println(" ");

  //LCD DISPLAY
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");

  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print(" %");
}
