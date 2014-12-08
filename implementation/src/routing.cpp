#include "routing.h"
#include "ip.h"
#include "hub.h"


routingEntry::routingEntry(hub* ndevice, ip* target, mac* nextHop, int nweight, routingEntry* priorEntry)
{
    targetIP = target;
    nextHopMac = nextHop;

    weight = nweight;
    next = priorEntry;

    device = ndevice;
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
