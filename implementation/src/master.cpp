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
}

master::~master()
{
    //delete our slaves
    for(int i=0; i<childCount; i++)
        delete slaves[i];
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

void master::tick(double dt)//do our tick first, then our loyal slaves
{
    hub::tick(dt);//tick us

    //give a child permission to act
    if(slaves[currentTransmitting]!=NULL)
        slaves[currentTransmitting]->permittedToTransmit = true;

    //move the index forward
    currentTransmitting++;
    if(currentTransmitting>=childCount)
        currentTransmitting = 0;

    for(int i=0; i<childCount; i++)
    {
        //BUGGY
        ((hub*) slaves[i])->tick(dt);//tick the slave
    }
}