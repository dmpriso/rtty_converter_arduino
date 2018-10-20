#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

class InputPin
{
public:
    virtual bool read() = 0;
};

class OutputPin
{
public:
    virtual void write(bool value) = 0;
};

class HardwareInputPin : public InputPin
{
public:
    HardwareInputPin(uint8_t pin, bool reverse = false);
public:
    bool read() final;
private:
    const uint8_t m_pin;
    const bool m_reverse;
};

class HardwareOutputPin : public OutputPin
{
public:
    HardwareOutputPin(uint8_t pin, bool reverse = false);
public:
    void write(bool value) final;
private:
    const uint8_t m_pin;
    const bool m_reverse;
};

#endif