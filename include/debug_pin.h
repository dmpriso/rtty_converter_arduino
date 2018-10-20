#ifndef DEBUGPIN_H
#define DEBUGPIN_H

#include "pins.h"

// simulates an input and an output pins which are connected with each other
class DebugPin : public InputPin, public OutputPin
{
public:
    DebugPin() = default;

public:
    bool read() const final;
    void write(bool value) final;

private:
    bool m_value = false;
};

#endif
