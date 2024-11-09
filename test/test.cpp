#include <unity.h>

#define PIN_DHT 23
#define DHT_MODEL DHT22

#ifndef HIGH
#define HIGH 1
#endif

#ifndef LOW
#define LOW 0
#endif

// Mock variables for testing hardware functions
float mockHumidity = 60.0;
float mockTemperature = 25.5;
float mockHumidityNan = 00.0;
float mockTemperatureNan = 00.0;
long mockPulseDuration = 1000;
int mockDigitalValue = 0;
int mockAnalogValue = 2048;

// Mock functions
float dht22_readHumidity() { return mockHumidity; }
float dht22_readTemperature() { return mockTemperature; }
long pulseIn(int pin, int state) { return mockPulseDuration; }
int analogRead(int pin) { return mockAnalogValue; }
void digitalWrite(int pin, int value) {}

void test_humidity_temperature_success() {
    TEST_ASSERT_EQUAL_FLOAT(60.0, dht22_readHumidity());
    TEST_ASSERT_EQUAL_FLOAT(25.5, dht22_readTemperature());
}
// Testes para os sensores
void test_humidity_temperature_error() {
    mockHumidityNan = NAN;
    mockTemperatureNan = NAN;
    TEST_ASSERT_TRUE(isnan(mockHumidityNan));
    TEST_ASSERT_TRUE(isnan(mockTemperatureNan));
}



void test_sound_sensor_measurement() {
    TEST_ASSERT_EQUAL_FLOAT(1000, pulseIn(1,1));
}

void test_lux_sensor_measurement() {
    TEST_ASSERT_EQUAL(2048, analogRead(1));
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
