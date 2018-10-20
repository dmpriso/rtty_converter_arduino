#include "print_stream.h"

PrintStream::PrintStream(Print& underlying)
    : m_underlying(underlying)
{}

void PrintStream::flush()
{
    m_underlying.flush();
}
