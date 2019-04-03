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

    inline void AutocompleteCRLF(bool autocomplete) { m_autocompleteCrLf = autocomplete; }
    inline bool AutocompleteCRLF() const { return m_autocompleteCrLf; }

private:
    void processChar(char chr) final;

    void autocompleteChar(char chr);
    void writeChar(char chr);

    char m_lastChar = 0;
    uint32_t m_lastCharTime = 0;
    bool m_hadChar = false;
    bool m_autocompleteCrLf = false;
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
void BaudotConverter<Size>::writeChar(char chr)
{
    BufferedWriter<Size>::write(chr);
}

template<int Size>
void BaudotConverter<Size>::autocompleteChar(char chr)
{
    if (!m_autocompleteCrLf)
        return;

    if (chr == '\n' && m_lastChar != '\r')
        writeChar('\r');
    else if (chr != '\n' && m_lastChar == '\r')
        writeChar('\n');
}

template<int Size>
void BaudotConverter<Size>::processChar(char chr)
{
    autocompleteChar(chr);

    writeChar(chr);
    m_hadChar = true;
    m_lastChar = chr;
    m_lastCharTime = millis();
}

#endif
