// test/mocks/mock_ArduinoJson.h
#ifndef MOCK_ARDUINOJSON_H
#define MOCK_ARDUINOJSON_H

#include <map>
#include <string>
#include <sstream>
#include <cstring>

class DynamicJsonDocument {
public:
    DynamicJsonDocument(size_t capacity) {
        // Constructor mock
    }

    std::map<std::string, float> data;

    float& operator[](const char* key) {
        return data[key];
    }
};

size_t serializeJson(DynamicJsonDocument& doc, char* output) {
    // Simple mock implementation
    std::ostringstream oss;
    oss << "{";
    bool first = true;
    for (const auto& pair : doc.data) {
        if (!first) {
            oss << ", ";
        }
        oss << "\"" << pair.first << "\": " << pair.second;
        first = false;
    }
    oss << "}";
    std::string jsonStr = oss.str();
    std::strcpy(output, jsonStr.c_str());
    return jsonStr.length();
}

#endif // MOCK_ARDUINOJSON_H
