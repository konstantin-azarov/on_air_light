/* 
An ESP32 server that turns a GPIO on and off when a command is received
*/
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "Add your SSID here";
const char *password = "Add your password here";

int btnGPIO = 0;
int btnState = false;

AsyncWebServer server(80);

const int PIN_OUT = 23;

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(PIN_OUT, OUTPUT);
  digitalWrite(PIN_OUT, LOW);

  // We start by connecting to a WiFi network
  // To debug, please enable Core Debug Level to Verbose
  Serial.println();
  Serial.print("[WiFi] Connecting to ");
  Serial.println(ssid);

  WiFi.setHostname("onair");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected!");

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest* request) {
    digitalWrite(PIN_OUT, HIGH);
    request->send_P(200, "text/plain", "ok");
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest* request) {
    digitalWrite(PIN_OUT, LOW);
    request->send_P(200, "text/plain", "ok");
  });

  server.begin();
}

void loop() {
  delay(1000);
}
