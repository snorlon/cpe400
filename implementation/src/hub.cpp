#include "hub.h"
#include "link.h"
#include <iostream>
#include "ip.h"
#include "internet.h"

using namespace std;

hub::hub()
{
    id = -1;//default ID

    ipAddress = NULL;

    next = NULL;
    parent = NULL;
    type = HUB_TYPE;//default is 0 for hub

    //generate our mac address here
    macAddress.generate();
    macAddress.printout();

    //generate some random frequency data
    messageGenThreshold = (rand() % 10000000)+12000000;
}

hub::~hub()
{
    //KILL ALL LINKS
    while(links!=NULL)
    {
        link* temp = links;
        links = links->next;
        delete temp;
    }

    if(ipAddress!=NULL)
        delete ipAddress;
}

string hub::typeString()
{
    switch(type)
    {
        case HUB_TYPE:
            return "Hub";
            break;
        case SWITCH_TYPE:
            return "Switch";
            break;
        case ROUTER_TYPE:
            return "Router";
            break;
    }
    return "Error";
}

bool hub::addLink(link* newLink)
{
    if(links == NULL)
    {
        links = newLink;
    }
    else
    {
        newLink->next = links;
        links = newLink;
    }

    linkCount++;
    return true;
}

bool hub::linkTo(hub* destination)
{
    //check if we have an existing link first
    link* iterator = links;
    while(iterator!=NULL)
    {
        if(iterator->end == destination)
            return false;//abort

        iterator=iterator->next;
    }

    //generate a random "normal" distance for it
    int distance = (rand() % 10)+1;

    //random outlier distance
    bool failed = false;
    while(!failed)
    {
        if(rand() % 2 == 0)
            distance++;
        else
            failed = true;
    }

    //create a new link to it and store it on both ends
    link* newLinkA = new link(this, destination);
    link* newLinkB = new link(destination, this);

    cout<<"   New link with distance "<<distance<<" from Device "<<id<<" to Device "<<destination->id<<"!"<<endl;

    newLinkA->weight = distance;
    newLinkB->weight = distance;

    addLink(newLinkA);
    destination->addLink(newLinkB);

    return true;
}

void hub::giveIP(ip* newIP)
{
    ipAddress = newIP;
}

void hub::tick(double dt)
{
    //do nothing for now
    if(rand() % int(messageGenThreshold) == 0)
    {
        //grab a random device
        hub* destination = parent->randomDevice();

        //create a packet of data to send
        string message = "ABCDEFGHIJKLMNOP";
        for(int i=0; i<16;i++)
            message[i] = (rand() % 26)+'A';

        cout<<"Message spawned! MAC:"<<destination->macAddress.printout()<<" IP:"<<destination->ipAddress->printout()<<" "<<message<<" "<<dt<<endl;

        packet* newPacket = new packet(message, ipAddress, destination->ipAddress);

        //enclose it in a datagram

        //enclose THAT in a frame

        //send it on its merry way

        //figure out how to get it there later, for now we just decide how to make the packet
    }
}
