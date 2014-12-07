#ifndef ROUTINGH
#define ROUTINGH

#include <cstddef>
#include "mac.h"
#include "link.h"

class ip;
class routingEntry
{
    public:
        ip* targetIP;//the ip where we're headed
        mac* nextHopMac;//the next direct step to our destination

        int weight;//unused maybe?

        routingEntry* next;

        routingEntry();
        routingEntry(routingEntry* oldEntry);
        routingEntry(ip* target, mac* nextHop, int nweight = 1, routingEntry* priorEntry = NULL);
        ~routingEntry();

        bool containsIP(ip* address);

    private:

};
#endif
