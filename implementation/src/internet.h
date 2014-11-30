#ifndef INTERNETH
#define INTERNETH
#include <cstddef>
#include <stdlib.h>
#include <iostream>
#include "router.h"

using namespace std;

class internet
{
    public:
        hub* connectedDevices;
        int connectedDeviceCount;

        internet(int numDevices);
        ~internet();

        bool connectDevice(hub* device);

    private:
};

#endif
