// test/mocks/mock_Serial.h
#ifndef MOCK_SERIAL_H
#define MOCK_SERIAL_H

#include <iostream>
#include <string>
#include <cstdarg>

class MockSerial {
public:
    void begin(int baudRate) {
        std::cout << "Serial.begin(" << baudRate << ")" << std::endl;
    }

    void print(const char* message) {
        std::cout << message;
    }

    void print(const std::string& message) {
        std::cout << message;
    }

    void print(int value) {
        std::cout << value;
    }

    void print(float value) {
        std::cout << value;
    }

    void println() {
        std::cout << std::endl;
    }

    void println(const char* message) {
        std::cout << message << std::endl;
    }

    void println(const std::string& message) {
        std::cout << message << std::endl;
    }

    void println(int value) {
        std::cout << value << std::endl;
    }

    void println(float value) {
        std::cout << value << std::endl;
    }

    void printf(const char* format, ...) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
};

extern MockSerial Serial;

#endif // MOCK_SERIAL_H
