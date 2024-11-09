#ifndef MOCK_MQTT_H
#define MOCK_MQTT_H

struct MQTTMock {
    bool connected() { return true; }
    bool connect(const char*) { return true; }
    void subscribe(const char*) {}
    void publish(const char*, const char*) {}
};

extern MQTTMock MQTT;

#endif // MOCK_MQTT_H
