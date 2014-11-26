//layer 3 - Network
//this may be totally wrong as wikipedia is not being helpful and not downloading powerpoint to check just yet
//basically this should be whatever the layer 3 data is which may be a packet or it may be a segment, probably a packet
//if so what the hell is a segment

class packet
{
    public:
        mac* destination;
        mac* source;

        packet* next;//for queuing them

        datagram();
        ~datagram();

        segment* strip();//bring out that sexy segment to work with, returns null if none for some reason
    private:

        segment* payload;//just some data to keep in here

};
