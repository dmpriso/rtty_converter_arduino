#include "baudot_reader.h"
#include "debug.h"

BaudotReader::BaudotReader(uint8_t pin, 
    float baudRate, 
    bool reverse)
    : SignalReader(pin, baudRate, reverse)
{}

bool BaudotReader::tryChangeState(State oldState, State newState)
{
    if (m_state != oldState)
        return false;

    DEBUGPRINT("Changing state from " << oldstate << " to " << newstate);
    m_state = newState;
    return true;
}

bool BaudotReader::tryEnterSynchronizable(bool high)
{
    return (high && tryChangeState(State::AwaitingSynchronizable, State::AwaitingStartBit));
}

bool BaudotReader::tryProcessStartBit(bool high)
{
    if (high || !tryChangeState(State::AwaitingStartBit, State::InChar))
        return false;

    m_current = 0;
    m_numBits = 0;
    return true;
}

bool BaudotReader::tryProcessCharBit(bool high)
{
    State newstate = (m_numBits == 4 ? State::AwaitingStopBit : State::InChar);

    if (!tryChangeState(State::InChar, newstate))
        return false;

    if (high)
        m_current = m_current | 1 << m_numBits;
    
    m_numBits++;
    
    return true;
}

void BaudotReader::processCurrentChar()
{
    auto chr = m_baudot.baudotToChar(m_current);
    if (chr != 0)
    {
        DEBUGPRINT("Processed char: " << chr);
        processChar(chr);
    }
}

bool BaudotReader::tryProcessStopBit(bool high)
{
    if (high && tryChangeState(State::AwaitingStopBit, State::AwaitingStartBit))
    {
        processCurrentChar();
        return true;
    }
    if (!high && tryChangeState(State::AwaitingStopBit, State::AwaitingSynchronizable))
    {
        m_baudot.reset();
        return true;
    }

    return false;
}

void BaudotReader::processBit(bool high)
{
    tryEnterSynchronizable(high) || 
    tryProcessStartBit(high) || 
    tryProcessStopBit(high) ||
    tryProcessCharBit(high);
}

void BaudotReader::processBits(bool high, float numBits)
{
    // discard short bits
    if (numBits < 0.6f)
        return;

    for (int i = 0; i < (int)roundf(numBits); i++)
        processBit(high);
}

