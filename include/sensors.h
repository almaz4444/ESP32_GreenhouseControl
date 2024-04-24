#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <Arduino_JSON.h>

#include "ntp.h"

#define DHTPIN 13  
#define DHTTYPE DHT22

DHT_Unified dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

JSONVar readings;

float readTemperature_DHT() {
  sensors_event_t dht_event;
  dht.temperature().getEvent(&dht_event);

  return dht_event.temperature;
}

float readHumidity_DHT() {
  sensors_event_t event;
  dht.humidity().getEvent(&event);

  return event.relative_humidity;
}

float readPressure_BMP() {
  return bmp.readPressure() / 100.0F;
}

void updateSensorsReadings() {
  readings["temperature"] = String(readTemperature_DHT());
  readings["humidity"] =  String(readHumidity_DHT());
  
  if (bmp.readRawPressure() == 0) {
    readings["pressure"] = "NaN";
  } else {
    readings["pressure"] = String(readPressure_BMP());
  }
}

void initSensors() {
  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1);
  }

  dht.begin();
}