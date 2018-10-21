#ifndef BLINK_H
#define BLINK_H

#include "pins.h"

class Blink
{
public:
    Blink(OutputPin& pin);

public:
    void setInterval(uint32_t intervalMs);
    void stop();

    void loop();

private:
    void write(bool state);
    bool shouldChange();

private:
    OutputPin& m_pin;
    uint32_t m_intervalMs = 0;

    uint32_t m_lastMillis;

    bool m_curState = false;
};

#endif
