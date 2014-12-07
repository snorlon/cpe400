#ifndef HUBH
#define HUBH
#include <cstddef>
#include <string>
#include "mac.h"
#include "frame.h"
#include "routing.h"
#include "datagram.h"

using namespace std;

class packet;
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

        routingEntry* routingTable;

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

        void init();

        void generateRoutingInfo();//run this N times, N being the number of routers

        string typeString();
        bool addLink(link* newLink);
        bool linkTo(hub* destination);
        void giveIP(ip* newIP);
        frame* generateMessage();//generate a message to send
        void tick(double dt);
        void sendFrame(frame* newData);//toss a frame into our outgoing queue
        void recieveFrame(frame* newData);//recieve a frame from someone
        void broadcast(int operation, frame* payload);
        void broadcastRREQ(ip* origin, ip* target, int TTL, routingEntry* routingInfo);
        int canReach(ip* address);
        void storeRouting(routingEntry* routingData, bool forward);//attempts to store the routing info we just found
        routingEntry* getEntry(ip* dest);
        void forwardFrame(frame* package);
    private:
};

#endif
