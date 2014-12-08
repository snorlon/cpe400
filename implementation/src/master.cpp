#include "master.h"
#include <iostream>

using namespace std;

master::master()
{
    type = MASTER_TYPE;
    //default all slaves for now
    for(int i=0; i<slaveMax; i++)
        slaves[i] = NULL;

    currentTransmitting = 0;

    
    id = -1;//default ID

    ipAddress = NULL;

    routingTable = NULL;

    next = NULL;
    parent = NULL;

    //generate our mac address here
    macAddress.generate();
    macAddress.printout();

    //generate some random frequency data
    messageGenThreshold = (rand() % 10000000)+12000000;

    incoming = NULL;
    outgoing = NULL;
}

master::~master()
{
}

void master::init()
{
    //call router init
    hub::init();

    //generate the slaves and link them
    childCount = (rand() % (slaveMax-1))+1;
    for(int i=0; i<childCount; i++)
    {
        //generate new slaves
        slaves[i] = new slave();
        cout<<"Slave generated!"<<endl;

        //tell them who their daddy is
        slaves[i]->parent = parent;

        //give them an ip
        slaves[i]->giveIP(ipAddress->ipRegistry->getRandomIP());

        //link them to us
        linkTo(slaves[i]);

        //generate routing info to each
        routingEntry* newEntry = new routingEntry(this, ipAddress, &macAddress, 5);//we have a static weight for latency for whatever reason
        slaves[i]->storeRouting(newEntry);

        newEntry = new routingEntry(slaves[i], slaves[i]->ipAddress, &(slaves[i]->macAddress), 5);//we have a static weight for latency for whatever reason
        storeRouting(newEntry);
    }
}

void master::tick(double dt, int outputlevel)//do our tick first, then our loyal slaves
{
    hub::tick(dt, outputlevel);//tick us

    //give a child permission to act
    if(slaves[currentTransmitting]!=NULL)
        slaves[currentTransmitting]->permittedToTransmit = true;

    //move the index forward
    currentTransmitting++;
    if(currentTransmitting>=childCount)
        currentTransmitting = 0;

    for(int i=0; i<childCount; i++)
    {
        if(slaves[i]->permittedToTransmit && outputlevel <= 0)
            cout<<endl<<"*"<<macAddress.printout()<<" gives permission to transmit to the slave "<<slaves[i]->macAddress.printout()<<endl;

        slaves[i]->tick(dt, outputlevel);//tick the slave
    }
}

void master::generateRoutingInfo()
{
    //then for us
    hub::generateRoutingInfo();

    //do it for all of our slaves
    for(int i=0; i<childCount; i++)
    {
        slaves[i]->generateRoutingInfo();
    }
}
