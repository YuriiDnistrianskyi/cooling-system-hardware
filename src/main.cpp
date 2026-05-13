#include <Arduino.h>

#include "../include/initPins.hpp"
#include "../include/initWiFi.hpp"
#include "../include/serverConnect.hpp"
#include "../include/webSocketCommandEnum.hpp"
#include "../include/config.hpp"

WebSocketCommandEnum webSocketCommand = COMMAND_NONE;
uint8_t fanSpeed = 0;
uint32_t lastFanUpdateTime = 0;

void setup() {
  initPins();
  initWiFi();
  connectToServer();
}

void loop() {
  loopWebSocket();
  uint32_t currentFanUpdateTime = millis();
  if(currentFanUpdateTime - lastFanUpdateTime >= FAN_UPDATE_INTERVAL) 
  {
    lastFanUpdateTime = currentFanUpdateTime;
    if(webSocketCommand != COMMAND_NONE) 
    {
      uint8_t newFanSpeed = fanSpeed;
      if(webSocketCommand == COMMAND_FAN_SPEED_UP) 
      {
        newFanSpeed = min(fanSpeed + 25, 255);
      }
      else if(webSocketCommand == COMMAND_FAN_SPEED_DOWN) 
      {
        newFanSpeed = max(fanSpeed - 25, 0);
      }
      else {
        Serial.println("Unknown WebSocketCommand: " + String((int)webSocketCommand)); 
      }

      webSocketCommand = COMMAND_NONE;
      fanSpeed = newFanSpeed;
      analogWrite(FAN_PIN, fanSpeed);
      sendWebSocketMessage(fanSpeed);
    }
  }
}
