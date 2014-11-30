#include "hub.h"
#include "frame.h"
//switch should just be a better hub

class switchDevice: public hub
{
    public:
        hub* neighbors;//linked list of neighbors this node has that it is "connected" to physically

        frame* bufferIncoming;
        frame* bufferOutgoing;//Needed?

        switchDevice();
        ~switchDevice();

        void tick(float dt);//do all actions per tick here, this is for integration purposes
        bool transmit(ip* destination);//generate a random transmission, can give it an IP address to override the random part, bool if fail
        bool connect(hub* neighbor);//physically connect to a new neighbor, bool if fail

    private:
};
