#include "mac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

mac::mac()
{
    //default all of the values to 0
    for(int i=0;i<12;i++)
        address[i] = 0;
}

mac::~mac()
{
    //what do?
}

bool mac::generate()
{
    bool bits[48];
    for(int i=0;i<48;i++)
    {
        if(rand() % 2 == 0)
            bits[i] = true;
        else
            bits[i] = false;
    }
    for(int i=0;i<12;i++)
    {
        //determine the characters
        int value = 0;
        address[i] = ' ';

        if(bits[i*4])
            value+= 8;
        if(bits[i*4 + 1])
            value+= 4;
        if(bits[i*4 + 2])
            value+= 4;
        if(bits[i*4 + 3])
            value+= 4;

        //create the character from it
        if(value<=9 && value>=0)
            address[i] = '0'+value;
        else
            address[i] = 'A'+value-10;
    }

	//Not sure what to use this for
    return false;
}

string mac::printout()
{
    string output = "";

    for(int i=0;i<12;i++)
    {
        output = output + address[i];

        if((i+1)%2 == 0 && i<10)
            output = output+"-";
    }

    return output;
}

bool mac::equal(mac &address2)
{
    for(int i=0;i<12;i++)
    {
        if(address[i]!=address2.address[i])
            return false;
    }

    return true;
}
