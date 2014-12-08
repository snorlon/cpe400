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
        void tick(float dt);
    private:
};

#endif
