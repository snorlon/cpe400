#include "routing.h"
#include "ip.h"
#include "hub.h"

routingEntry::routingEntry(hub* ndevice)
{
    targetIP = NULL;
    nextHopMac = NULL;

    device = ndevice;

    weight = 1;
    next = NULL;
}

routingEntry::routingEntry(routingEntry* oldEntry)
{
    targetIP = oldEntry->targetIP;
    nextHopMac = oldEntry->nextHopMac;
    weight = oldEntry->weight;
    next = NULL;

    device = oldEntry->device;
}


routingEntry::routingEntry(ip* target, mac* nextHop, int nweight, routingEntry* priorEntry)
{
    targetIP = target;
    nextHopMac = nextHop;

    weight = nweight;
    next = priorEntry;
}


routingEntry::~routingEntry()
{

}

bool routingEntry::containsIP(ip* address)
{
    if(targetIP == NULL)
    {
        return false;
    }
    else
    {
        if(*address == *targetIP)
        {
            return true;
        }
    }

    if(next == NULL)
        return false;
    return next->containsIP(address);
}
