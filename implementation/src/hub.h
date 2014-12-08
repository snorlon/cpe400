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
class netlink;
class hub
{
    public:
        static const int HUB_TYPE = 0;
        static const int SWITCH_TYPE = 1;
        static const int ROUTER_TYPE = 2;
        static const int MASTER_TYPE = 3;
        static const int SLAVE_TYPE = 4;

        double messageGenThreshold;

        routingEntry* routingTable;

        int id;

        hub* next;//for linked list uses
        int type;//for tracking what type of device this is
        int linkCount;

        ip* ipAddress;
        mac macAddress;
        internet* parent;

        netlink* links;

        frame* outgoing;
        frame* incoming;

        hub();
        virtual ~hub();

        virtual void init();//initialize the device for operation

        bool storeEntry(routingEntry* midpoint, routingEntry* targetEntry);//attempt to store the given entry into the routing table and replace if existent
        virtual void generateRoutingInfo();//run this N times, N being the number of routers

        virtual string typeString();//get the name of the device, EX: Hub, Router, Switch
        bool addLink(netlink* newLink);//add an existing link to our links list
        bool linkTo(hub* destination);//create a link to a device
        void giveIP(ip* newIP);//assign the router an ip
        virtual void tick(double dt, int outputlevel);//all stuff happens in here, message generation and frame processing
        void sendFrame(frame* newData);//toss a frame into our outgoing queue
        void recieveFrame(frame* newData);//recieve a frame from someone into our incoming queue
        void broadcast(int operation, frame* payload);//unused, can be used, TO FINISH
        int canReach(ip* address);//determine the distance to the target address from us, default is 999999
        void storeRouting(routingEntry* routingData);//attempts to store the routing info we just found
        routingEntry* acquireEntry(ip* dest);//get the routing table entry for the particular ip address
        void forwardFrame(frame* package);//send an already generated frame to the mac address on it (if we have it), if not, use IP to find it out, TO FINISH: IP TO MAC CONVERSION
        virtual void processOutgoing();//virtual so that slaves can override it
        void processIncoming();
        void generateMessage();//generates a random message to a random someone somewhere
    private:
};

#endif
