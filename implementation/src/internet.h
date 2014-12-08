#ifndef INTERNETH
#define INTERNETH
#include <cstddef>
#include <stdlib.h>
#include <iostream>
#include "master.h"
#include "slave.h"
#include "registry.h"

using namespace std;

class internet
{
    public:
        hub* connectedDevices;
        int connectedDeviceCount;

        registry ipRegistry;//all ips will be pulled from here

        internet(int numDevices, int masterCount);
        ~internet();

        void init();

        bool connectDevice(hub* device);
        hub* getDevice(int index);
        hub* randomDevice();
        int countDevices(int type);
        void tick(double dt, int outputlevel);//tick the internet

    private:
};

#endif
