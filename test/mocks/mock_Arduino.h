#ifndef MOCK_ARDUINO_H
#define MOCK_ARDUINO_H

#include <cstdint>
#include <string>
#include <thread>
#include <chrono>
#include <cmath>

// Define Arduino types
typedef uint8_t byte;

// Define Arduino constants
#ifndef HIGH
#define HIGH 1
#endif

#ifndef LOW
#define LOW 0
#endif

// Mock delay functions
inline void delay(unsigned long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

inline void delayMicroseconds(unsigned int us) {
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}

// Mock String class
class String : public std::string {
public:
    String() : std::string() {}
    String(const char* s) : std::string(s) {}
    String(const std::string& s) : std::string(s) {}
    String& operator+=(char c) {
        this->push_back(c);
        return *this;
    }
    String& operator+=(const char* s) {
        this->append(s);
        return *this;
    }
    String& operator+=(const std::string& s) {
        this->append(s);
        return *this;
    }
};

#endif // MOCK_ARDUINO_H
