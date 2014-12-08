#ifndef MASTERH
#define MASTERH
#include "router.h"
#include "slave.h"
#include <cstddef>

const int slaveMax = 5;

class master: public router
{
    public:
        slave* slaves[slaveMax];//we have up to 5 possible slaves to manage
        int childCount;//number of slaves actually held

        master();
        ~master();

        void init();
    private:
};

#endif
