#include <WebSocketsClient.h>
#include <ArduinoJson.h>

#include "../include/serverConnect.hpp"

#include "../include/config.hpp"
#include "../include/webSocketCommandEnum.hpp"

extern WebSocketCommandEnum webSocketCommand;
extern uint8_t fanSpeed;
WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.println("WebSocket Disconnected");
            break;
        case WStype_CONNECTED:
            Serial.println("WebSocket Connected");
            break;
        case WStype_TEXT:
            Serial.printf("WebSocket Message: %s\n", payload);
            StaticJsonDocument<200> doc;
            DeserializationError error = deserializeJson(doc, payload, length);
            if (error) 
            {
                Serial.print("deserializeJson() failed: ");
                Serial.println(error.c_str());
                return;
            }

            const char* command = doc["command"];
            if (strcmp(command, "up") == 0) 
            {
                webSocketCommand = COMMAND_FAN_SPEED_UP;
            }
            else if(strcmp(command, "down") == 0)
            {
                webSocketCommand = COMMAND_FAN_SPEED_DOWN;
            }
            break;
    }
}

void connectToServer() {
    webSocket.begin(SERVER_URL, SERVER_PORT, SERVER_PATH);
    webSocket.onEvent(webSocketEvent);
    webSocket.setReconnectInterval(5000);
}

void loopWebSocket() {
    webSocket.loop();
}

void sendWebSocketMessage(uint8_t speed) {
    StaticJsonDocument<200> doc;
    doc["value"] = (speed * 100) / 255;
    Serial.println("Send speed: " + String(speed));

    String payload;
    serializeJson(doc, payload);
    webSocket.sendTXT(payload);
}

