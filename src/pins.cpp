#include "pins.h"

ReversablePin::ReversablePin(bool reverse)
    : m_reverse(reverse)
{}

void ReversablePin::Reverse(bool reverse)
{
    m_reverse = reverse;
}

bool ReversablePin::Reverse() const
{
    return m_reverse;
}

HardwareInputPin::HardwareInputPin(uint8_t pin, bool pullUp, bool reverse)
    : ReversablePin(reverse)
    , m_pin(pin)
{
    pinMode(pin, pullUp ? INPUT_PULLUP : INPUT);
}

bool HardwareInputPin::read() const
{
    return digitalRead(m_pin) == (Reverse() ? LOW : HIGH);
}

HardwareOutputPin::HardwareOutputPin(uint8_t pin, bool reverse)
    : ReversablePin(reverse)
    , m_pin(pin)
{
    pinMode(pin, OUTPUT);
}

void HardwareOutputPin::write(bool value)
{
    digitalWrite(m_pin, (value ^ Reverse()) ? HIGH : LOW);
}
