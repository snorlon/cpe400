#ifndef INTERNETH
#define INTERNETH
#include "hub.h"
#include <cstddef>
#include <stdlib.h>
#include <iostream>

using namespace std;

class internet
{
    public:
        hub* connectedDevices;
        int connectedDeviceCount;

        internet(int numDevices);
        ~internet();

    private:
};

#endif
