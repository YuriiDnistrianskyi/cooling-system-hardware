#include <ESP8266WiFi.h>

#include "../include/initPins.hpp"
#include "../include/config.hpp"

void initWifFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi (" + String(WIFI_SSID) + ")");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}
