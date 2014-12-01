#ifndef IPH
#define IPH
#include <string>

using namespace std;

//ip address class
class ip
{
    public:
        int address[4];//4 integers 0-255 make up an ip
        ip* next; //purely for the registry

        ip();
        ~ip();

        bool generate();// make a new ip address
        bool equal(ip &address2);//return true if they are equal
        string printout();
        //may need other comparisons later
    private:
};

#endif
