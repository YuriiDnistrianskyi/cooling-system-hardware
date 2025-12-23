#include <Arduino.h>

#include "../include/initPins.hpp"

#include "../include/config.hpp"

void initPins() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);
}
