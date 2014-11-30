#ifndef LINKH
#define LINKH
#include <cstddef>
#include <string>

using namespace std;

class hub;
class link
{
    public:

        hub* start;
        hub* end;
        link* next;//for linked list uses
        int weight;//the weight or distance or cost of the link

        link();
        link(hub* nStart, hub* nEnd);
        ~link();
    private:
};

#endif
