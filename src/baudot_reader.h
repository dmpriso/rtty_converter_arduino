#ifndef BAUDOTREADER_H
#define BAUDOTREADER_H

#include "signal_reader.h"
#include "baudot_code.h"

class BaudotReader : public SignalReader
{
private:
    enum class State
    {
        AwaitingSynchronizable,
        AwaitingStartBit,
        InChar,
        AwaitingStopBit
    };

public:
    BaudotReader(uint8_t pin, 
        float baudRate, 
        bool reverse = false);

private:
    virtual void processChar(char chr) = 0;

    void processBits(bool high, float numBits) final;

private:
    bool tryChangeState(State oldState, State newState);

    bool tryEnterSynchronizable(bool high);
    bool tryProcessStartBit(bool high);
    bool tryProcessCharBit(bool high);
    bool tryProcessStopBit(bool high);
    void processBit(bool high);

    void processCurrentChar();

private:
    State m_state;
    
    unsigned char m_current;
    int m_numBits;

    BaudotCode m_baudot;

};

#endif
