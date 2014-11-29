#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "ip.h"



using namespace std;
ip::ip()
{
    //default all of the values to 0.0.0.0
    address[0] = 0;
    address[1] = 0;
    address[2] = 0;
    address[3] = 0;
}

ip::~ip()
{
    //what do?

	//Maybe set these to impossible values?
	address[0] = -1;
    address[1] = -1;
    address[2] = -1;
    address[3] = -1;

}

bool ip::generate()
{
    //empty for now
	
	//Replace current ip with new ip
	for(int i=0;i<4;i++)
	{
		address[i] = rand() % 256;
	}

	//Not sure what to use this for
    return false;
}

bool ip::equal(ip &address2)
{
    //compare to see if equal
    for(int i=0; i<4;i++)
    {
        //return false if any do not match
        if(address[i]!=address2.address[i])
		{
            return false;
		}
    }

    //otherwise return true
    return true;
}
