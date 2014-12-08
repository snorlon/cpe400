#include "internet.h"
#include "ip.h"
#include "hub.h"
#include <time.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

bool keepRunning = true;
internet* theInternet = NULL;
long int cycles = 0;
long int cycleLimit = 0;

int deviceCount = 10;
int masterCount = 5;
int seed = 0;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::nanoseconds nanoseconds;

//program designed to be modular to integrate with visuals
int main(int argv, char* argc[])
{

    //check console for data
    //parameters are: ./Project DEVICECOUNT MASTERCOUNT SEED CYCLELIMIT
    //All parameters are optional, defaults provided

    if(argv>1)
        deviceCount = atoi(argc[1]);

    if(argv>2)
        masterCount = atoi(argc[2]);

    if(argv>3)
        seed = atoi(argc[3]);

    if(argv>4)
        cycleLimit = atoi(argc[4]);

    //seed stuff
    if(seed == 0)
        srand (time(NULL));
    else
        srand (seed);

    //create the internet here
    theInternet = new internet(deviceCount, masterCount);//temporarily hard-coded parameters

    Clock::time_point t0 = Clock::now();//set our clocks

    //init the internet
    theInternet->init();
    

    while(keepRunning)
    {
        //tick like a boss until time runs out
        //calc the time
        Clock::time_point t1 = Clock::now();
        nanoseconds ms = std::chrono::duration_cast<nanoseconds>(t1 - t0);
        double dt = ms.count();
        t0 = t1;

        theInternet->tick(dt);

        cycles++;

        //stop running if we hit a cap
        if(cycleLimit > 0 && cycles > cycleLimit)
            keepRunning = false;
    }

    //show devices on end
    cout<<"There are "<<theInternet->countDevices(hub::HUB_TYPE)<<" hubs connected."<<endl;
    cout<<"There are "<<theInternet->countDevices(hub::SWITCH_TYPE)<<" switches connected."<<endl;
    cout<<"There are "<<theInternet->countDevices(hub::ROUTER_TYPE)<<" normal routers connected."<<endl;
    cout<<"There are "<<theInternet->countDevices(hub::MASTER_TYPE)<<" master routers connected."<<endl;

    cout<<"Device 7 is a "<<theInternet->getDevice(6)->typeString()<<endl;

    //lets delete the internet! yay!
    delete theInternet;

    return 0;
}
