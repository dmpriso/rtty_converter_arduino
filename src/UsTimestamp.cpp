#include "UsTimestamp.h"

int32_t UsTimestamp::operator-(const UsTimestamp& diff)
{
    return static_cast<int32_t>(this->value - diff.value);
}