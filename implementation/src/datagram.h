//layer 3 - Network

class datagram
{
    public:
        ip* destination;
        ip* source;

        datagram* next;//for queuing them

        datagram();
        ~datagram();

        segment* strip();//bring out that sexy segment to work with, returns null if none for some reason
    private:

        segment* payload;//just some data to keep in here

};
