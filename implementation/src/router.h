//routers should just be a better hub

class router: public hub
{
    public:
        routerNode* neighbors;//linked list of neighbors this node has that it is "connected" to physically

        frame* bufferIncoming;
        frame* bufferOutgoing;//Needed?

        router();
        ~router();

        void tick(float dt);//do all actions per tick here, this is for integration purposes
        bool transmit(ip* destination);//generate a random transmission, can give it an IP address to override the random part, bool if fail
        bool connect(router* neighbor);//physically connect to a new neighbor, bool if fail

    private:
};
