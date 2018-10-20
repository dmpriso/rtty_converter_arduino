#include "readable_baudot_reader.h"

ReadableBaudotReader::ReadableBaudotReader(const InputPin& pin, float baudRate)
    : BaudotReader(pin, baudRate)
{}

char ReadableBaudotReader::read()
{
    auto tmp = m_chr;
    m_chr = 0;
    return tmp;
}

bool ReadableBaudotReader::hasData() const
{
    return 0 != m_chr;
}

void ReadableBaudotReader::processChar(char chr)
{
    m_chr = chr;
}
