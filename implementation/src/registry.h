#ifndef IPREGH
#define IPREGH

class ip;
class registry
{
    public:
        ip* available;
        int ipCount;

        registry();//generate all available IP addresses here
        ~registry();

        bool returnIP(ip* returnedIP);
        ip* getIP(int index);
        ip* getRandomIP();
    private:

};


#endif
