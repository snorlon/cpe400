#include "datagram.h"

//layer 3 - Network


datagram::datagram()
{
    destination = NULL;
    source = NULL;

    payload = NULL;

    next = NULL;
}

datagram::datagram(packet* npayload, ip* origin, ip* dest, int nTTL, int nid, int nfragment, bool fragFlag )
{
    payload = npayload;
    
    destination = dest;
    source = origin;

    next = NULL;

    id = nid;//for fragmenting, unused for now
    fragOffset = nfragment;
    flags[0] = fragFlag;
    TTL = nTTL;
}

datagram::~datagram()
{

}

packet* datagram::strip()
{
    return payload;
}
