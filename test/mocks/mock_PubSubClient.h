// test/mocks/mock_PubSubClient.h
#ifndef MOCK_PUBSUBCLIENT_H
#define MOCK_PUBSUBCLIENT_H

#include "mock_WiFiClient.h"
#include <iostream>
#include <functional>
#include <string>

class PubSubClient {
public:
    PubSubClient(WiFiClient& client) {
        // Constructor mock
        std::cout << "PubSubClient initialized with WiFiClient" << std::endl;
    }

    bool connected() {
        // Return mock connected status
        return true;
    }

    bool connect(const char* id) {
        // Mock connect
        std::cout << "MQTT.connect(\"" << id << "\")" << std::endl;
        return true; // Simulate successful connection
    }

    void subscribe(const char* topic) {
        // Mock subscribe
        std::cout << "MQTT.subscribe(\"" << topic << "\")" << std::endl;
    }

    bool publish(const char* topic, const char* payload) {
        // Mock publish
        std::cout << "MQTT.publish(\"" << topic << "\", \"" << payload << "\")" << std::endl;
        return true;
    }

    void loop() {
        // Mock loop
    }

    void setServer(const char* domain, uint16_t port) {
        // Mock setServer
        std::cout << "MQTT.setServer(\"" << domain << "\", " << port << ")" << std::endl;
    }

    void setCallback(std::function<void(char*, uint8_t*, unsigned int)> callback) {
        // Mock setCallback
        std::cout << "MQTT.setCallback()" << std::endl;
    }
};

#endif // MOCK_PUBSUBCLIENT_H
