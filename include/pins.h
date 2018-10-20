#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

class InputPin
{
public:
    virtual bool read() const = 0;
};

class OutputPin
{
public:
    virtual void write(bool value) = 0;
};

class InvertablePin
{
public:
    InvertablePin(bool invert = false);
public:
    void Inverted(bool invert);
    bool Inverted() const;

private:
    bool m_inverted = false;
};

class HardwareInputPin : public InputPin, public InvertablePin
{
public:
    HardwareInputPin(uint8_t pin, bool pullUp = false, bool reverse = false);
public:
    bool read() const final;
private:
    const uint8_t m_pin;
};

class HardwareOutputPin : public OutputPin, public InvertablePin
{
public:
    HardwareOutputPin(uint8_t pin, bool reverse = false);
public:
    void write(bool value) final;
private:
    const uint8_t m_pin;
};

#endif
