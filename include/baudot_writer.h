#ifndef BAUDOTWRITER_H
#define BAUDOTWRITER_H

#include "signal_writer.h"
#include "baudot_code.h"

class BaudotWriter : public SignalWriter
{
public:
    BaudotWriter(
        OutputPin& pin, 
        float baudRate, 
        float stopBitLength = 1.5f);

private:
    virtual char getNextChar() = 0;

    bool getNextSignal(float& durationInBits) final;

private:
    bool tryReleaseQueuedChar();
    void setWithStartBit(unsigned char send);
    void setNextSend();

private:
    const float m_stopBitLength;

    BaudotCode m_baudot;

    unsigned char m_queuedChar = 0;
    unsigned char m_curSend;
    uint8_t m_bitsSent;
};

#endif
