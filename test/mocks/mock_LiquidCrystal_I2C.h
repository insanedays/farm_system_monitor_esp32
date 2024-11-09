// test/mocks/mock_LiquidCrystal_I2C.h
#ifndef MOCK_LIQUIDCRYSTAL_I2C_H
#define MOCK_LIQUIDCRYSTAL_I2C_H

#include <iostream>
#include <string>

class LiquidCrystal_I2C {
public:
    LiquidCrystal_I2C(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) {
        // Constructor mock
        std::cout << "LCD initialized at address " << static_cast<int>(lcd_Addr) << std::endl;
    }

    void init() {
        std::cout << "LCD init()" << std::endl;
    }

    void backlight() {
        std::cout << "LCD backlight turned on" << std::endl;
    }

    void clear() {
        std::cout << "LCD cleared" << std::endl;
    }

    void print(const char* str) {
        std::cout << "LCD print: " << str << std::endl;
    }

    void print(float num) {
        std::cout << "LCD print: " << num << std::endl;
    }

    void setCursor(uint8_t col, uint8_t row) {
        std::cout << "LCD cursor set to (" << static_cast<int>(col) << ", " << static_cast<int>(row) << ")" << std::endl;
    }
};

#endif // MOCK_LIQUIDCRYSTAL_I2C_H
