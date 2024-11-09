#ifndef ARDUINO_MOCK_H
#define ARDUINO_MOCK_H

struct SerialMock {
    void begin(int) {}
    void println(const char*) {}
};

extern SerialMock Serial;

struct WiFiMock {
    void connect(const char*, const char*) {}
};

extern WiFiMock WiFi;

struct MQTTMock {
    void publish(const char*, const char*) {}
};

extern MQTTMock MQTT;

#endif // ARDUINO_MOCK_H
