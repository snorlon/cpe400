#include "switch.h"

switchDevice::switchDevice()
{
    neighbors = NULL;

    bufferIncoming = NULL;
    bufferOutgoing = NULL;
    type = SWITCH_TYPE;//default is 1 for switch
}
