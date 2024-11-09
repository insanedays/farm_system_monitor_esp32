#include <unity.h>
#include "test_main.cpp"

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
void lcdPrint(const char* message) { Serial.println(message); }
void EnviaValores(const char* topic, float value1, float value2) {
    Serial.printf("Mock EnviaValores - Topic: %s, Value1: %.2f, Value2: %.2f\n", topic, value1, value2);
}

// Tests
void test_humidity_temperature_error() {
    mockHumidity = NAN;
    mockTemperature = NAN;
    humidity_temperature();
}

void test_humidity_temperature_success() {
    mockHumidity = 60.0;
    mockTemperature = 25.5;
    humidity_temperature();
    TEST_ASSERT_EQUAL_FLOAT(60.0, mockHumidity);
    TEST_ASSERT_EQUAL_FLOAT(25.5, mockTemperature);
}

void test_sound_sensor_measurement() {
    mockPulseDuration = 1000;
    sound();
}

void test_lux_sensor_measurement() {
    mockAnalogValue = 2048;
    lux();
}

void test_motion_detected() {
    mockDigitalValue = HIGH;
    movi();
}

void test_no_motion_detected() {
    mockDigitalValue = LOW;
    movi();
}

// Run all tests
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
    Serial.begin(9600);
    runTests();
}

void loop() {}
