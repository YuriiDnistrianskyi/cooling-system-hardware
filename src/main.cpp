#include <Arduino.h>

#include "../include/initPins.hpp"
#include "../include/initWiFi.hpp"
#include "../include/serverConnect.hpp"
#include "../include/webSocketCommandEnum.hpp"
#include "../include/config.hpp"

WebSocketCommandEnum webSocketCommand = COMMAND_NONE;
uint16_t lastFanUpdateTime = 0;

void setup() {
  initPins();
  initWiFi();
  connectToServer();
}

void loop() {
  uint16_t currentFanUpdateTime = millis();
  if(currentFanUpdateTime - lastFanUpdateTime >= FAN_UPDATE_INTERVAL) 
  {
    lastFanUpdateTime = currentFanUpdateTime;
    if(webSocketCommand != COMMAND_NONE) 
    {
      uint8_t currentFanSpeed = analogRead(FAN_PIN);
      uint8_t newFanSpeed = currentFanSpeed;
      if(webSocketCommand == COMMAND_FAN_SPEED_UP) 
      {
        newFanSpeed = min(currentFanSpeed + 25, 255);
      }
      else if(webSocketCommand == COMMAND_FAN_SPEED_DOWN) 
      {
        newFanSpeed = max(currentFanSpeed - 25, 0);
      }
      else {
        Serial.println("Unknown WebSocketCommand: " + String((int)webSocketCommand)); 
      }

      webSocketCommand = COMMAND_NONE;
      analogWrite(FAN_PIN, newFanSpeed);
      sendWebSocketMessage();
    }
  }
}
