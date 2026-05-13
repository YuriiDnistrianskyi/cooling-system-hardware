#include <Arduino.h>

#include "../include/initPins.hpp"

#include "../include/config.hpp"

extern uint8_t fanSpeed;

void initPins() {
    // pinMode(RELAY_PIN, OUTPUT);
    // digitalWrite(RELAY_PIN, HIGH);
    Serial.begin(115200);
    analogWriteRange(255);
    pinMode(FAN_PIN, OUTPUT);
    analogWrite(FAN_PIN, fanSpeed);
}
