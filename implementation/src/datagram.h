#ifndef DATAGRAMH
#define DATAGRAMH

#include "ip.h"
#include "packet.h"
#include <cstddef>
//layer 3 - Network

class datagram
{
    public:
        ip* destination;
        ip* source;

        datagram* next;//for queuing them

        //version not needed
        //length, type of service not needed
        int id;//for fragmenting
        int fragOffset;
        bool flags[4];
        int TTL;// hops left
        //upper layer protocol not needed, assumed UDP
        //no checksum
        //options data stored differently?

        datagram();
        datagram(packet* npayload, ip* origin, ip* dest, int nTTL, int nid = 0, int nfragment = 0, bool fragFlag=false );
        ~datagram();

        packet* strip();//bring out that sexy segment to work with, returns null if none for some reason
    private:

        packet* payload;//just some data to keep in here

};

#endif
