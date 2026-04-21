//------------------ LIBRARIES ------------------
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

//------------------ DEFINITIONS ------------------
#define DHTPIN 2          // DHT11 signal pin
#define DHTTYPE DHT11
#define RAIN_PIN A0       // Rain sensor analog pin

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD I2C Address 0x27

//------------------ SETUP ------------------
void setup() {
  Serial.begin(9600);
  
  dht.begin();
  bmp.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Weather Monitor");
  lcd.setCursor(0,1);
  lcd.print("System Loading..");
  delay(2000);
  lcd.clear();
}

//------------------ LOOP ------------------
void loop() {

  // ----- DHT11 -----
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  // ----- BMP180 -----
  float pressure = bmp.readPressure() / 100.0; // hPa
  float altitude = bmp.readAltitude();

  // ----- Rain Sensor -----
  int rainValue = analogRead(RAIN_PIN);
  String rainStatus;

  if (rainValue < 300) rainStatus = "Raining";
  else if (rainValue < 700) rainStatus = "Drizzle";
  else rainStatus = "Clear";

  // ----- SHOW ON LCD -----
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print("C ");

  lcd.setCursor(8,0);
  lcd.print("H:");
  lcd.print(hum);
  lcd.print("%");

  lcd.setCursor(0,1);
  lcd.print("P:");
  lcd.print(pressure);
  lcd.print("hPa");

  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Alt:");
  lcd.print(altitude);
  lcd.print("m");

  lcd.setCursor(0,1);
  lcd.print("Rain:");
  lcd.print(rainStatus);

  delay(2000);
  lcd.clear();
}
