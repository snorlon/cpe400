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

    incoming = NULL;
    outgoing = NULL;

    waiting = false;
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
    while(outgoing!=NULL)
    {
        frame* temp = outgoing;
        outgoing = outgoing->next;
        delete temp;
    }
    while(incoming!=NULL)
    {
        frame* temp = incoming;
        incoming = incoming->next;
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
    if(rand() % int(messageGenThreshold) == 0 && !waiting)
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
        datagram* newDatagram = new datagram(newPacket, ipAddress, destination->ipAddress, 3);//TTL of 3 for now

        //enclose THAT in a frame
        //need to find the appropriate mac destination for it, leave it NULL for now
        frame* newFrame = new frame(newDatagram, ipAddress, destination->ipAddress, &macAddress, NULL, 1);//op of 1 for now

        //send it on its merry way
        //which way is that??
        //add it to outgoing queue for now
        sendFrame(newFrame);
    }

    //process incoming here

    

    bool processed = false;
    //now try to process the frontmost outgoing message and send it along
    if(outgoing!=NULL)
    {
        //this means we need to find out if we know where it's going, and find out if we don't know
            //first, check if it's right next to us
        link* neighbors = links;
        while(neighbors!=NULL && !processed)
        {
            if(neighbors->end->ipAddress == outgoing->destinationIP)
            {
                //they're next to us, so move the message to them

                cout<<"Message DIRECTLY delivered to "<<outgoing->destinationIP->printout()<<" from "<<neighbors->end->ipAddress->printout()<<"!"<<endl;

                //remove the node

                //clean up
                processed = true;
            }
            neighbors=neighbors->next;
        }
            //check our routing table of IPs and paths
        //broadcast for reactive DSR to find out where they are, wait for the response, may take a while
        //for simulation purposes, we ignore error change, and simply wait until it is back to us while keeping the shortest path to destination in routing table
        //we still process incoming while waiting, and exit waiting state when what we want arrives and we can send our frame
    }
}

void hub::sendFrame(frame* newData)
{
    if(outgoing == NULL)
    {
        outgoing = newData;
    }
    else
    {
        frame* iterator = outgoing;
        while(iterator->next != NULL)
            iterator = iterator->next;

        iterator->next = newData;
    }
}
