#include "../include/initPins.hpp"
#include "../include/initWiFi.hpp"
#include "../include/serverConnect.hpp"
#include "../include/webSocketCommandEnum.hpp"

WebSocketCommandEnum webSocketCommand = COMMAND_NONE;

void setup() {
  initPins();
  initWiFi();
  connectToServer();
}

void loop() {
  
}
