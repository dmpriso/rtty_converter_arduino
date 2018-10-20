#include "debug_baudot_reader.h"

DebugBaudotReader::DebugBaudotReader(
        const InputPin& pin,
        float baudRate,
        Print& printTo)
    : BaudotReader(pin, baudRate)
    , m_printTo(printTo)
{}

void DebugBaudotReader::processChar(char chr)
{
    m_printTo.print(chr);
}