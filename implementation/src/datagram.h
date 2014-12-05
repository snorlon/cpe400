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
        ~datagram();

        packet* strip();//bring out that sexy segment to work with, returns null if none for some reason
    private:

        packet* payload;//just some data to keep in here

};
