#include "debug_pin.h"

bool DebugPin::read() const
{
    return m_value;
}

void DebugPin::write(bool value)
{
    m_value = value;
}
