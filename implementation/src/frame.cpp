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

    operation = 0;
}

frame::frame(datagram* npayload, ip* originIP, ip* destIP, mac* locOrigin, mac* locDest, int noperation)
{
    payload = npayload;
    senderIP = originIP;
    destinationIP = destIP;
    senderMac = locOrigin;
    destinationMac = locDest;
    operation = noperation;

    next = NULL;
}

frame::~frame()
{

}

datagram* frame::strip()
{
    return payload;
}
