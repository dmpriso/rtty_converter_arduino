#ifndef SIGNALWRITER_H
#define SIGNALWRITER_H

#include <Arduino.h>
#include "us_timestamp.h"
#include "pins.h"

class SignalWriter
{
public:
    SignalWriter(OutputPin& pin, float baudRate);

public:
    void loop();

private:
    // must be implemented to return the next signal and it's duration in bits. 
    // the duration is a float in order to support 1.5 stop bits
    virtual bool getNextSignal(float& durationInBits) = 0;

private:
    bool checkIfNext();
    float getDurationInUs(float durationInBits);

    void calcMaxJitterCorrection();
    int32_t getMaxJitterCorrection(int32_t diffUs);

private:
    OutputPin& m_pin;
    const float m_baudRate;

    UsTimestamp m_upTo;

    int32_t m_maxJitterCorrection;
};

#endif