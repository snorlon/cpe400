#include "datagram.h"

//layer 3 - Network


datagram::datagram()
{
    destination = NULL;
    source = NULL;

    payload = NULL;

    next = NULL;
}

datagram::~datagram()
{

}

packet* datagram::strip()
{
    return NULL;
}
