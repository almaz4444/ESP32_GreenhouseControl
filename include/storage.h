#include <Arduino.h>
#include <SPIFFS.h>


#define SAVE_LINES_COUNT 50

const char* temperatureFilePath = "/temperature_datas.csv";
const char* humidityFilePath = "/humidity_datas.csv";
const char* pressureFilePath = "/pressure_datas.csv";
const char* tempFilePath = "/temp.csv";

const char* temperatureDataHead = "Date,Температура";
const char* humidityDataHead = "Date,Влажность";
const char* pressureDataHead = "Date,Давление";

void checkFile(const char* path, const char* head) {
  if (!SPIFFS.exists(path)) {
    File dataFile = SPIFFS.open(path, "w");
    dataFile.println(head);
    dataFile.close();
  }
}

void saveData(const char* path, const char* head, String time, String data) {
  File dataFile = SPIFFS.open(path, "r");
  int16_t lines_count = 0;

  while (dataFile.available()) {
    dataFile.readStringUntil('\n');
    lines_count++;
  }
  dataFile.close();

  dataFile = SPIFFS.open(path, "r");
  dataFile.readStringUntil('\n');

  File tempFile = SPIFFS.open(tempFilePath, "w");
  tempFile.println(head);
  
  int16_t string_index = 0;
  while (dataFile.available()) {
    String s = dataFile.readStringUntil('\n');
    s.trim();
    if (lines_count - string_index <= SAVE_LINES_COUNT && s) {
      tempFile.println(s);
    }
    string_index++;
  }

  String out = time + "," + data;
  tempFile.println(out);

  tempFile.close();
  dataFile.close();

  SPIFFS.remove(path);
  SPIFFS.rename(tempFilePath, path);
}

void checkFiles() {
  checkFile(temperatureFilePath, temperatureDataHead);
  checkFile(humidityFilePath, humidityDataHead);
  checkFile(pressureFilePath, pressureDataHead);
}

void saveSensorsDatas() {
  checkFiles();

  String time = getTime();
  saveData(temperatureFilePath, temperatureDataHead, time, readings["temperature"]);
  saveData(humidityFilePath, humidityDataHead, time, readings["humidity"]);
  saveData(pressureFilePath, pressureDataHead, time, readings["pressure"]);
}

String getSensorsDatas() {
  checkFiles();

  File dataFile = SPIFFS.open("/temperature_datas.csv", "r");

  String data = "";
  if (dataFile) {
    data = dataFile.readString();
  }

  dataFile.close();

  return data;
}

void initStorage() {
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
}