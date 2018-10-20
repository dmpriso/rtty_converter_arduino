#ifndef BUFFERED_WRITER_H
#define BUFFERED_WRITER_H

#include "baudot_writer.h"

template<int Size>
class BufferedWriter : public BaudotWriter
{
public:
    BufferedWriter(
        OutputPin& pin, 
        float baudRate, 
        float stopBitLength = 2.f);

public:
    void write(char chr);
    void write(const char* str);

private:
    char getNextChar() final;

private:
    int getAndAdvancePos(int& pos);

private:
    char m_buf[Size];
    int m_readPos = 0;
    int m_writePos = 0;
};

template<int Size>
BufferedWriter<Size>::BufferedWriter(
        OutputPin& pin, 
        float baudRate, 
        float stopBitLength)
    : BaudotWriter(pin, baudRate, stopBitLength)
{
    static_assert(Size >= 2, "Queue size must at least be 2");
}

template<int Size>
char BufferedWriter<Size>::getNextChar()
{
    if (m_readPos == m_writePos)
        return 0;

    auto chr = m_buf[getAndAdvancePos(m_readPos)];
    return chr;
}

template<int Size>
int BufferedWriter<Size>::getAndAdvancePos(int& pos)
{
    auto ret = pos;
    ++pos;
    if (pos == Size)
        pos = 0;
    
    return ret;
}

template<int Size>
void BufferedWriter<Size>::write(char chr)
{
    m_buf[getAndAdvancePos(m_writePos)] = chr;
}

template<int Size>
void BufferedWriter<Size>::write(const char* chr)
{
    while(0 != *chr)
        write(*chr++);
}

#endif
