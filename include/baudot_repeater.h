#ifndef BAUDOTREPEATER_H
#define BAUDOTREPEATER_H

#include "baudot_reader.h"
#include "buffered_writer.h"

template<int Size>
class BaudotRepeater
    : protected BaudotReader
    , protected BufferedWriter<Size>
{
public:
    BaudotRepeater(
        uint8_t inputPin,
        float inputBaudRate,
        uint8_t outputPin,
        float outputBaudRate,
        bool reverseInput = false,
        bool reverseOutput = false
    );

public:
    void loop();

private:
    void processChar(char chr) final;

};

template<int Size>
BaudotRepeater<Size>::BaudotRepeater(
        uint8_t inputPin,
        float inputBaudRate,
        uint8_t outputPin,
        float outputBaudRate,
        bool reverseInput,
        bool reverseOutput
    )
    : BaudotReader(inputPin, inputBaudRate, reverseInput)
    , BufferedWriter<Size>(outputPin, outputBaudRate, reverseOutput)
{}

template<int Size>
void BaudotRepeater<Size>::loop()
{
    BaudotReader::loop();
    BaudotRepeater::loop();
}

template<int Size>
void BaudotRepeater<Size>::processChar(char chr)
{
    BufferedWriter<Size>::write(chr);
}

#endif
