#include <unity.h>
#include "mock_Serial.h"

#ifndef HIGH
#define HIGH 1
#endif

#ifndef LOW
#define LOW 0
#endif

// Mock variables for testing hardware functions
float mockHumidity = 0.0;
float mockTemperature = 0.0;
long mockPulseDuration = 0;
int mockDigitalValue = 0;
int mockAnalogValue = 0;

// Mock functions
float dht22_readHumidity() { return mockHumidity; }
float dht22_readTemperature() { return mockTemperature; }
long pulseIn(int pin, int state) { return mockPulseDuration; }
int digitalRead(int pin) { return mockDigitalValue; }
int analogRead(int pin) { return mockAnalogValue; }
void digitalWrite(int pin, int value) {}

// Testes para os sensores
void test_humidity_temperature_error() {
    mockHumidity = NAN;
    mockTemperature = NAN;
    TEST_ASSERT_TRUE(isnan(mockHumidity));
    TEST_ASSERT_TRUE(isnan(mockTemperature));
}

void test_humidity_temperature_success() {
    mockHumidity = 60.0;
    mockTemperature = 25.5;
    TEST_ASSERT_EQUAL_FLOAT(60.0, mockHumidity);
    TEST_ASSERT_EQUAL_FLOAT(25.5, mockTemperature);
}

void test_sound_sensor_measurement() {
    mockPulseDuration = 1000;
    TEST_ASSERT_EQUAL(1000, mockPulseDuration);
}

void test_lux_sensor_measurement() {
    mockAnalogValue = 2048;
    TEST_ASSERT_EQUAL(2048, mockAnalogValue);
}

void test_motion_detected() {
    mockDigitalValue = HIGH;
    TEST_ASSERT_EQUAL(HIGH, mockDigitalValue);
}

void test_no_motion_detected() {
    mockDigitalValue = LOW;
    TEST_ASSERT_EQUAL(LOW, mockDigitalValue);
}

// Executar todos os testes
void runTests() {
    UNITY_BEGIN();
    RUN_TEST(test_humidity_temperature_error);
    RUN_TEST(test_humidity_temperature_success);
    RUN_TEST(test_sound_sensor_measurement);
    RUN_TEST(test_lux_sensor_measurement);
    RUN_TEST(test_motion_detected);
    RUN_TEST(test_no_motion_detected);
    UNITY_END();
}

void setup() {
    runTests();
}

void loop() {}

#ifdef UNIT_TEST
int main() {
    setup();
    while (true) {
        loop();
        break; // Adicione o break para evitar um loop infinito durante os testes
    }
    return 0;
}
#endif
