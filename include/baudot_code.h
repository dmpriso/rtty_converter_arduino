#ifndef BAUDOT_H
#define BAUDOT_H

class BaudotCode
{
public:
    // special chars:
    // � = who there?
    // \a = ring
    // % = number mode
    // a = char mode
    // # = nul

    char baudotToChar(unsigned char byt);

    /**
     * @param switchCode Baudot code to be sent for the current number mode (if changed)
     */
    unsigned char charToBaudot(char chr, unsigned char& switchCode);
    void reset();

private:
    char handleControlChar(char chr);

    unsigned char setNumbermode(bool numberMode);

    static int findChar(char chr);
    static int findNumber(char chr);

    static constexpr const char* s_chartable = "#E\rA SIU\nDRJNFCKTZLWHYPQOBG%MXVa";
    static constexpr const char* s_numtable = "#3\r- '87\n#4',#:(5+)2#6019?#%./=a";

private:
    bool m_numberMode = false;
};

#endif
