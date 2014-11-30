#ifndef MACH
#define MACH
#include <iostream>

using namespace std;

//mac address class
class mac
{
    public:
        char address[12];//the 48 bits to an address

        mac();
        ~mac();

        bool generate();// make a new mac address
        string printout();
        bool equal(mac &address);//return true if they are equal
        //may need other comparisons later
    private:
};

#endif
