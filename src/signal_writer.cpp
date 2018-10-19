#include "signal_writer.h"

SignalWriter::SignalWriter(uint8_t pin, float baudRate, bool reverse)
    : m_pin(pin)
    , m_baudRate(baudRate)
    , m_reverse(reverse)
{
    pinMode(pin, OUTPUT);
}

bool SignalWriter::checkIfNext()
{
    UsTimestamp now;
    auto diff = m_upTo - now;
    if (diff < 0)
        return false;

    m_upTo = now - diff;
    return true;
}

void SignalWriter::write(bool signal)
{
    digitalWrite(m_pin, signal ^ m_reverse ? HIGH : LOW);
}

float SignalWriter::getDurationInUs(float durationInBits)
{
    return durationInBits * 1,000,000.f / m_baudRate;
}

void SignalWriter::loop()
{
    if (!checkIfNext())
        return;
    
    float durationInBits;
    write(getNextSignal(durationInBits));
    
    m_upTo += getDurationInUs(durationInBits);
}
