#ifndef HUBH
#define HUBH
#include <cstddef>
#include <string>
#include "mac.h"
#include "frame.h"

using namespace std;

class internet;
class ip;
class link;
class hub
{
    public:
        static const int HUB_TYPE = 0;
        static const int SWITCH_TYPE = 1;
        static const int ROUTER_TYPE = 2;

        double messageGenThreshold;

        int id;

        hub* next;//for linked list uses
        int type;//for tracking what type of device this is
        int linkCount;

        ip* ipAddress;
        mac macAddress;
        internet* parent;

        link* links;

        frame* outgoing;
        frame* incoming;

        bool waiting;

        hub();
        ~hub();

        string typeString();
        bool addLink(link* newLink);
        bool linkTo(hub* destination);
        void giveIP(ip* newIP);
        frame* generateMessage();//generate a message to send
        void tick(double dt);
        void sendFrame(frame* newData);//toss a frame into our outgoing queue
        void broadcast(int operation, frame* payload);
    private:
};

#endif
