// test/mocks/mock_Wire.h
#ifndef MOCK_WIRE_H
#define MOCK_WIRE_H

class TwoWire {
public:
    void begin(int sda = -1, int scl = -1) {
        // Mock implementation: Do nothing
    }
};

extern TwoWire Wire;

#endif // MOCK_WIRE_H
