#include "pins.h"

InvertablePin::InvertablePin(bool invert)
    : m_inverted(invert)
{}

void InvertablePin::Inverted(bool invert)
{
    m_inverted = invert;
}

bool InvertablePin::Inverted() const
{
    return m_inverted;
}

HardwareInputPin::HardwareInputPin(uint8_t pin, bool pullUp, bool reverse)
    : InvertablePin(reverse)
    , m_pin(pin)
{
    pinMode(pin, pullUp ? INPUT_PULLUP : INPUT);
}

bool HardwareInputPin::read() const
{
    return digitalRead(m_pin) == (Inverted() ? LOW : HIGH);
}

HardwareOutputPin::HardwareOutputPin(uint8_t pin, bool reverse)
    : InvertablePin(reverse)
    , m_pin(pin)
{
    pinMode(pin, OUTPUT);
}

void HardwareOutputPin::write(bool value)
{
    digitalWrite(m_pin, (value ^ Inverted()) ? HIGH : LOW);
}
