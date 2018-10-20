#ifndef SIGNALREADER_H
#define SIGNALREADER_H

#include <Arduino.h>
#include "us_timestamp.h"

#include "pins.h"

class SignalReader
{
public:
    SignalReader(const InputPin& pin, float baudRate);

    void loop();
    float updateAndGetTimeSeconds();

private:
    virtual void processBits(bool high, float numBits) = 0;

private:
    const InputPin& m_pin;
    const float m_baudRate;

    bool m_lastValue = false;
    UsTimestamp m_lastChangeUs;
};

#endif