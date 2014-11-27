#ifndef IPH
#define IPH

//ip address class
class ip
{
    public:
        int address[4];//4 integers 0-255 make up an ip

        ip();
        ~ip();

        bool generate();// make a new ip address
        bool equal(ip &address2);//return true if they are equal
        //may need other comparisons later
    private:
};

#endif
