#ifndef IPH
#define IPH
#include <string>
#include "registry.h"

using namespace std;

//ip address class
class ip
{
    public:
        int address[4];//4 integers 0-255 make up an ip
        ip* next; //purely for the registry

        registry* ipRegistry;

        ip();
        ~ip();

        bool generate();// make a new ip address
        bool equal(ip &address2);//return true if they are equal
        string printout();
        //may need other comparisons later

    private:
};

bool operator== (ip &ip1, ip &ip2);
bool operator!= (ip &ip1, ip &ip2);

#endif
