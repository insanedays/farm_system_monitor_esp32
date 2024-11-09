// test/mocks/mock_WiFi.h
#ifndef MOCK_WIFI_H
#define MOCK_WIFI_H

#include <iostream>
#include <string>

#define WL_CONNECTED 1

class WiFiClass {
public:
    int status() {
        // Return connected status
        return WL_CONNECTED;
    }

    void begin(const char* ssid, const char* password) {
        // Mock WiFi begin
        std::cout << "WiFi.begin(\"" << ssid << "\", \"" << password << "\")" << std::endl;
    }

    std::string localIP() {
        // Return mock IP address
        return "192.168.1.100";
    }
};

extern WiFiClass WiFi;

#endif // MOCK_WIFI_H
