#include "blink.h"

Blink::Blink(OutputPin& pin)
    : m_pin(pin)
{
    m_pin.write(false);
}

void Blink::setInterval(uint32_t intervalMs)
{
    m_intervalMs = intervalMs;
}

void Blink::write(bool state)
{
    if (m_curState == state)
        return;

    m_pin.write(state);
    m_curState = state;
    m_lastMillis = millis();
}   

void Blink::stop()
{
    m_intervalMs = 0;
}

void Blink::loop()
{
    if (m_intervalMs == 0)
    {
        write(false);
        return;
    }
    if (millis() - m_lastMillis < m_intervalMs)
        return;

    write(!m_curState);
}
