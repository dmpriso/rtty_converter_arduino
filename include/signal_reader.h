#include <Arduino.h>
#include "us_timestamp.h"

class SignalReader
{
public:
    SignalReader(uint8_t pin, float baudRate, bool reverse = false);

    bool read();
    void loop();
    float updateAndGetTimeSeconds();

private:
    virtual void processBits(bool high, float numBits) = 0;

private:
    const uint8_t m_pin;
    const int m_highValue;
    const float m_baudRate;

    bool m_lastValue = false;
    UsTimestamp m_lastChangeUs;
};
