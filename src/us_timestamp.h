#ifndef TOOLS_H
#define TOOLS_H

#include <Arduino.h>

class UsTimestamp
{
public:
    UsTimestamp() = default;
    UsTimestamp(const UsTimestamp&) = default;
    UsTimestamp& operator=(const UsTimestamp&) = default;

public:

    int32_t operator-(const UsTimestamp& diff);
    
    UsTimestamp operator+(int32_t val);
    inline UsTimestamp operator-(int32_t val) { return operator+(-val); }
    inline UsTimestamp& operator+=(int32_t val) { *this = *this + val; return *this; }
    inline UsTimestamp& operator-=(int32_t val) { *this = *this - val; return *this; }

    inline bool operator>(const UsTimestamp& compare) { return *this - compare > 0; }
    inline bool operator>=(const UsTimestamp& compare) { return *this - compare >= 0; }
    inline bool operator<(const UsTimestamp& compare) { return *this - compare < 0; }
    inline bool operator<=(const UsTimestamp& compare) { return *this - compare <= 0; }
    inline bool operator==(const UsTimestamp& compare) { return *this - compare == 0; }
    inline bool operator!=(const UsTimestamp& compare) { return *this - compare != 0; }

private:
    uint32_t value = micros();
};


#endif
