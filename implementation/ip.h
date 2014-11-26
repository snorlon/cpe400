//mac address class
class ip
{
    public:
        int[4] address;//4 integers 0-255 make up an ip

        ip();
        ~ip();

        bool generate();// make a new ip address
        bool equal(ip &address);//return true if they are equal
        //may need other comparisons later
    private:
};
