#include "baudot_code.h"
#include "debug_print.h"

void BaudotCode::reset() { m_numberMode = false; }

char BaudotCode::handleControlChar(char chr)
{
    if (m_numberMode && chr == 'a')
    {
        m_numberMode = false;
        return 0;
    }
    else if (!m_numberMode && chr == '%')
    {
        m_numberMode = true;
        return 0;
    }
    else if (chr == '#')
        return 0;

    return chr;
}

char BaudotCode::baudotToChar(unsigned char byt)
{
    if (byt > 31)
    {
        WARNINGPRINT("baudot input too large: " << (int)byt);
        return 0;
    }

    auto chr = (m_numberMode ? s_numtable : s_chartable)[byt];

    return handleControlChar(chr);
}

static int find(const char* ary, char chr)
{
    for (int i = 0; i < 32; i++)
        if (ary[i] == chr)
            return i;
    return -1;
}

int BaudotCode::findChar(char chr) { return find(s_chartable, chr); }

int BaudotCode::findNumber(char chr) { return find(s_numtable, chr); }

unsigned char BaudotCode::charToBaudot(char chr, unsigned char& switchCode)
{
    if (chr == 0)
        chr = '#';

    int id;
    if (-1 != (id = findChar(chr)))
    {
        switchCode = setNumbermode(false);
        return (unsigned char)id;
    }

    if (-1 != (id = findNumber(chr)))
    {
        switchCode = setNumbermode(true);
        return (unsigned char)id;
    }

    WARNINGPRINT("cannot send unknown char: " << chr);
    switchCode = 0;
    m_numberMode = false;
    return 0;
}

unsigned char BaudotCode::setNumbermode(bool numberMode)
{
    if (numberMode == m_numberMode)
        return 0;

    m_numberMode = numberMode;

    return (unsigned char)find(s_chartable, numberMode ? '%' : 'a');
}
