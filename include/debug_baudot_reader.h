#ifndef DEBUGBAUDOTREADER_H
#define DEBUGBAUDOTREADER_H

#include "baudot_reader.h"

class DebugBaudotReader : public BaudotReader
{
public:
    DebugBaudotReader(
        const InputPin& pin,
        float baudRate,
        Print& printTo);

private:
    void processChar(char chr) final;

private:
    Print& m_printTo;
};


#endif
