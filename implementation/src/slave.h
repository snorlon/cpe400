#ifndef SLAVEH
#define SLAVEH
#include "router.h"

class slave: public router
{
    public:
        bool permittedToTransmit;

        slave();
        ~slave();

        void processOutgoing();
    private:
};

#endif
