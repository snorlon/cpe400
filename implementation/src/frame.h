//layer 2 - Data link

class frame
{
    public:
        mac* destination;
        mac* source;

        frame* next;//for queuing them

        frame();
        ~frame();

        datagram* strip();//bring out that sexy packet to work with, returns null if none for some reason
    private:

        datagram* payload;//just some data to keep in here

};