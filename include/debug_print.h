#ifndef DEBUGPRINT_H
#define DEBUGPRINT_H

//#define DEBUG_SERIAL Serial

#ifdef DEBUG_SERIAL

#include "print_stream.h"
class DebugPrint
{
public:
    static PrintStream ps;
};

#define DEBUGPRINT(x) DebugPrint::ps << x << "\n"; DebugPrint::ps.flush();

#else
#define DEBUGPRINT(x);
#endif

#define WARNINGPRINT(x) DEBUGPRINT("WARNING " << x)

#endif
