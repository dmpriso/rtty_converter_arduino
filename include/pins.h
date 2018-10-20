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

class ReversablePin
{
public:
    ReversablePin(bool reverse = false);
public:
    void Reverse(bool reverse);
    bool Reverse() const;

private:
    bool m_reverse = false;
};

class HardwareInputPin : public InputPin, public ReversablePin
{
public:
    HardwareInputPin(uint8_t pin, bool pullUp = false, bool reverse = false);
public:
    bool read() const final;
private:
    const uint8_t m_pin;
};

class HardwareOutputPin : public OutputPin, public ReversablePin
{
public:
    HardwareOutputPin(uint8_t pin, bool reverse = false);
public:
    void write(bool value) final;
private:
    const uint8_t m_pin;
};

#endif
