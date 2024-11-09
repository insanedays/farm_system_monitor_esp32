#ifndef MOCK_WIFI_H
#define MOCK_WIFI_H

#define WL_CONNECTED 3

struct WiFiMock {
    int status() { return WL_CONNECTED; }
    void begin(const char*, const char*) {}
    unsigned int localIP() { return 0xC0A80001; } // Mock IP 192.168.0.1
};

extern WiFiMock WiFi;

#endif // MOCK_WIFI_H
