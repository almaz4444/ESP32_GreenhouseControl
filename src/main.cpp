#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "time.h"

#include "sensors.h"
#include "storage.h"


#define SENSORS_UPDATE_D_TIME 10 * 1000

const char* ssid = "Ufanet39";
const char* password = "89177919406";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

uint32_t updateSensorsTMR;

void initWiFI() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println(WiFi.localIP());
}

// void notficateClients(String sensorsReadings) {
//   ws.textAll(sensorsReadings);
// }

// void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
//   AwsFrameInfo *info = (AwsFrameInfo*)arg;
//   if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
//     data[len] = 0;
//     String message = (char*)data;
//     if (strcmp((char*)data, "getReadings") == 0) {
//       String sensorsReadings = getSensorsReadings();
//       Serial.print(sensorsReadings);
//       notficateClients(sensorsReadings);
//     }
//   }
// }

// void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
//   switch (type) {
//     case WS_EVT_CONNECT:
//       Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
//       break;
//     case WS_EVT_DISCONNECT:
//       Serial.printf("WebSocket client #%u disconnected\n", client->id());
//       break;
//     case WS_EVT_DATA:
//       handleWebSocketMessage(arg, data, len);
//       break;
//     case WS_EVT_PONG:
//     case WS_EVT_ERROR:
//       break;
//   }
// }

// void initWebSokets() {
//   ws.onEvent(onEvent);
//   server.addHandler(&ws);
// }

void setup(){
  Serial.begin(115200);
  
  initSensors();
  initStorage();

  initWiFI();
  // initWebSokets();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.on("/get_sensors_datas", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", getSensorsDatas().c_str());
  });

  server.serveStatic("/", SPIFFS, "/");

  initNTP();

  server.begin();

  updateSensorsTMR = millis();
}
 
void loop() {
  if (millis() - updateSensorsTMR >= SENSORS_UPDATE_D_TIME) {
    updateSensorsReadings();
    saveSensorsDatas();
    // notficateClients(sensorsReadings);

    updateSensorsTMR = millis();
  }

  ws.cleanupClients();
}