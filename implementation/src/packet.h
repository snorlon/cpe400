#ifndef PACKETH
#define PACKETH
#include <cstddef>
#include <string>

using namespace std;

//layer 4 - transport layer

class ip;
class packet
{
    public:
        ip* destination;
        ip* source;

        packet* next;//for queuing them

        string data;

        //Protocol always UDP so no need to state it, it is assumed
        //Length assumed not needed
        //Checksum not used
        int sourcePort;//unused?
        int destinationPort;

        packet();
        packet(string newData, ip* origin, ip* dest);
        ~packet();
    private:

};

#endif
