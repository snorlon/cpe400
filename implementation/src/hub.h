#ifndef HUBH
#define HUBH
#include <cstddef>
#include <string>
#include "mac.h"

using namespace std;

class ip;
class link;
class hub
{
    public:
        static const int HUB_TYPE = 0;
        static const int SWITCH_TYPE = 1;
        static const int ROUTER_TYPE = 2;

        int id;

        hub* next;//for linked list uses
        int type;//for tracking what type of device this is
        int linkCount;

        ip* ipAddress;
        mac macAddress;

        link* links;

        hub();
        ~hub();

        string typeString();
        bool addLink(link* newLink);
        bool linkTo(hub* destination);
        void giveIP(ip* newIP);
    private:
};

#endif
