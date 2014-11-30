#include "internet.h"
#include "ip.h"
#include "hub.h"
#include <time.h>
#include <stdlib.h>

using namespace std;

bool keepRunning = true;
internet* theInternet = NULL;

//program designed to be modular to integrate with visuals
int main(int argv, char* argc[])
{
    //seed stuff
    srand (time(NULL));

    //create the internet here
    theInternet = new internet(50);//temporarily hard-coded parameters

    

    while(keepRunning)
    {
        //for now, give up like a wuss on first loop
        keepRunning = false;
    }

    //test counting devices
    cout<<"There are "<<theInternet->countDevices(hub::HUB_TYPE)<<" hubs connected."<<endl;
    cout<<"There are "<<theInternet->countDevices(hub::SWITCH_TYPE)<<" switches connected."<<endl;
    cout<<"There are "<<theInternet->countDevices(hub::ROUTER_TYPE)<<" routers connected."<<endl;

    cout<<"Device 7 is a "<<theInternet->getDevice(6)->typeString()<<endl;

    //lets delete the internet! yay!
    delete theInternet;

    return 0;
}
