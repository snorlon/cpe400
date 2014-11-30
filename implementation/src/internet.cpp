#include "internet.h"

internet::internet(int numDevices)
{
    connectedDevices = NULL;

    //lets make an internet!
    //YAY!

    //for each device, we should create a new random device and randomly add it to the network
    for(int i=0;i<numDevices;i++)
    {
        //randomly decide what to generate
        int roll = rand() % 5;

        if(roll<=0)//hub
        {
            cout<<"HUB generated!"<<endl;

            hub* newDevice = new hub();
            connectDevice(newDevice);
        }
        else if(roll<=3)//router
        {
            cout<<"ROUTER generated!"<<endl;

            hub* newDevice = new router();
            connectDevice(newDevice);
        }
        else if(roll<=4)//switch
        {
            cout<<"SWITCH generated!"<<endl;

            hub* newDevice = new switchDevice();
            connectDevice(newDevice);
        }
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

bool internet::connectDevice(hub* device)
{
    if(device!=NULL)
        connectedDeviceCount++;
    else
        return false;

    cout<<"Device mounted onto network!"<<endl;

    if(connectedDevices == NULL)
    {
        connectedDevices = device;
        return true;
    }
    else
    {
        hub* iterator = connectedDevices;
        while(iterator->next!=NULL)
            iterator = iterator->next;

        iterator->next = device;
        return true;
    }
}
