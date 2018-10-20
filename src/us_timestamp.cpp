#include "us_timestamp.h"

UsTimestamp UsTimestamp::operator+(int32_t val)
{
    UsTimestamp ret(*this);
    if (val >= 0)
        ret.value += static_cast<uint32_t>(val);
    else
        ret.value -= static_cast<uint32_t>(-val);

    return ret;
}

int32_t UsTimestamp::operator-(const UsTimestamp& diff)
{
    return static_cast<int32_t>(this->value - diff.value);
}
