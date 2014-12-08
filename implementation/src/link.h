#ifndef LINKH
#define LINKH
#include <cstddef>
#include <string>

using namespace std;

class hub;
class netlink
{
    public:

        hub* start;
        hub* end;
        netlink* next;//for linked list uses
        int weight;//the weight or distance or cost of the link

        netlink();
        netlink(hub* nStart, hub* nEnd);
        ~netlink();
    private:
};

#endif
