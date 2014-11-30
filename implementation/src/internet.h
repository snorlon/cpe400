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
        hub* getDevice(int index);
        hub* randomDevice();
        int countDevices(int type);

    private:
};

#endif
