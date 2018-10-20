#include "pins.h"

HardwareInputPin::HardwareInputPin(uint8_t pin, bool reverse)
    : m_pin(pin)
    , m_reverse(reverse)
{}

bool HardwareInputPin::read()
{
    return digitalRead(m_pin) == (m_reverse ? LOW : HIGH);
}

HardwareOutputPin::HardwareOutputPin(uint8_t pin, bool reverse)
    : m_pin(pin)
    , m_reverse(reverse)
{}

void HardwareOutputPin::write(bool value)
{
    digitalWrite(m_pin, value ^ m_reverse ? HIGH : LOW);
}
