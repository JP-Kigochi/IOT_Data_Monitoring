// Library dependencies
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>

// DHT sensor initialization
#define DHTPIN 0
#define DHTTYPE 11

// Initialization of firebase host
#define FIREBASE_HOST  "iot2024-2708d-default-rtdb.firebaseio.com"

// initialization of wifi ssid and password
#define WIFI_SSID "" /* input WIFI SSID */
#define WIFI_PASSWORD "" /* input your password */

// Object instance for dht sensor, lcd_i2c and the firebase database
DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Firebase firebase (FIREBASE_HOST);

void setup() {
  Serial.begin(9600);

  // Begin sensor measurement
  dht.begin();

  // Connect to wifi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);

  while(WiFi.status() != WL_CONNECTED){
    delay(200);
    Serial.print(".");
  }

  Serial.println("WiFi Connected");

  // LCD Setup
  lcd.init();
  lcd.backlight();
  lcd.clear();
}


void loop(){
  delay(1000);

  // Reading of temperature and humidity from the sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Error checking
  if (isnan(h)||isnan(t)){
    Serial.println("Failed to read from DHT!!!");
    firebase.setString("ERROR","Failed to read from sensor!!!");
    return;
  }

  // Showcase the readings
  Serial.println("___________________________");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%t");
  firebase.setFloat("Humidity ",h);


  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(char(186));
  Serial.println("C ");
  Serial.println("___________________________");
  Serial.println(" ");
  firebase.setFloat("Temperature ", t);

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
