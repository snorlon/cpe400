#include "ip.h"
#include "registry.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


registry::registry()
{
    available = NULL;
    ipCount = 0;

    for(int a=192;a<223;a++)//generate ips to use
    {
        for(int b=20;b<72;b++)
        {
            for(int c=10;c<39;c++)
            {
                for(int d=0;d<53;d++)
                {
                    if(b>0 || c>0 || d>0)//do not allow X.0.0.0
                    {
                        ip* newIP = new ip();
                        newIP->address[0] = a;
                        newIP->address[1] = b;
                        newIP->address[2] = c;
                        newIP->address[3] = d;

                        returnIP(newIP);//toss the ip into the registry
                    }
                }
            }
        }
    }
}

registry::~registry()
{
    //delete all remaining IPs
    while(available!=NULL)
    {
        ip* temp = available;
        available=available->next;
        delete temp;
    }
}

bool registry::returnIP(ip* returnedIP)
{
    ipCount++;

    returnedIP->next = available;
    available = returnedIP;

    return true;
}

ip* registry::getIP(int index)
{
    ip* iterator = available;
    while(index>0 && iterator!=NULL)
    {
        iterator = iterator->next;
        index--;
    }

    if(iterator!=NULL)
        ipCount--;

    return iterator;
}
ip* registry::getRandomIP()
{
    int index = rand() % ipCount;

    return getIP(index);
}
