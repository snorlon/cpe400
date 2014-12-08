#ifndef MASTERH
#define MASTERH
#include "hub.h"
#include "router.h"
#include "slave.h"
#include <cstddef>

const int slaveMax = 5;

class master: public router
{
    public:
        slave* slaves[slaveMax];//we have up to 5 possible slaves to manage
        int childCount;//number of slaves actually held
        int currentTransmitting;//the index of the slave that is given permission to transmit

        master();
        ~master();

        void init();
        void tick(double dt, int outputlevel);
        void generateRoutingInfo();//overridden to factor in slaves
    private:
};

#endif
