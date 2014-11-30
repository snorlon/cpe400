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

    return 0;
}
