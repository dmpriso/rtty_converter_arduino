#include "baudot_writer.h"

BaudotWriter::BaudotWriter(
    uint8_t pin, 
    float baudRate, 
    float stopBitLength,
    bool reverse
    )
    : SignalWriter(pin, baudRate, reverse)
    , m_stopBitLength(stopBitLength)
{}

bool BaudotWriter::tryReleaseQueuedChar()
{
    if (0 == m_queuedChar)
        return false;

    setWithStartBit(m_queuedChar);
    m_queuedChar = 0;

    return true;
}

void BaudotWriter::setWithStartBit(unsigned char send)
{
    // add start bit
    m_curSend = (send << 1) & ~1;
}

void BaudotWriter::setNextSend()
{
    if (tryReleaseQueuedChar())
        return;

    unsigned char controlChar;
    unsigned char chr = m_baudot.charToBaudot(getNextChar(), controlChar);
    if (0 != controlChar)
    {
        m_queuedChar = chr;
        chr = controlChar;
    }
    setWithStartBit(chr);
}

bool BaudotWriter::getNextSignal(float& durationInBits)
{
    // while the baudot code has 5 bits, we also add the start bit to m_curSend, so we send 6 bits plus stop bits
    if (m_bitsSent < 6)
    {
        durationInBits = 1;
        return 0 != (m_curSend & (1 << m_bitsSent++));
    }
    else if (m_bitsSent == 6)
    {
        setNextSend();
        durationInBits = m_stopBitLength;
        return true;
    }
}
