#ifndef TOOLS_H
#define TOOLS_H

#include <Arduino.h>

class UsTimestamp
{
public:
    UsTimestamp() = default;
    UsTimestamp(const UsTimestamp&) = default;
    UsTimestamp& operator=(const UsTimestamp&) = default;

    int32_t operator-(const UsTimestamp& diff);

private:
    uint32_t value = micros();;
};


#endif
