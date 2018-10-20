#include "signal_writer.h"
#include "debug_print.h"

SignalWriter::SignalWriter(OutputPin& pin, float baudRate)
    : m_pin(pin)
    , m_baudRate(baudRate)
{
    calcMaxJitterCorrection();
}

void SignalWriter::calcMaxJitterCorrection()
{
    // we want the jitter correction for small errors, but we want to omit it if e.g. loop() wasn't called
    // for a long time.
    // so let's set it to a third of a bit

    m_maxJitterCorrection = static_cast<int32_t>((1000000.f / m_baudRate) / 3.f);
}

int32_t SignalWriter::getMaxJitterCorrection(int32_t diffUs)
{
    if (abs(diffUs) > m_maxJitterCorrection)
        return 0;

    return diffUs;
}

bool SignalWriter::checkIfNext()
{
    UsTimestamp now;
    auto diff = now - m_upTo;

    if (diff < 0)
        return false;

    m_upTo = now - getMaxJitterCorrection(diff);
    return true;
}

float SignalWriter::getDurationInUs(float durationInBits)
{
    return durationInBits * 1000000.f / m_baudRate;
}

void SignalWriter::loop()
{
    if (!checkIfNext())
        return;
    
    float durationInBits;
    bool signal = getNextSignal(durationInBits);
    m_pin.write(signal);

    float us = getDurationInUs(durationInBits);
    
    m_upTo += static_cast<int32_t>(us);
}
