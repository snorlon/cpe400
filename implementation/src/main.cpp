#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "internet.h"
#include "ip.h"
#include "mac.h"
#include "hub.h"


bool keepRunning = true;
internet* theInternet = NULL;

//program designed to be modular to integrate with visuals
int main(int argv, char* argc[])
{
    int i;
	ip g;
	mac c;
	
	//seed stuff
    srand (time(NULL));

    //create the internet here
    theInternet = new internet(50);//temporarily hard-coded parameters

    while(keepRunning)
    {
        //for now, give up like a wuss on first loop
        keepRunning = false;
    }
	g.generate();
	c.generate();
	cout<<c.address;
	cin>>i;
    return 0;
}
