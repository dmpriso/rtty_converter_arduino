#ifndef SIGNALWRITER_H
#define SIGNALWRITER_H

#include <Arduino.h>
#include "us_timestamp.h"

class SignalWriter
{
public:
    SignalWriter(uint8_t pin, float baudRate, bool reverse = false);

public:
    void loop();

private:
    // must be implemented to return the next signal and it's duration in bits. 
    // the duration is a float in order to support 1.5 stop bits
    virtual bool getNextSignal(float& durationInBits) = 0;

private:
    bool checkIfNext();
    void write(bool signal);
    float getDurationInUs(float durationInBits);

private:
    const uint8_t m_pin;
    const float m_baudRate;
    const bool m_reverse;

    UsTimestamp m_upTo;
};

#endif