#include "ip.h"
#include <iostream>

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

string ip::printout()
{
    string returnstring = "";
    returnstring+= to_string(address[0]);
    returnstring+= ".";
    returnstring+= to_string(address[1]);
    returnstring+= ".";
    returnstring+= to_string(address[2]);
    returnstring+= ".";
    returnstring+= to_string(address[3]);

    return returnstring;
}


bool operator== (ip &ip1, ip &ip2)
{
    for(int i=0; i<4; i++)
        if(ip1.address[i] != ip2.address[i])
            return false;

    return true;
}


bool operator!= (ip &ip1, ip &ip2)
{
    return !(ip1==ip2);
}
