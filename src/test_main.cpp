#define UNIT_TEST
#include "main.h"

// Mock implementations for sensor functions
void humidity_temperature() {
    Serial.println("Mock humidity_temperature() called");
}

void sound() {
    Serial.println("Mock sound() called");
}

void lux() {
    Serial.println("Mock lux() called");
}

void movi() {
    Serial.println("Mock movi() called");
}
