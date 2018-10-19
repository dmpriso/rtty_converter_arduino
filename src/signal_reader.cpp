#include "signal_reader.h"

SignalReader::SignalReader(uint8_t pin, float baudRate, bool reverse)
    : m_pin(pin)
    , m_highValue(reverse ? LOW : HIGH)
    , m_baudRate(baudRate)
{
    pinMode(pin, INPUT);
}

bool SignalReader::read()
{
    return digitalRead(m_pin) == m_highValue;
}

float SignalReader::updateAndGetTimeSeconds()
{
    UsTimestamp now;
    auto diffUs = now - m_lastChangeUs;
    m_lastChangeUs = now;

    return static_cast<float>(diffUs) / 1,000,000.f;
}

void SignalReader::loop()
{
    auto current = read();
    if (current == m_lastValue)
        return;

    m_lastValue = current;
    auto time = updateAndGetTimeSeconds();
    auto bits = time * m_baudRate;

    processBits(current, bits);
}