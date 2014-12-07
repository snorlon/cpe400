#include "internet.h"
#include "ip.h"
#include "hub.h"
#include <time.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

bool keepRunning = true;
internet* theInternet = NULL;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::nanoseconds nanoseconds;

//program designed to be modular to integrate with visuals
int main(int argv, char* argc[])
{
    //seed stuff
    srand (time(NULL));

    //create the internet here
    theInternet = new internet(20);//temporarily hard-coded parameters

    Clock::time_point t0 = Clock::now();//set our clocks
    

    while(keepRunning)
    {
        //tick like a boss until time runs out
        //calc the time
        Clock::time_point t1 = Clock::now();
        nanoseconds ms = std::chrono::duration_cast<nanoseconds>(t1 - t0);
        double dt = ms.count();
        t0 = t1;

        theInternet->tick(dt);
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
