#ifndef MOCK_SERIAL_H
#define MOCK_SERIAL_H

struct SerialMock {
    void begin(int) {}
};

extern SerialMock Serial;

#endif // MOCK_SERIAL_H
