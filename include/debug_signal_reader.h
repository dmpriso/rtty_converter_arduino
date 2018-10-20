#ifndef DEBUG_SIGNAL_READER
#define DEBUG_SIGNAL_READER

#include "debug_print.h"
#include "signal_reader.h"

class DebugSignalReader : public SignalReader
{
public:
    DebugSignalReader(
        const InputPin& pin, 
        float baudRate,
        Print& printTo);
private:
    void processBits(bool high, float numBits) final;

private:
    Print& m_printTo;
};

#endif
