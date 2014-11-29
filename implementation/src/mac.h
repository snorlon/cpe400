#ifndef MACH
#define MACH

//mac address class
class mac
{
    public:
        char address[48];//the 48 bits to an address

        mac();
        ~mac();

        bool generate();// make a new mac address
        bool equal(mac &address);//return true if they are equal
        //may need other comparisons later
    private:
};
#endif