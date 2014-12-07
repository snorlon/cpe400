#ifndef FRAMEH
#define FRAMEH

#include <cstddef>
#include "datagram.h"
#include "mac.h"
#include "routing.h"
//layer 2 - Data link

class frame
{
    public:
        ip* senderIP;//for overall source and destination
        ip* destinationIP;
        mac* senderMac;//for direct source and destination, replaced at each step
        mac* destinationMac;

        int id;//for debugging

        routingEntry* routingData;//for storing data from RREQ

        frame* next;//for queuing them

        //hardware type not needed
        //protocol type assumed ARP
        //lengths not needed
        int operation;

        frame();
        frame(datagram* npayload, ip* originIP, ip* destIP, mac* locOrigin, mac* locDest, int noperation, routingEntry* priorEntries = NULL);
        ~frame();

        datagram* strip();//bring out that sexy packet to work with, returns null if none for some reason
    private:

        datagram* payload;//just some data to keep in here

};
#endif
