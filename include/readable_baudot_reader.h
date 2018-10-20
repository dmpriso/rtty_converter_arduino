#ifndef READABLEBAUDOTREADER_H
#define READABLEBAUDOTREADER_H

#include "baudot_reader.h"

class ReadableBaudotReader : public BaudotReader
{
public:
    ReadableBaudotReader(
        const InputPin& pin,
        float baudRate);

public:
    char read();

private:
    void processChar(char chr) final;

private:
    char m_chr = 0;
};

#endif
