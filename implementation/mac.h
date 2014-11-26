//mac address class
class mac
{
    public:
        char[48] address;//the 48 bits to an address

        mac();
        ~mac();

        bool generate();// make a new mac address
        bool equal(mac &address);//return true if they are equal
        //may need other comparisons later
    private:
};
