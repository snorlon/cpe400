#include "packet.h"
#include "ip.h"

//layer 4 - Transport


packet::packet()
{
    destination = NULL;
    source = NULL;

    data = "ERROR";

    next = NULL;

    sourcePort = 0;//unused
    destinationPort = 0;
}

packet::packet(string newData, ip* origin, ip* dest)
{
    destination = dest;
    source = origin;

    data = newData;//load in the data to be moved

    next = NULL;

    sourcePort = 0;//unused
    destinationPort = 0;
}

packet::~packet()
{

}
