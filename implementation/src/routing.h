#ifndef ROUTINGH
#define ROUTINGH

#include <cstddef>
#include "mac.h"
#include "link.h"

class hub;
class ip;
class routingEntry
{
    public:
        ip* targetIP;//the ip where we're headed
        mac* nextHopMac;//the next direct step to our destination

        hub* device;//not supposed to be here, but is for simulation stuff to tell us device stuff that we're holding routing to

        int weight;//unused maybe?

        routingEntry* next;

        routingEntry(hub* ndevice, ip* target, mac* nextHop, int nweight = 1, routingEntry* priorEntry = NULL);
        ~routingEntry();

        bool containsIP(ip* address);

    private:

};
#endif
