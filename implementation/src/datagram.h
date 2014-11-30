#include "ip.h"
#include "packet.h"
//layer 3 - Network

class datagram
{
    public:
        ip* destination;
        ip* source;

        datagram* next;//for queuing them

        datagram();
        ~datagram();

        packet* strip();//bring out that sexy segment to work with, returns null if none for some reason
    private:

        packet* payload;//just some data to keep in here

};
