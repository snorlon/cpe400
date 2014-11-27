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
        }
        else if(roll<=3)//router
        {
            cout<<"ROUTER generated!"<<endl;
        }
        else if(roll<=4)//switch
        {
            cout<<"SWITCH generated!"<<endl;
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
