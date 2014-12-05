#include "frame.h"

//layer 2 - Data link

frame::frame()
{
    senderIP = NULL;
    destinationIP = NULL;
    senderMac = NULL;
    destinationMac = NULL;

    payload = NULL;

    next = NULL;
}

frame::~frame()
{

}

datagram* frame::strip()
{
    return NULL;
}
