#include "internet.h"

internet::internet(int numDevices, int masterCount)
{
    connectedDevices = NULL;

    //lets make an internet!
    //YAY!

    //for each device, we should create a new random device and randomly add it to the network
    for(int i=0;i<numDevices;i++)
    {
        //randomly decide what to generate
        int roll = rand() % 5;
        roll = 3;//just always make a router, but allow hubs and switches if desired
        hub* newDevice = NULL;

        if(roll<=0)//hub
        {
            cout<<"HUB generated!"<<endl;

            newDevice = new hub();
        }
        else if(roll<=3)//router
        {
            cout<<"ROUTER generated!"<<endl;

            newDevice = new router();
        }
        else if(roll<=4)//switch
        {
            cout<<"SWITCH generated!"<<endl;

            newDevice = new switchDevice();
        }

        //give them an IP
        ip* newIP = ipRegistry.getRandomIP();
        newDevice->giveIP(newIP);

        cout<<"IP address of:  "<<newIP->printout()<<endl;

        connectDevice(newDevice);
    }

    //generate masters, they'll create their own slaves
    for(int i=0;i<masterCount;i++)
    {
        hub* newDevice = NULL;

        cout<<"MASTER router generated!"<<endl;
        newDevice = new master();

        //give them an IP
        ip* newIP = ipRegistry.getRandomIP();
        newDevice->giveIP(newIP);

        cout<<"IP address of:  "<<newIP->printout()<<endl;

        connectDevice(newDevice);
    }
}

internet::~internet()
{
    //destroy the internet
    while(connectedDevices!=NULL)
    {
        hub* device = connectedDevices;
        connectedDevices = connectedDevices->next;
        delete device;
    }
}

void internet::init()
{

    hub* iterator = connectedDevices;

    //init the internet
    while(iterator!=NULL)
    {
        iterator->init();

        iterator = iterator->next;
    }

    //generate routing info
    for(int i=0; i<connectedDeviceCount;i++)
    {
        iterator = connectedDevices;
        while(iterator!=NULL)
        {
            iterator->generateRoutingInfo();

            iterator = iterator->next;
        }
    }
}

bool internet::connectDevice(hub* device)
{
    if(device==NULL)
        return false;

    device->id = connectedDeviceCount;
    device->parent = this;

    //give it a random link
    if(connectedDeviceCount > 0) // don't try to link the first node please
    {
        hub* rDevice = randomDevice();
        device->linkTo(rDevice);

        for(int i=0;i<5;i++)//random bonus links
        {
            if(rand() % 2 == 0)//50% chance to get another link, run until limit
            {
                rDevice = randomDevice();
                device->linkTo(rDevice);
            }
            else
                break;
        }
    }

    connectedDeviceCount++;

    cout<<"   Device "<<device->id<<" mounted onto network!"<<endl<<endl;

    if(connectedDevices == NULL)
    {
        connectedDevices = device;
    }
    else
    {
        hub* iterator = connectedDevices;
        while(iterator->next!=NULL)
            iterator = iterator->next;

        iterator->next = device;
    }

    return true;
}

hub* internet::getDevice(int index)
{
    hub* iterator = connectedDevices;

    while(index>0&&iterator!=NULL)
    {
        iterator=iterator->next;
        index--;
    }

    return iterator;
}

hub* internet::randomDevice()
{
    return getDevice(rand() % connectedDeviceCount);
}

int internet::countDevices(int type)
{
    int count = 0;

    hub* iterator = connectedDevices;
    while(iterator!=NULL)
    {
        if(type == iterator->type)
            count++;

        iterator=iterator->next;
    }

    return count;
}

void internet::tick(double dt)
{
    //tick each hub
    hub* iterator = connectedDevices;
    while(iterator!=NULL)
    {
        iterator->tick(dt);

        iterator=iterator->next;
    }
}
