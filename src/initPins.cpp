#include <Arduino.h>

#include "../include/initPins.hpp"

#include "../include/config.hpp"

void initPins() {
    // pinMode(RELAY_PIN, OUTPUT);
    // digitalWrite(RELAY_PIN, HIGH);

    analogWriteRange(255);
    pinMode(FAN_PIN, OUTPUT);
    analogWrite(FAN_PIN, 0);
}
