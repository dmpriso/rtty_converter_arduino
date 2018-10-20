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
        const InputPin& inputPin,
        float inputBaudRate,
        OutputPin& outputPin,
        float outputBaudRate,
        float stopBitLength = 2.f
    );

public:
    void loop();

private:
    void processChar(char chr) final;

};

template<int Size>
BaudotRepeater<Size>::BaudotRepeater(
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
