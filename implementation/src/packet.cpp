#include "packet.h"
#include "ip.h"

//layer 4 - Transport


packet::packet()
{
    destination = NULL;
    source = NULL;

    data = "ERROR";

    next = NULL;
}

packet::packet(string newData, ip* origin, ip* dest)
{
    destination = dest;
    source = origin;

    data = newData;

    next = NULL;
}

packet::~packet()
{

}
