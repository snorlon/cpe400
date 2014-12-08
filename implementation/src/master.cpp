#include "master.h"
#include <iostream>

using namespace std;

master::master()
{
    type = MASTER_TYPE;
    //default all slaves for now
    for(int i=0; i<slaveMax; i++)
        slaves[i] = NULL;
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
