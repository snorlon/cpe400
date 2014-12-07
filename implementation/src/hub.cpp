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

void hub::init()
{
    //by default store all of our neighbors in our routing table
    link* iterator = links;
    while(iterator!=NULL)
    {
        //generate a routing table entry for each neighbor
        routingEntry* newEntry = new routingEntry(iterator->end->ipAddress, &(iterator->end->macAddress), iterator->weight);
        storeRouting(newEntry, true);
        
        iterator = iterator->next;
    }
}

void hub::generateRoutingInfo()
{
    //check all connected entries for more connections to see if we can reach them
    routingEntry* iterator = routingTable;

    //check all elements in routing table
    while(iterator!=NULL)
    {
        //check all of their neighbors to see if we have them
            //if we do not, add them
        //if we do, check if they're closer than our current knowledge
            //if they are, replace our data for them
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
        dt = dt*1.0;
        //grab a random device
        hub* destination = parent->randomDevice();

        if(!(*(destination->ipAddress)==*ipAddress))
        {

            //create a packet of data to send
            string message = "ABCDEFGHIJKLMNOP";
            for(int i=0; i<16;i++)
                message[i] = (rand() % 26)+'A';

            cout<<"Message spawned! MAC:"<<destination->macAddress.printout()<<" IP:"<<destination->ipAddress->printout()<<" "<<message<<" |"<<ipAddress->printout()<<endl;

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
    }

    

    bool processed = false;
    //now try to process the frontmost outgoing message and send it along
    if(outgoing!=NULL)
    {
        //this means we need to find out if we know where it's going, and find out if we don't know
            //check neighbors for next hop
        mac* ournextHop = NULL;
        routingEntry* entry = getEntry(outgoing->destinationIP);

        //check each of our routing table entries
        if(entry!=NULL)
        {
            ournextHop = entry->nextHopMac;
        }

        //if we found who we're sending to
        if(ournextHop!=NULL)
        {
            outgoing->destinationMac = ournextHop;

            //hand it off to the next step in the chain
            link* neighbors = links;
            while(neighbors!=NULL && !processed)
            {
                if((neighbors->end->macAddress) == *ournextHop)
                {
                    //they're next to us, so move the message to them

                    cout<<"Message handed to "<<outgoing->destinationMac->printout()<<" from "<<macAddress.printout()<<"|"<<outgoing->id<<"!"<<endl;

                    //remove the node
                    frame* temp = outgoing;
                    outgoing = outgoing->next;
                    delete temp;

                    //clean up
                    processed = true;
                }
                //else
                    //cout<<neighbors->end->macAddress.printout()<<"|"<<ournextHop->printout()<<"|"<<macAddress.printout()<<endl;
                neighbors=neighbors->next;
            }
        }
        else if(!waiting)//if not...
        {
            //broadcast for reactive DSR to find out where they are, wait for the response, may take a while
            //for simulation simplicity purposes, we ignore errors in transmission, and simply wait until it is back to us while keeping the shortest path to destination in routing table
            broadcastRREQ(ipAddress, outgoing->destinationIP, 8, NULL);//we have no routing info yet and TTL of 8 is not specific
            cout<<"Router "<<macAddress.printout()<<" is now waiting for routing info."<<endl;

            waiting = true;
        }
    }

    //we still process incoming while waiting, and exit waiting state when what we want arrives and we can send our frame
    //handle 5 at a time
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
        }

        //decide what to do with the info we found
        //case for RREQ table building
        if(currFrame->operation == 3)
        {
            //attempt to store routing data
            storeRouting(currFrame->routingData,true);

                    //cout<<"!!!"<<macAddress.printout()<<" from "<<incoming->senderMac->printout()<<"!"<<endl;
            //are we who they wanted to reach?
            if(currDatagram->destination == ipAddress)
            {
                //send it back!
                routingEntry* entry = getEntry(currDatagram->source);
                if(entry!=NULL)
                {
                    //cout<<"Responding to RREQ! "<<currFrame->senderMac->printout()<<"|"<<entry->nextHopMac->printout()<<"|"<<currDatagram->source->printout()<<endl;
//if(currDatagram->source!=currFrame->senderIP)
                //cout<<"RESPONDING!"<<currFrame->id<<dt<<endl;  
                    //cout<<"SHARING THE LOVE"<<endl;
                    packet* newPacket = new packet();
                    datagram* newDatagram = new datagram(newPacket, ipAddress, currDatagram->source, 999999);
                    frame* newFrame = new frame(newDatagram, ipAddress, currDatagram->source, &macAddress, entry->nextHopMac, 4, currFrame->routingData);//lets use 4 for a RREQ response
                    sendFrame(newFrame);
                    throwaway = true;
                }
                
            }
            //check if the routing data does not have us in it
            else if(!currFrame->routingData->containsIP(ipAddress))
            {

                //check if we can give them what they want in terms of info
                routingEntry* entry = getEntry(currDatagram->destination);

                if(entry == NULL)//if we can't, broad ourselves to find out where it is
                {
                    broadcastRREQ(currDatagram->source, currDatagram->destination, 8, currFrame->routingData);
                    //cout<<"SHARING THE LOVE"<<endl;
                }
                else//otherwise, append on our routing info so that they can just send it to us to handle
                {
                    packet* newPacket = new packet();
                    datagram* newDatagram = new datagram(newPacket, currDatagram->source, currDatagram->destination, 999999);
                    frame* newFrame = new frame(newDatagram, currDatagram->source, currDatagram->destination, &macAddress, entry->nextHopMac, 3, currFrame->routingData);//lets use 3 for a RREQ frame
                    forwardFrame(newFrame);
                    throwaway = true;
                }
            }
            //if it does, we ignore it, it's a lamo we don't want
            else
                throwaway = true;
        }
        //RREP
        else if(currFrame->operation == 4)
        {
            storeRouting(currFrame->routingData,false);
            //are we who they wanted to reach?
            if(currDatagram->destination == ipAddress)
            {
                //let it get dumped
                cout<<"THANK YOU!"<<endl;  
                throwaway = true;    
                waiting = false;          
            }
            else//otherwise, rebuild it and send it along
            {
                //send it on!
                cout<<"WUT!"<<dt<<endl;  
                routingEntry* entry = getEntry(currDatagram->destination);
                if(entry!=NULL)
                {
                    cout<<"Pass it on!"<<endl;
                    //cout<<"SHARING THE LOVE"<<endl;
                    packet* newPacket = new packet();
                    datagram* newDatagram = new datagram(newPacket, currDatagram->source, currDatagram->destination, 999999);
                    frame* newFrame = new frame(newDatagram, currDatagram->source, currDatagram->destination, &macAddress, entry->nextHopMac, 4, currFrame->routingData);//lets use 4 for a RREP response
                    sendFrame(newFrame);
                    throwaway = true;
                }
                else
                    cout<<"UH OH"<<endl;
            }
        }
        else
            cout<<currFrame->operation<<endl;

        //rebuild the frame and send it on its way

        //ditch the frame and use what we just got

        //destroy the old frame and datagram and remove this from our inbox
        if(throwaway)
        {
            incoming = incoming->next;

            delete currPacket;//changed for simulation purposes, dump and rebuild entirely each time

            delete currFrame;
            delete currDatagram;
        }
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


void hub::broadcastRREQ(ip* origin, ip* target, int TTL, routingEntry* routingInfo)
{

    //we send off a broadcast to the target IP for each of our local links
    link* iterator = links;
    while(iterator!=NULL)
    {
        routingEntry* nroutingInfo = new routingEntry(ipAddress, &macAddress, iterator->weight, routingInfo);

        packet* newPacket = new packet();
        datagram* newDatagram = new datagram(newPacket, origin, target, TTL);
        frame* newFrame = new frame(newDatagram, origin, target, &macAddress, &(iterator->end->macAddress), 3, nroutingInfo);//lets use 3 for a RREQ frame

        iterator->end->recieveFrame(newFrame);

        iterator = iterator->next;
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

void hub::storeRouting(routingEntry* newData, bool forward)
{
    if(newData==NULL)
        return;//abort if no stuff to add to our routing

    int weightSum = 0;
    //check attached routing info to see if we can use it
    routingEntry* endCondition = NULL;
    routingEntry* startCondition = newData;
    mac* adjacentMac = NULL;

    if(!forward)//we need to reverse our checking if we are rebuilding from the back
    {
        endCondition = NULL;
        startCondition = newData;
        if(startCondition!=NULL)
            while(startCondition->next != NULL)
                startCondition = startCondition->next;
    }
    routingEntry* iterator = startCondition;

    //establish the nearest routing mac address to reach it, and use that for the mac in the routing table
    //if it came forward due to being a type 3 message, then we take the frontmost one for all macs
    //if not, we take the one just before us in the routing data and use it for all
    if(forward)
    {
        //just pull the forward-most one for all of them as it is by default nearest
        adjacentMac = newData->nextHopMac;
    }
    else
    {
        //pull the one that is just before us for the reverse path, abort when we pass it
        routingEntry* iterator4 = newData;
        while(iterator4!=NULL && iterator4->next!=NULL && *(iterator4->next->nextHopMac) != macAddress)
            iterator4 = iterator4->next;

        if(iterator4!=NULL)
            adjacentMac = iterator4->nextHopMac;
    }

    while(iterator!=endCondition)
    {
        //calc distance to it through its pathway
        weightSum+=iterator->weight;

        if(!(iterator->targetIP==ipAddress))
        {
            int cr = canReach(iterator->targetIP);
            //is it closer than us
            if(cr > weightSum )
            {

                //store it if so
                if(cr == 999999)
                {
                    routingEntry* newEntry = new routingEntry(iterator);
    
                    newEntry->weight = weightSum;
                    newEntry->next = routingTable;
                    newEntry->nextHopMac = adjacentMac;
                    routingTable = newEntry;

                    return;
                }
                else
                {

                    //remove the existing
                    routingEntry* iterator2 = routingTable;

                    while(iterator2!=NULL)
                    {
                        if(iterator2->targetIP == iterator->targetIP)//found it
                        {
                            iterator2->weight = weightSum;
                            iterator2->nextHopMac = iterator->nextHopMac;
                        }

                        iterator2 = iterator2->next;
                    } 



                    routingEntry* newEntry = new routingEntry(iterator);
                    newEntry->weight = weightSum;
                    newEntry->next = routingTable;
                    newEntry->nextHopMac = adjacentMac;
                    routingTable = newEntry;

                    return;
                }

            }
        }

        //fancy linked list forward and backward stuff to figure it out
        if(forward)
            iterator = iterator->next;
        else
        {
            routingEntry* iterator3 = newData;
            if(iterator == newData)
                iterator = NULL;
            else
            {
                while(iterator3->next != iterator)
                    iterator3 = iterator3->next;

                iterator = iterator3;
            }
        }
    }
}

routingEntry* hub::getEntry(ip* dest)
{
cout<<"A"<<endl;
cout<<"__________________"<<endl;
    routingEntry* iterator2 = routingTable;
    while(iterator2!=NULL)
    {
        cout<<iterator2->nextHopMac->printout()<<"|"<<iterator2->targetIP->printout()<<endl;

        iterator2 = iterator2->next;
    }
cout<<"_"<<endl;
    link* iterator3 = links;
    while(iterator3!=NULL)
    {
        cout<<iterator3->end->macAddress.printout()<<"|"<<iterator3->end->ipAddress->printout()<<endl;

        iterator3 = iterator3->next;
    }
cout<<"__________________"<<endl;

    routingEntry* iterator = routingTable;
    while(iterator!=NULL)
    {
        if(*(iterator->targetIP) == *dest)
        {
            //cout<<iterator->nextHopMac->printout()<<"|"<<iterator->targetIP->printout()<<endl;
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
