#include "ip.h"

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
}

bool ip::generate()
{
    //empty for now
    return false;
}

bool ip::equal(ip &address2)
{
    //compare to see if equal
    for(int i=0; i<4;i++)
    {
        //return false if any do not match
        if(address[i]!=address2.address[i])
            return false;
    }

    //otherwise return true
    return true;
}