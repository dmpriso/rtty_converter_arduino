#include "signal_reader.h"

SignalReader::SignalReader(const InputPin& pin, float baudRate)
    : m_pin(pin)
    , m_baudRate(baudRate)
{}

float SignalReader::updateAndGetTimeSeconds()
{
    UsTimestamp now;
    auto diffUs = now - m_lastChangeUs;
    m_lastChangeUs = now;

    return static_cast<float>(diffUs) / 1000000.f;
}

void SignalReader::loop()
{
    auto current = m_pin.read();
    if (current == m_lastValue)
        return;

    m_lastValue = current;
    auto time = updateAndGetTimeSeconds();
    auto bits = time * m_baudRate;

    processBits(!current, bits);
}
