#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

// Wi‑Fi i serwer
const char* ssid     = "UPC1511627_24G";
const char* password = "y6jntjfejdcR";
const char* server   = "http://192.168.0.10:5000/now";

// Utwór i czasy
String title  = "—";
String artist = "—";
long progress_ms = 0;
long duration_ms = 1;

// Rysowanie UI
void drawUI(){
  tft.fillScreen(TFT_BLACK);

  // nagłówek
  tft.setTextSize(3);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(10, 10);
  tft.print("Now Playing");

  // duży tytuł utworu
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(10, 60);
  tft.print(title);

  // artysta
  tft.setTextSize(2);
  tft.setTextColor(TFT_LIGHTGREY);
  tft.setCursor(10, 100);
  tft.print(artist);

  // pasek postępu
  int barX = 10, barY = 150, barW = 300, barH = 8;
  tft.fillRect(barX, barY, barW, barH, TFT_DARKGREY);
  int filled = (int)((float)progress_ms / duration_ms * barW);
  if(filled > 0) tft.fillRect(barX, barY, filled, barH, TFT_GREEN);

  // czas miniony / całkowity
  int pSec = progress_ms / 1000;
  int dSec = duration_ms / 1000;
  int pMin = pSec / 60, pS = pSec % 60;
  int dMin = dSec / 60, dS = dSec % 60;
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(barX, barY + barH + 12);
  tft.printf("%02d:%02d  /  %02d:%02d", pMin, pS, dMin, dS);
}

void setup(){
  Serial.begin(115200);

  // WiFi
  WiFi.begin(ssid, password);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(10,80);
  tft.print("Łączenie WiFi...");

  while(WiFi.status() != WL_CONNECTED) delay(500);

  tft.fillScreen(TFT_BLACK);
  drawUI();
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(server);
    int code = http.GET();
    if(code == 200){
      String payload = http.getString();

      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);

      title  = doc["track"].as<String>();
      artist = doc["artist"].as<String>();
      progress_ms = doc["progress_ms"].as<long>();
      duration_ms = doc["duration_ms"].as<long>();

      drawUI();
    }
    http.end();
  }
  delay(1000);
}
