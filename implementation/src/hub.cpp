#include "hub.h"
#include "link.h"
#include <iostream>
#include "ip.h"
#include "internet.h"
#include "packet.h"

using namespace std;

hub::hub()
{
    id = -1;//default ID

    ipAddress = NULL;

    routingTable = NULL;

    next = NULL;
    parent = NULL;
    type = HUB_TYPE;//default is 0 for hub

    //generate our mac address here
    macAddress.generate();
    macAddress.printout();

    //generate some random frequency data
    messageGenThreshold = (rand() % 100000000)+12000000;

    incoming = NULL;
    outgoing = NULL;
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

void hub::init()
{
    //by default store all of our neighbors in our routing table
    link* iterator = links;
    while(iterator!=NULL)
    {
        //generate a routing table entry for each neighbor
        routingEntry* newEntry = new routingEntry(iterator->end, iterator->end->ipAddress, &(iterator->end->macAddress), iterator->weight);
        storeRouting(newEntry);
        
        iterator = iterator->next;
    }
}

bool hub::storeEntry(routingEntry* midpoint, routingEntry* targetEntry)
{
    if(targetEntry->targetIP == ipAddress)
        return false;//can't link to ourself

    routingEntry* entries = routingTable;
    
    while(entries!=NULL)
    {
        if(entries->targetIP == targetEntry->device->ipAddress)
        {
            //update the weight, we need to know about better routes
            if(targetEntry->weight + midpoint->weight < entries->weight)
            {
                entries->weight = targetEntry->weight + midpoint->weight;
            }
            else
                return false;//not a better weight, don't bother

            return true;
        }

        entries = entries->next;
    }

    //add them if we don't have them
    routingEntry* newEntry = new routingEntry(targetEntry->device, targetEntry->targetIP, midpoint->nextHopMac, targetEntry->weight + midpoint->weight);
    storeRouting(newEntry);
    return true;
}

void hub::generateRoutingInfo()//**
{
    //check all connected entries for more connections to see if we can reach them
    routingEntry* iterator = routingTable;

    //check all elements in routing table
    while(iterator!=NULL)
    {
        //check all of their neighbors
        routingEntry* deviceLinks = iterator->device->routingTable;
        while(deviceLinks!=NULL)
        {
            if(deviceLinks->device!=this)
                //attempt to store this link
                storeEntry(iterator, deviceLinks);

            deviceLinks = deviceLinks->next;
        }

        iterator = iterator->next;
    }
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
        case MASTER_TYPE:
            return "Master";
            break;
        case SLAVE_TYPE:
            return "Slave";
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
        dt = dt*1.0;//to appease strict compiler, does nothing

        generateMessage();
        
    }

    processOutgoing();

    processIncoming();
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

void hub::recieveFrame(frame* newData)
{
    if(incoming == NULL)
    {
        incoming = newData;
    }
    else
    {
        frame* iterator = incoming;
        while(iterator->next != NULL)
            iterator = iterator->next;

        iterator->next = newData;
    }
}

int hub::canReach(ip* address)
{
    routingEntry* iterator = routingTable;
    while(iterator!=NULL)
    {
        if(*(iterator->targetIP) == *address)//return the distance from us to the target with our current routing info
        {
            return iterator->weight;
        }

        if(iterator->next != NULL)
            if(iterator->next == iterator)
                cout<<"FUCK"<<endl;

        iterator = iterator->next;
    }

    return 999999;//arbitrary, up as needed
}

void hub::storeRouting(routingEntry* newData)
{
    if(newData==NULL)
        return;//abort if no stuff to add to our routing

    newData->next = routingTable;
    routingTable = newData;
}

routingEntry* hub::acquireEntry(ip* dest)
{
    routingEntry* iterator = routingTable;
    while(iterator!=NULL)
    {
        if(*(iterator->targetIP) == *dest)
        {
        //cout<<"GIVING|"<<macAddress.printout()<<"|"<<iterator->nextHopMac->printout()<<"|"<<iterator->targetIP->printout()<<endl;
            return iterator;
        }

        iterator = iterator->next;
    }

    return iterator;
}

void hub::forwardFrame(frame* package)
{
    link* iterator = links;
    while(iterator != NULL)
    {
        if(&(iterator->end->macAddress) == package->destinationMac)
        {
            iterator->end->recieveFrame(package);
        }

        iterator = iterator->next;
    }
}

void hub::processIncoming()
{
    if(incoming!=NULL)
    {
        //process incoming here
        //pick the frame apart for what we want
        frame* currFrame = incoming;
        datagram* currDatagram = currFrame->strip();
        packet* currPacket = currDatagram->strip();
        bool throwaway = false;

        //check if the datagram TTL ran out
        if(currDatagram->TTL == 1)
        {
            //if so, we won't rebuild it, we throw it out
            throwaway = true;
            cout<<"EXPIRED Packet"<<endl;
        }
        //decide what to do with the info we found
        else if(currFrame->operation == 1)//a simple data delivery
        {
            //are we who they wanted to reach?
            if(currDatagram->destination == ipAddress)
            {
                cout<<"Message "<<currPacket->id<<" arrived! Thanks! "<<currPacket->data<<endl<<endl;
                throwaway = true;
            }
            //if we aren't, pass it on
            else
            {
                //send it on!
                routingEntry* entry = acquireEntry(currDatagram->destination);
                if(entry->nextHopMac == currFrame->senderMac)
                {
                    cout<<"REDUNDANCY"<<endl;
                }
                if(entry!=NULL)
                {
                    //create a new frame to send
                    datagram* newDatagram = new datagram(currPacket, currDatagram->source, currDatagram->destination, currDatagram->TTL-1);
                    frame* newFrame = new frame(newDatagram, currDatagram->source, currDatagram->destination, &macAddress, entry->nextHopMac, currFrame->operation);
                    sendFrame(newFrame);
                }
                else
                {
                    throwaway = true;//if we don't know where it is, dump it
                }
            }
        }
        else
        {
            //dump it
            throwaway = true;
        }

        //destroy the old frame and datagram and remove this from our incoming queue
        incoming = incoming->next;

        delete currFrame;
        delete currDatagram;
        if(throwaway)
        {
            delete currPacket;//changed for simulation purposes, dump and rebuild entirely each time
        }
    }
}

void hub::processOutgoing()
{
    bool processed = false;
    //now try to process the frontmost outgoing message and send it along
    if(outgoing!=NULL)
    {
        //check neighbors for next hop

        //hand it off to the next step in the chain
        link* neighbors = links;
        while(neighbors!=NULL && !processed)
        {
            if((neighbors->end->macAddress) == *(outgoing->destinationMac))
            {
                //they're next to us, so move the message to them

                cout<<"Message "<<outgoing->strip()->strip()->id<<" handed to "<<outgoing->destinationMac->printout()<<" from "<<macAddress.printout()<<"!"<<endl;

                //remove the frame
                frame* delivery = outgoing;
                outgoing = outgoing->next;
                delivery->next = NULL;

                //send it out
                neighbors->end->recieveFrame(delivery);

                //clean up
                processed = true;
            }
            //else
                //cout<<neighbors->end->macAddress.printout()<<"|"<<ournextHop->printout()<<"|"<<macAddress.printout()<<endl;
            neighbors=neighbors->next;
        }
    }
}

void hub::generateMessage()
{
    //grab a random device
    hub* destination = parent->randomDevice();

    if(!(*(destination->ipAddress)==*ipAddress))
    {

        //create a packet of data to send
        string message = "ABCDEFGHIJKLMNOP";
        for(int i=0; i<16;i++)
            message[i] = (rand() % 26)+'A';

        packet* newPacket = new packet(message, ipAddress, destination->ipAddress);

        cout<<"Message "<<newPacket->id<<" spawned! Send to IP "<<destination->ipAddress->printout()<<". Data:"<<message<<endl;

        //enclose it in a datagram
        datagram* newDatagram = new datagram(newPacket, ipAddress, destination->ipAddress, 500);//TTL of 3 for now

        //enclose THAT in a frame
        //need to find the appropriate mac destination for it, leave it NULL for now
        frame* newFrame = new frame(newDatagram, ipAddress, destination->ipAddress, &macAddress, acquireEntry(destination->ipAddress)->nextHopMac, 1);//op of 1 for now

        //send it on its merry way
        //which way is that??
        //add it to outgoing queue for now
        sendFrame(newFrame);
    }
}
