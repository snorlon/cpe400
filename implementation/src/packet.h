//layer 4 - transport layer

class packet
{
    public:
        mac* destination;
        mac* source;

        packet* next;//for queuing them

        datagram();
        ~datagram();

        datagram* strip();//bring out that sexy datagram to work with, returns null if none for some reason
    private:

        datagram* payload;//just some data to keep in here

};
