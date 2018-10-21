#ifndef BAUDOTCONVERTER_H
#define BAUDOTCONVERTER_H

#include "baudot_reader.h"
#include "buffered_writer.h"

template<int Size>
class BaudotConverter
    : protected BaudotReader
    , protected BufferedWriter<Size>
{
public:
    BaudotConverter(
        const InputPin& inputPin,
        float inputBaudRate,
        OutputPin& outputPin,
        float outputBaudRate,
        float stopBitLength = 2.f
    );

public:
    void loop();

    inline uint32_t lastCharTime() const { return m_lastCharTime; }
    inline bool isActive() const { return m_hadChar && millis() - m_lastCharTime < 1000; }

private:
    void processChar(char chr) final;

    uint32_t m_lastCharTime = 0;
    bool m_hadChar = false;
};

template<int Size>
BaudotConverter<Size>::BaudotConverter(
        const InputPin& inputPin,
        float inputBaudRate,
        OutputPin& outputPin,
        float outputBaudRate,
        float stopBitLength
    )
    : BaudotReader(inputPin, inputBaudRate)
    , BufferedWriter<Size>(outputPin, outputBaudRate, stopBitLength)
{}

template<int Size>
void BaudotConverter<Size>::loop()
{
    BaudotReader::loop();
    BufferedWriter<Size>::loop();
}

template<int Size>
void BaudotConverter<Size>::processChar(char chr)
{
    BufferedWriter<Size>::write(chr);
    m_hadChar = true;
    m_lastCharTime = millis();
}

#endif
