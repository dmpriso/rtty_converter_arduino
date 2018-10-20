#include "debug_signal_reader.h"

DebugSignalReader::DebugSignalReader(
    const InputPin& pin, 
    float baudRate,
    Print& printTo)
    : SignalReader(pin, baudRate)
    , m_printTo(printTo)
{}

void DebugSignalReader::processBits(bool high, float numBits)
{
    auto print = high ? "-" : "_";
    for (int i = 0; i < static_cast<int>(roundf(numBits)); i++)
        m_printTo.print(print);

    m_printTo.flush();
}
