#ifndef PRINTSTREAM_H
#define PRINTSTREAM_H

#include <Arduino.h>

class PrintStream
{
private:
    template<typename T> struct IsSpecial;

public:
    PrintStream(Print& underlying);

public:
    template<typename T>
    PrintStream& operator<<(T value);

    void flush();
    inline const Print& Underlying() const { return m_underlying; }
    Print& Underlying() { return m_underlying; }

private:
    Print& m_underlying;
};

template<typename T>
PrintStream& PrintStream::operator<<(T value)
{
    m_underlying.print(value);
    return *this;
}

#endif
