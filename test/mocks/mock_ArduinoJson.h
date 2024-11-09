#ifndef MOCK_ARDUINOJSON_H
#define MOCK_ARDUINOJSON_H

#include <map>
#include <string>
#include <sstream>
#include <cstring>

class DynamicJsonDocument {
public:
    DynamicJsonDocument(size_t capacity) {}
    std::map<std::string, float> data;
    float& operator[](const char* key) {
        return data[key];
    }
};

inline size_t serializeJson(const DynamicJsonDocument& doc, char* output) {
    std::ostringstream oss;
    oss << "{";
    bool first = true;
    for (const auto& pair : doc.data) {
        if (!first) oss << ", ";
        oss << "\"" << pair.first << "\": " << pair.second;
        first = false;
    }
    oss << "}";
    std::string jsonStr = oss.str();
    std::strcpy(output, jsonStr.c_str());
    return jsonStr.length();
}

#endif // MOCK_ARDUINOJSON_H