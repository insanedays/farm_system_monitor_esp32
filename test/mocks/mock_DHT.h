// test/mocks/mock_DHT.h
#ifndef MOCK_DHT_H
#define MOCK_DHT_H

#include <cstdint>

class DHT {
public:
    DHT(uint8_t pin, uint8_t type) {
        // Constructor mock
    }

    void begin() {
        // Mock implementation: Do nothing
    }

    float readHumidity() {
        // Return a mock humidity value
        return 50.0f;
    }

    float readTemperature() {
        // Return a mock temperature value
        return 25.0f;
    }
};

#endif // MOCK_DHT_H
