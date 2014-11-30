#ifndef PACKETH
#define PACKETH

#include "mac.h"
//layer 4 - transport layer

class packet
{
    public:
        mac* destination;
        mac* source;

        packet* next;//for queuing them

        packet();
        ~packet();
    private:

};

#endif
