#ifndef HUBH
#define HUBH
#include <cstddef>

class hub
{
    public:
        hub* next;//for linked list uses
        int type;//for tracking what type of device this is

        hub();
        ~hub();
    private:
};

#endif
