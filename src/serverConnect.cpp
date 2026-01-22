#include <WebSocketsClient.h>
#include <ArduinoJson.h>

#include "../include/serverConnect.hpp"

#include "../include/config.hpp"
#include "../include/webSocketCommandEnum.hpp"

extern WebSocketCommandEnum webSocketCommand;
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
            if (strcmp(command, "fan_speed_up") == 0) 
            {
                webSocketCommand = COMMAND_FAN_SPEED_UP;
            }
            else if(strcmp(command, "fan_speed_down") == 0)
            {
                webSocketCommand = COMMAND_FAN_SPEED_DOWN;
            }
            break;
    }
}

void connectToServer() {
    webSocket.begin(SERVER_URL, SERVER_PORT, SERVER_PATH);
    webSocket.onEvent(webSocketEvent);
    webSocket.setREconnectInterval(5000);
}

void loopWebSocket() {
    webSocket.loop();
}

void sendWebSocketMessage() {
    StaticJsonDocument<100> doc;
    doc["type"] = "fan_speed";
    doc["value"] = analogRead(FAN_PIN);

    String payload;
    serializeJson(doc, payload);
    webSocket.sendTXT(payload);
}

